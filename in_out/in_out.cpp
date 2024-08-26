#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <stdarg.h>
#include "../useful/useful.h"
#include "in_out.h"
#include "../consts.h"
#include "../QES_structs.h"
#include "../terminal/terminal.h"

//!
//! @brief Принимает на ввод число типа double
//!
//! @param [out] num     Переменная типа double, в которую записывается введенное значение
//!
//! @return 0
//!
static int get_double(double* num);

//!
//! @brief Очищает буффер от ввода пользователя
//!
//! @param void
//!
//! @return void
//!
static void clearBuff();

//!
//! @brief Проверяет строку на пробельные символы
//!
//! @param void
//!
//! @return 1, если строка полностью состоит из пробельных символов, иначе 0
//!
static bool strIsSpace();

int printQdrEqRoots(const struct QuadraticEquationSol* sol){
    assert(sol != NULL);

    switch(sol->QES_root_count){
        case 0:{
            printf("Equation has no roots\n");
            break;
        }
        case 1:{
            printf("Equation has 1 root: x = %lg\n", sol->root1);
            break;
        }
        case 2:{
            printf("Equation has 2 roots: x1 = %lg, x2 = %lg\n", sol->root1, sol->root2);
            break;
        }
        case ES_INF_ROOTS:{
            printf("The root of the equation is any number\n");
            break;
        }
        default:{
            printf("Error: nRoots = %d\n", sol->QES_root_count);
            return 1;
        }
    }
    return 0;
}

static bool strIsSpace(){
    int character = 0;
    bool flag = true;

    while ((character = getchar()) != '\n' && character != EOF){
        if (!isspace(character)) flag = false;
    }
    return flag;
}

static void clearBuff(){
    int character;

    while ((character = getchar()) != '\n' && character != EOF){
        continue;
    }
}

static int get_double(double* num){
    assert(num != NULL);

    int scanf_output = 0;

    while (true){
        while ((scanf_output = scanf("%lg", num)) != 1){
            if (scanf_output == EOF){
                return 1;
            }
            printf("This is not a number! Try 2.2 or 6\n");
            clearBuff();
        }
        if (!strIsSpace()){
            printf("This is not a number! Try 2.2 or 6\n");
        }
        else{   // if (strIsSpace())
            return 0;
        }
    }
}

int get_coefs(struct QuadraticEquationCoef* coefs){
    assert(coefs != NULL);

    int get_double_output = 0;

    printf("Enter a:\n");
    get_double_output = get_double(&coefs->coef_a);
    if (get_double_output == 1){
        return 1;
    }
    printf("Enter b:\n");
    get_double_output = get_double(&coefs->coef_b);
    if (get_double_output == 1){
        return 1;
    }
    printf("Enter c:\n");
    get_double_output = get_double(&coefs->coef_c);
    if (get_double_output == 1){
        return 1;
    }
    return 0;
}
