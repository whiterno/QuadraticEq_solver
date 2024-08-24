#include <stdio.h>
#include <stdlib.h>
#include "QES.h"

int main(int argc, char* argv[]){
    Flag fl = {.flag = 1, .flag_cnt = 0};
    Color col= {.color = DEFAULT, .color_cnt = 0};
    int check_res = checkArgs(argc, argv, &fl, &col);
    set_color_flag(col.color);

    runProgramm(check_res, argc, argv);
    return 0;
}

void runProgramm(int check_res, int argc, char* argv[]){
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
            int test_amount = 0;
            Test* Tests = freadTests(&test_amount);
            runAllTests(Tests, test_amount);
            free(Tests);
            break;
        }
        case TERMINAL_ERROR:{
            printf("Nah, not gonna do this: ");
            printArgs(argc, argv);
        }
    }
}
