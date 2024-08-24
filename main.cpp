#include <stdio.h>
#include "QES.h"
extern Test* TESTS;

int main(int argc, char* argv[]){
    printf("run main\n");
    Flag fl = {.flag = 1, .flag_cnt = 0};
    Color col= {.color = DEFAULT, .color_cnt = 0};
    int check_res = checkArgs(argc, argv, &fl, &col);
    set_color_flag(col.color);

    switch(check_res){
        case HELP:{
            printf("For manual scanning: ./a.out -m 0\n");
            printf("For Unit Testing: ./a.out -m 1\n");
            printf("To change color: ./a.out -c 0 (for blank)\v");
            printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
            printf("1 (for red)\v");
            printf("\b\b\b\b\b\b\b\b\b\b\b");
            printf("2 (for green)\n\r");
            break;
        }
        case MANUAL_SCAN:{
            printf("Quadratic Equation solver\n\n");
            struct QuadraticEquationCoef coefs;
            get_coefs(&coefs);

            struct QuadraticEquationSol equation;
            QuadraticEquationSolver(&coefs, &equation);
            printQdrEqRoots(&equation);
            break;
        }
        case UNIT_TESTING:{
            runAllTests();
            free();
            break;
        }
        case TERMINAL_ERROR:{
            printf("Nah, not gonna do this: ");
            printArgs(argc, argv);
        }
    }
    return 0;
}
