#include <stdio.h>
#include <stdarg.h>
#include "../terminal/terminal.h"
#include "../in_out/in_out.h"
#include "cprint.h"

//! @brief Используется, чтобы остановить цветной вывод
const char* STOP_COL = "\033[0m";

//! @brief  Показывает включен или выключен цветной вывод
static int color_flag = DEFAULT;

static void printColor(const int col);

void cprint(const int col, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    if (color_flag == DISABLE_COLOR){
        vprintf(fmt, ap);
    }
    else{
        printColor(col);
        vprintf(fmt, ap);
        printf("%s", STOP_COL);
    }
}

void set_color_flag(const int col){
    color_flag = col;
}

static void printColor(const int col){
    if (col == BLANK){
        printf("\033[0m");
    }
    if (col == RED){
        printf("\033[31m");
    }
    if (col == GREEN){
        printf("\033[32m");
    }
}
