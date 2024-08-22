#include <stdio.h>
#include "QES.h"

int main(int argc, char* argv[]){
    Flag fl = {.flag = 1, .flag_cnt = 0};
    Color col= {.color = DEFAULT, .color_cnt = 0};
    int check_res = checkArgs(argc, argv, &fl, &col);

    switch(check_res){
        case HELP:{
            printColor(col.color);
            printf("For manual scanning: ./a.out -m 0\n");
            printf("For Unit Testing: ./a.out -m 1\n");
            printf("To change color: ./a.out -c 0 (for blank)\v");
            printf("\b\b\b\b\b\b\b\b\b\b\b\b\b");
            printf("1 (for red)\v");
            printf("\b\b\b\b\b\b\b\b\b\b\b");
            printf("2 (for green)\n");
            break;
        }
        case MANUAL_SCAN:{
            printColor(col.color);
            printf("Quadratic Equation solver\n\n");
            struct QuadraticEquationCoef coefs;
            get_coefs(&coefs);

            struct QuadraticEquationSol equation;
            QuadraticEquationSolver(&coefs, &equation);
            printQdrEqRoots(&equation);
            break;
        }
        case UNIT_TESTING:{
            printColor(col.color);
            runAllTests(col.color);
            break;
        }
        case TERMINAL_ERROR:{
            printf("Nah, not gonna do this: ");
            printArgs(argc, argv);
        }
    }
    return 0;
}
