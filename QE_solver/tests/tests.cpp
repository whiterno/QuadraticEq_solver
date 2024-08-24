#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../QES_funcs/QES_funcs.h"
#include "../useful/useful.h"
#include "tests.h"
#include "../consts.h"
#include "../terminal/terminal.h"
#include "../in_out/in_out.h"

static int runTest(const Test test, const int TEST_AMOUNT);
static int checkTest(const Test test, const struct QuadraticEquationSol* roots);
static void printTestResult(const int result, const Test test, const struct QuadraticEquationSol* roots);
static void printSolutionError(const Test test, const struct QuadraticEquationSol* roots);

static int runTest(const Test test, const int TEST_AMOUNT){
    assert((test.serial_num >= 0) && (test.serial_num < TEST_AMOUNT));

    struct QuadraticEquationSol roots = {0, 0, 0};

    QuadraticEquationSolver(&test.coefs, &roots);

    int result = checkTest(test, &roots);
    printTestResult(result, test, &roots);
    return result;
}

static int checkTest(const Test test, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);

    if (roots->QES_root_count == test.sol.QES_root_count){
        if (fequal(roots->root1, test.sol.root1) && fequal(roots->root2, test.sol.root2)){
            return SOLUTION_SUCCESS;
        }
        if(fequal(roots->root1, test.sol.root2) && fequal(roots->root2, test.sol.root1)){
            return SOLUTION_SUCCESS;
        }
    }
    return SOLUTION_ERROR;
}

static void printTestResult(const int result, const Test test, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);

    switch (result){
        case SOLUTION_SUCCESS: {
            cprint(GREEN, "Test %d: successful!\n", test.serial_num + 1);
            break;
        }
        case SOLUTION_ERROR: {
            printSolutionError(test, roots);
            break;
        }
        default:{
            printf("Unknown ERROR!\n");
        }
    };
}

void runAllTests(Test TESTS[], const int test_amount){
    for(int test_count = 0; test_count < test_amount; test_count++){
        runTest(TESTS[test_count], test_amount);
    }
}

static void printSolutionError(const Test test, const struct QuadraticEquationSol* roots){
    cprint(RED, "Test %d: ERROR\n", test.serial_num + 1);
    printf("Test coefficients: a = %lg, b = %lg, c = %lg\n",
    test.coefs.coef_a, test.coefs.coef_b, test.coefs.coef_c);
    printf("Got result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    roots->QES_root_count, roots->root1, roots->root2);
    printf("Expected result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    test.sol.QES_root_count, test.sol.root1, test.sol.root2);
}

Test* freadTests(int* test_amount){
    FILE * fp = fopen("./tests/tests", "r");
    assert(fp != NULL);

    fscanf(fp, "%d", test_amount);

    Test* pntTest = (Test*)calloc(*test_amount, sizeof(Test));

    for(int test = 0; test < *test_amount; test++){
        fscanf(fp, "%d", &pntTest[test].serial_num);
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_a);
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_b);
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_c);
        fscanf(fp, "%d", &pntTest[test].sol.QES_root_count);
        fscanf(fp, "%lg", &pntTest[test].sol.root1);
        fscanf(fp, "%lg", &pntTest[test].sol.root2);
    }
    fclose(fp);
    return pntTest;
}

void Testspr(Test* source, int size){
    for(int test = 0; test < size; test++){
        printf("%d ", source[test].serial_num);
        printf("%lg ", source[test].coefs.coef_a);
        printf("%lg ", source[test].coefs.coef_b);
        printf("%lg ", source[test].coefs.coef_c);
        printf("%d ", source[test].sol.QES_root_count);
        printf("%lg ", source[test].sol.root1);
        printf("%lg ", source[test].sol.root2);
        printf("\n");
    }
}
