#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "nts_system_funcs.h"

#ifdef _WIN32
    #include <windows.h>
    #define msleep(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define msleep(ms) usleep((ms) * 1000)
#endif

void aprint(char* str, int delay_ms){
    for (int i = 0; str[i] != '\0'; i++){
        putchar(str[i]);
        fflush(stdout);
        msleep(delay_ms);
    }
}

void safeScanf(const char *input, ...){
    va_list args;
    va_start(args, input);
    int per_num = 0;
    for (int i = 0; input[i] != '\0'; i++){
        if (input[i] == '%' && input[i+1] != '%'){
            per_num++;
        }
    }
    if (vscanf(input, args) < per_num){
        while (getchar() != '\n');
    };
    va_end(args);
}

