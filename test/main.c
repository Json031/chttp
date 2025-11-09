#include <stdio.h>
#include <cjson/cJSON.h>
#include "../src/chttp.h"
#include "../src/str_util.h"


cJSON *post_request(void) {
    char *base_url = "https://www.xxx.com/post";
    char *access_token = "xxx.c01e10f773e89c7623267b527cf49xxx.xxxMW3wEYAY6gAZQG_y2_AQSvtJfD2655unQb3w.xxxxxx";
    char url[1024];
    snprintf(url, sizeof(url),
        "%s?method=filemanager&access_token=%s&opera=delete",
        base_url, access_token);

    char *address_param = "NY";
    char form_urlencoded[256];
    snprintf(form_urlencoded, sizeof(form_urlencoded), "address=%s&async=1", address_param);

    cJSON *json = http_post_req(url, NULL, form_urlencoded, NULL);
    char *json_str = cJSON_PrintUnformatted(json);
    printf("result:%s\n", json_str);
    return json;
}

cJSON *upload_files(void) {
    char *file_path = "./test/Doraemon_Charactor.jpg";
    char *upload_file_url = "https://www.xxx.com/file";
    char *access_token = "xxx.c01e10f773e89c7623267b527cf49xxx.xxxMW3wEYAY6gAZQG_y2_AQSvtJfD2655unQb3w.xxxxxx";
    char *file_name = "file";

    char url[1024];
    snprintf(url, sizeof(url),
        "%s?method=upload&access_token=%s",
        upload_file_url, access_token);
    cJSON *json = http_post_upload_file_req(url, file_name, file_path, NULL);
    char *json_str = cJSON_PrintUnformatted(json);
    printf("result:%s\n", json_str);
    return json;
}

cJSON *query_todos(void) {
    cJSON *json = get_query("https://jsonplaceholder.typicode.com/todos/1");

    cJSON *keyJson = cJSON_GetObjectItemCaseSensitive(json, "result");
    if (cJSON_IsString(keyJson) && keyJson->valuestring)
    {
        printf("result: %s\n", keyJson->valuestring);
    }

    return json;
}

int main(void) {
    cJSON *resp = query_todos();
    if (resp) {
        printf("✅ queryIT success!\n");
        cJSON_Delete(resp);
    } else {
        printf("❌ queryIT failed.\n");
    }
    cJSON *resp2 = upload_files();
    cJSON *resp3 = post_request();
    
    return 0;
}
