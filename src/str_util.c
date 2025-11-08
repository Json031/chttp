#include <string.h>   // 提供 NULL strlen()
#include <stdbool.h>
#include <stdio.h>//snprintf，printf
#include <stdlib.h>//malloc
#include <stdarg.h>// ❌call to undeclared function 'va_start'；✅引入函数声明的头文件：#include <stdarg.h>

/**
 * 判断是否为Windows系统
 * @param void
 * @return bool 是否为Windows系统
 */
_Bool is_windows_sys() {
    _Bool is_windows = false;
    #if defined(_WIN32) || defined(_WIN64)
        is_windows = true;
    #endif
    return is_windows;
}
