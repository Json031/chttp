#include <stdio.h>
#include <cjson/cJSON.h>
#include "../src/chttp.h"

cJSON *queryIT(void) {
    cJSON *json = get_query("https://jsonplaceholder.typicode.com/todos/1");

    cJSON *keyJson = cJSON_GetObjectItemCaseSensitive(json, "result");
    if (cJSON_IsString(keyJson) && keyJson->valuestring)
    {
        printf("result: %s\n", keyJson->valuestring);
    }

    const cJSON *codeJson = cJSON_GetObjectItemCaseSensitive(json, "code");
    if (cJSON_IsNumber(codeJson))
        printf("code: %d\n", codeJson->valueint);

    const cJSON *intJson = cJSON_GetObjectItemCaseSensitive(json, "resultCode");
    if (cJSON_IsNumber(intJson))
        printf("completed: %s\n", intJson->valueint != 0 ? "true" : "false");

    return json;
}

int main(void) {
    cJSON *resp = queryIT();
    if (resp) {
        printf("✅ queryIT success!\n");
        cJSON_Delete(resp);
    } else {
        printf("❌ queryIT failed.\n");
    }
    return 0;
}
