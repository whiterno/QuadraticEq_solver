#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "../useful/useful.h"
#include "in_out.h"
#include "../consts.h"
#include "../QES_structs.h"
#include "../terminal/terminal.h"

static int get_double(double* num);
static void clearBuff();
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

    while (true){
        while (scanf("%lg", num) != 1){
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

    printf("Enter a:\n");
    get_double(&coefs->coef_a);
    printf("Enter b:\n");
    get_double(&coefs->coef_b);
    printf("Enter c:\n");
    get_double(&coefs->coef_c);
    return 0;
}

void printColor(int col){
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
