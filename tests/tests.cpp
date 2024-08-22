#include <stdio.h>
#include <assert.h>
#include "../QES_funcs/QES_funcs.h"
#include "../useful/useful.h"
#include "tests.h"
#include "../consts.h"
#include "../terminal/terminal.h"

static int runTest(const int serial_num, int col);
static int checkTest(const int serial_num, const struct QuadraticEquationSol* roots);
static void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots, int col);
static void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots, int col);

static int runTest(const int serial_num, int col){
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    struct QuadraticEquationSol roots = {0, 0, 0};

    QuadraticEquationSolver(&TESTS[serial_num].coefs, &roots);

    int result = checkTest(serial_num, &roots);
    printTestResult(result, serial_num, &roots, col);
    return result;
}

static int checkTest(const int serial_num, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    if (roots->QES_root_count == TESTS[serial_num].sol.QES_root_count){
        if (fequal(roots->root1, TESTS[serial_num].sol.root1) && fequal(roots->root2, TESTS[serial_num].sol.root2)){
            return SOLUTION_SUCCESS;
        }
        if(fequal(roots->root1, TESTS[serial_num].sol.root2) && fequal(roots->root2, TESTS[serial_num].sol.root1)){
            return SOLUTION_SUCCESS;
        }
    }
    return SOLUTION_ERROR;
}

static void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots, int col){
    assert(roots != NULL);
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    switch (result){
        case SOLUTION_SUCCESS: {
            if (col == DEFAULT){
                printf("\033[32mTest %d: successful!\n\033[0m", serial_num + 1);
            }
            else{
                printf("Test %d: successful!\n", serial_num + 1);
            }
            break;
        }
        case SOLUTION_ERROR: {
            printSolutionError(serial_num, roots, col);
            break;
        }
        default:{
            printf("Unknown ERROR!\n");
        }
    };
}

void runAllTests(int col){
    for(int test_count = 0; test_count < TEST_AMOUNT; test_count++){
        runTest(test_count, col);
    }
}

static void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots, int col){
    if (col == DEFAULT){
        printf("\033[31mTest %d: ERROR\033[0m", serial_num + 1);
    }
    else{
        printf("Test %d: ERROR", serial_num + 1);
    }
    printf("Test coefficients: a = %lg, b = %lg, c = %lg\n",
    TESTS[serial_num].coefs.coef_a, TESTS[serial_num].coefs.coef_b, TESTS[serial_num].coefs.coef_c);
    printf("Got result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    roots->QES_root_count, roots->root1, roots->root2);
    printf("Expected result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    TESTS[serial_num].sol.QES_root_count, TESTS[serial_num].sol.root1, TESTS[serial_num].sol.root2);
}
