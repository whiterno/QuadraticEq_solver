#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "terminal.h"
#include "../consts.h"
#include "../cprint/cprint.h"

//!
//! @brief Считывает второй аргумент после флага -m
//!
//! @param [in] str     Второй аргумент в виде строки
//!
//! @return 0, если введено 0, 1, если введено 1
//!
static int get_m(char* str);

//!
//! @brief Считывает второй аргумент после флага -с
//!
//! @param [in] str     Второй аргумент в виде строки
//!
//! @return 0, если введено 0, 1, если введено 1
//!
static int get_col_flag(char* str);


int checkArgs(const int argc, char* argv[], int* flag, int* col, char* file_name){
    if (argc == 1){
        return MANUAL_SCAN;
    }

    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--help") == 0){
            if (*flag == NOTHING){
                *flag = HELP;
                continue;
            }
            else return TERMINAL_ERROR;
        }
        if (strcmp(argv[i], "-m") == 0){
            if (*flag == NOTHING){
                if (i + 1 == argc){
                    return TERMINAL_ERROR;
                }
                *flag = get_m(argv[i + 1]);
                i++;
                continue;
            }
            else return TERMINAL_ERROR;
            }
        if (strcmp(argv[i], "-c") == 0){
            if (*col == DEFAULT){
                if (i + 1 == argc){
                    return TERMINAL_ERROR;
                }
                *col = get_col_flag(argv[i + 1]);
                i++;
                continue;
            }
            else return TERMINAL_ERROR;
        }
        if (strcmp(argv[i], "-f") == 0 && *flag == UNIT_TESTING){
            if (i + 1 == argc){
                return TERMINAL_ERROR;
            }
            strcpy(file_name, argv[i + 1]);
            i++;
            continue;
        }
        return TERMINAL_ERROR;
    }
    return *flag;
}

void printArgs(const int argc, char* argv[]){
    for (int arg = 0; arg < argc; arg++){
        printf("%s ", argv[arg]);
    }
    printf("\n");
}

int get_m(char* str){
    if (strcmp(str, "0") == 0){
            return MANUAL_SCAN;
    }
    if (strcmp(str, "1") == 0){
            return UNIT_TESTING;
    }
    return TERMINAL_ERROR;
}

int get_col_flag(char* str){
    if (strcmp(str, "0") == 0){
            return DISABLE_COLOR;
    }
    if (strcmp(str, "1") == 0){
            return DEFAULT_IN;
    }
    return TERMINAL_ERROR;
}
