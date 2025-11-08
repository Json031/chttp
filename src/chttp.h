#ifndef CHTTP_H
#define CHTTP_H
#include <cjson/cJSON.h>
#include <curl/curl.h>

// Request enumeration type
enum http_client_req_method {
    get,// get
    post,// post
};

/**
*Pure URL link request
*@ param URL link
*@ return cJSON request result
*/
cJSON *get_query(const char *const url);

/**
*Get request
*@ param URL API address
*@ param headers Request headers (HTTP headers)
*The User Agent field in the HTTP request header of @ param useragent
*@ return cJSON request result
*/
cJSON *http_get_req(const char *const url, struct curl_slist *headers, const char *const useragent);

/**
*Post request
*@ param URL API address
*@ param headers Request headers (HTTP headers)
*@ parampost_fields POST form data
*The User Agent field in the HTTP request header of @ param useragent
*@ return cJSON request result
*/
cJSON * http_post_req(const char *const url, struct curl_slist *headers, const char *post_fields, const char *const useragent);

/**
*Upload file Upload file
*@ param URL API address
*@ param form_data_name form field name, upload file field name: "file" or "image"
*The file path for @ param file_cath is "/apps/AppName/filename. jpg"
*The User Agent field in the HTTP request header of @ param useragent
*
*@ return_Sool Upload file result
*/
cJSON * http_post_upload_file_req(const char *const url, char *file_name, char *file_path, const char *const useragent);

#endif // CHTTP_H
