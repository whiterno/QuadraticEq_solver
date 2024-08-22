#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "terminal.h"
#include "../consts.h"

static int get_color(char* arg);
static int get_m(char* arg);

int checkArgs(const int argc, char* argv[], Flag* fl, Color* col){
    if (argc == 1){
        return MANUAL_SCAN;
    }

    for (int arg = 1; arg < argc; arg++){
        if (strcmp(argv[arg], "-c") == 0){
            if (arg + 1 == argc) {
                return TERMINAL_ERROR;
            }
            col->color = get_color(argv[arg + 1]);
            arg++;
            col->color_cnt++;
            continue;
        }
        if (strcmp(argv[arg], "--help") == 0){
            fl->flag = HELP;
            fl->flag_cnt++;
            continue;
        }
        if (strcmp(argv[arg], "-m") == 0){
            if (arg + 1 == argc) {
                return TERMINAL_ERROR;
            }
            fl->flag = get_m(argv[arg + 1]);
            arg++;
            fl->flag_cnt++;
            continue;
        }
        return TERMINAL_ERROR;
    }
    if (fl->flag_cnt > 1 || col->color == COLOR_ERROR || fl->flag == TERMINAL_ERROR || col->color_cnt > 1){
        return TERMINAL_ERROR;
    }
    return fl->flag;
}

void printArgs(const int argc, char* argv[]){
    for (int arg = 0; arg < argc; arg++){
        printf("%s ", argv[arg]);
    }
    printf("\n");
}

static int get_color(char* arg){
    if (strcmp(arg, "0") == 0){
        return BLANK;
    }
    if (strcmp(arg, "1") == 0){
        return RED;
    }
    if (strcmp(arg, "2") == 0){
        return GREEN;
    }
    return COLOR_ERROR;
}

static int get_m(char* arg){
    if (strcmp(arg, "0") == 0){
        return MANUAL_SCAN;
    }
    if (strcmp(arg, "1") == 0){
        return UNIT_TESTING;
    }
    return TERMINAL_ERROR;
}
