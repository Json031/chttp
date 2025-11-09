#include <string.h>   // 提供 NULL strlen()
#include <stdbool.h>
#include <stdio.h>//snprintf，printf
#include <stdlib.h>//malloc
#include <stdarg.h>// ❌call to undeclared function 'va_start'；✅引入函数声明的头文件：#include <stdarg.h>

/**
*Determine whether it is a Windows system
* @param void
*Is @ return boolean a Windows system
*/
_Bool is_windows_sys() {
    _Bool is_windows = false;
    #if defined(_WIN32) || defined(_WIN64)
        is_windows = true;
    #endif
    return is_windows;
}

/**
*Determine if the file exists
*The file path of @ aram file_math, for example: "./assets/images/cymbal/cymbal-00. jpg";
*Does the @ return boolean file exist
*/
_Bool is_file_exist(const char *file_path) {
    if (!file_path) return false;
    FILE *fp = fopen(file_path, "rb");
    if (fp) {
        fclose(fp);
        return true;
    }
    return false;
}