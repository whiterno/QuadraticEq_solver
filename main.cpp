#include <stdio.h>
#include <stdlib.h>
#include "QES.h"

//!
//! @brief Основная функция, которая работает исходя из пользовательского ввода
//!
//! @param [in] check_res   Флаг, полученный из ввода пользователя
//! @param [in] argc    Количество аргументов терминала
//! @param [in] argv     Массив аргументов терминала
//!
//! @return void
//!
void runProgramm(int check_res, int argc, char* argv[], char* file_name);

//!
//! @brief Функция main
//!
//! @param [in] int argc    Количество аргументов терминала
//! @param [in] char** argv     Массив аргументов терминала
//!
//! @return int     0
//!
int main(int argc, char* argv[]){
    int flag = NOTHING;
    int col = DEFAULT;
    char file_name[100] = "./tests/tests";
    int check_res = checkArgs(argc, argv, &flag, &col, file_name);
    set_color_flag(col);

    runProgramm(check_res, argc, argv, file_name);
    return 0;
}

void runProgramm(int check_res, int argc, char* argv[], char* file_name){
    switch(check_res){
        case HELP:{
            printf("For manual scanning: ./a.out -m 0\n");
            printf("For Unit Testing: ./a.out -m 1\n");
            printf("To read tests from file (DEFAULT: ./tests/tests): ./a.out -m 1 -f FILE_NAME\n");
            printf("To disable color: ./a.out -c 0\n");
            printf("To set default color: ./a.out -c 1\n");
            break;
        }
        case MANUAL_SCAN:{
            printf("Quadratic Equation solver\n\n");
            struct QuadraticEquationCoef coefs;
            int get_coefs_output = 0;
            get_coefs_output = get_coefs(&coefs);

            if (get_coefs_output == 1){
                printf("Input Error detected\n");
                break;
            }

            struct QuadraticEquationSol equation;
            QuadraticEquationSolver(&coefs, &equation);
            printQdrEqRoots(&equation);
            break;
        }
        case UNIT_TESTING:{
            int test_amount = 0;
            bool is_calloc = true;
            Test* Tests = freadTests(&test_amount, file_name, &is_calloc);
            //Testspr(Tests, 11);
            runAllTests(Tests, test_amount);
            if (is_calloc){
                free(Tests);
            }
            break;
        }
        case TERMINAL_ERROR:{
            printf("Nah, not gonna do this: ");
            printArgs(argc, argv);
        }
    }
}
