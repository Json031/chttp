#include "chttp.h"
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "str_util.h"

typedef struct {
    char *memory_data;
    size_t size;
} MemoryBlock;

/**
*Curl callback
*The data pointer sent by libcurl for @ param contents
*@ paramsize The size of each data unit (usually 1)
*Number of Aram nmem data units
*Custom pointer passed in through CURLOPT-WRITEDATA by @ paramuserp (can be used to pass structures, buffers, etc.)
*@ return Actual number of bytes processed
*/
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t total = size * nmemb;
    MemoryBlock *mem = (MemoryBlock *)userp;

    char *ptr = realloc(mem->memory_data, mem->size + total + 1);
    if (ptr == NULL) {
        printf("Out of memory");
        return 0; 
    }

    mem->memory_data = ptr;
    memcpy(&(mem->memory_data[mem->size]), contents, total);
    mem->size += total;
    mem->memory_data[mem->size] = '\0';

    return total;
}

/**
*HTTP request
*@ param URL API address
*@ param method request method, get/post
*@ param headers Request headers (HTTP headers)
*@ param form_urlencoded regular form (text) Content Type: application/x-www-form-urlencoded
*The User Agent field in the HTTP request header of @ param useragent
*
*@ return cJSON request result
*/
static cJSON *http_request(const char *const url,
                          enum http_client_req_method method,
                          struct curl_slist *headers,
                          const char *form_urlencoded,
                          struct curl_httppost *form_data,
                          const char *const useragent) {

    MemoryBlock chunk = {0};
    chunk.memory_data = malloc(1);  // 初始空字符串
    chunk.size = 0;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL *curl = curl_easy_init();
    if (curl) {
        // 设置目标 URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        switch (method)
        {
        case get:
            curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
            break;
        case post:
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            //Set the POST data as the RequestBody parameter, and attach the URL parameter directly to the URL
            if (form_urlencoded != NULL)
            {
                printf("form_urlencoded: %s\n", form_urlencoded);
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, form_urlencoded);
            }
            if (form_data != NULL) {
                //Form_data is a pointer type pointing to the linked list structure. If the output of the printed pointer is (nil) or 0x0, it indicates that cur_formadd() was not successfully created
                printf("form_data pointer: %p\n", (void*)form_data);
                //Set HTTP POST multipart/form data form data
                curl_easy_setopt(curl, CURLOPT_HTTPPOST, form_data);
            }
            break;

        default:
            break;
        }

        if (headers != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        if (useragent != NULL)
        {
            curl_easy_setopt(curl, CURLOPT_USERAGENT, useragent);
        }


        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        //Open detailed debugging output and observe the TLS handshake process
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        if (is_windows_sys()) {
            printf("Running on Windows\n");
            const char *cert_path = getenv("SSL_CERT_FILE");
            if (cert_path) {
                curl_easy_setopt(curl, CURLOPT_CAINFO, cert_path);
            } else {
                printf("Warning: SSL_CERT_FILE not set.\n");
            }
        } else {
            printf("Running on MacOS or Linux System\n");
        }

        //Using OpenSSL for certificate verification
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);  
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);  

        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            printf("curl failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Response:\n%s\n", chunk.memory_data);

            cJSON *json = cJSON_Parse(chunk.memory_data);
            if (json == NULL) {
                fprintf(stderr, "Failed to parse JSON\n");
            } else {

                return json;
            }
        }
    }

    //Request failed, returned NULL
    free(chunk.memory_data);
    return NULL;
}



/**
*Pure URL link request
*@ param URL link
*@ return cJSON request result
*/
cJSON *get_query(const char *const url) {
    return http_request(url, get, NULL, NULL, NULL, NULL);
}


/**
*Get request
*@ param URL API address
*@ param headers Request headers (HTTP headers)
*The User Agent field in the HTTP request header of @ param useragent
*@ return cJSON request result
*/
cJSON * http_get_req(const char *const url, struct curl_slist *headers, const char *const useragent) {
    return http_request(url, get, headers, NULL, NULL, useragent);
}

/**
*Post request
*@ param URL API address
*@ param headers Request headers (HTTP headers)
*@ parampost_fields POST form data
*The User Agent field in the HTTP request header of @ param useragent
*@ return cJSON request result
*/
cJSON * http_post_req(const char *const url, struct curl_slist *headers, const char *post_fields, const char *const useragent) {
    return http_request(url, post, headers, post_fields, NULL, useragent);
}


/**
*Upload file Upload file
*@ param URL API address
*@ param form_data_name form field name, upload file field name: "file" or "image"
*The file path for @ param file_cath is "/apps/AppName/filename. jpg"
*The User Agent field in the HTTP request header of @ param useragent
*
*@ return_Sool Upload file result
*/
cJSON * http_post_upload_file_req(const char *const url, char *form_data_name, char *file_path, const char *const useragent) {
    //Set up multipart/form data form
    struct curl_httppost *formpost = NULL;
    struct curl_httppost *lastptr = NULL;

    curl_formadd(&formpost, &lastptr,
                    CURLFORM_COPYNAME, form_data_name,
                    CURLFORM_FILE, file_path,
                    CURLFORM_END);

    cJSON *result = http_request(url, post, NULL, NULL, formpost, useragent);

    curl_formfree(formpost); //free resources
    return result;
}
