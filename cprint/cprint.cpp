#include <stdio.h>
#include <stdarg.h>
#include "../terminal/terminal.h"
#include "../in_out/in_out.h"
#include "cprint.h"

//! @brief enables or disables colorful output
static int color_flag = DEFAULT;

void cprint(const int col, const char* fmt, ...){
    va_list ap;
    va_start(ap, fmt);

    if (color_flag == BLANK){
        vprintf(fmt, ap);
    }
    else{
        printColor(col);
        vprintf(fmt, ap);
        printf("\033[0m");
    }
}

void set_color_flag(const int col){
    color_flag = col;
}

