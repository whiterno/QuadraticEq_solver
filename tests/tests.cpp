#include <stdio.h>
#include <assert.h>
#include "../QES_funcs/QES_funcs.h"
#include "../useful/useful.h"
#include "tests.h"
#include "../consts.h"
#include "../terminal/terminal.h"
#include "../in_out/in_out.h"

static Test* TESTS = freadTests();
static int TEST_AMOUNT =  0;

static int runTest(const int serial_num);
static int checkTest(const int serial_num, const struct QuadraticEquationSol* roots);
static void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots);
static void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots);

static int runTest(const int serial_num){
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    struct QuadraticEquationSol roots = {0, 0, 0};

    QuadraticEquationSolver(&TESTS[serial_num].coefs, &roots);

    int result = checkTest(serial_num, &roots);
    printTestResult(result, serial_num, &roots);
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

static void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    switch (result){
        case SOLUTION_SUCCESS: {
            cprint(GREEN, "Test %d: successful!\n", serial_num + 1);
            break;
        }
        case SOLUTION_ERROR: {
            printSolutionError(serial_num, roots);
            break;
        }
        default:{
            printf("Unknown ERROR!\n");
        }
    };
}

void runAllTests(){
    for(int test_count = 0; test_count < TEST_AMOUNT; test_count++){
        runTest(test_count);
    }
}

static void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots){
    cprint(RED, "Test %d: ERROR\n", serial_num + 1);
    printf("Test coefficients: a = %lg, b = %lg, c = %lg\n",
    TESTS[serial_num].coefs.coef_a, TESTS[serial_num].coefs.coef_b, TESTS[serial_num].coefs.coef_c);
    printf("Got result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    roots->QES_root_count, roots->root1, roots->root2);
    printf("Expected result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    TESTS[serial_num].sol.QES_root_count, TESTS[serial_num].sol.root1, TESTS[serial_num].sol.root2);
}

Test* freadTests(){
    printf("run freadTests\n");
    int size = 0;
    FILE * fp = fopen("./tests/tests", "r");
    assert(fp != NULL);
    //fseek(fp, 0L, SEEK_SET);

    printf("fscanf = %d\n", fscanf(fp, "%d", &size));
    printf("%d\n", size);

    Test* pntTest = (Test*)calloc(size, sizeof(Test));

    for(int test = 0; test < size; test++){
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_a);
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_b);
        fscanf(fp, "%lg", &pntTest[test].coefs.coef_c);
        fscanf(fp, "%d", &pntTest[test].sol.QES_root_count);
        fscanf(fp, "%lg", &pntTest[test].sol.root1);
        fscanf(fp, "%lg", &pntTest[test].sol.root2);
    }
    fclose(fp);
    TEST_AMOUNT = size;
    return pntTest;
}

void Testspr(Test* source, int size){
    for(int test = 0; test < size; test++){
        printf("%lg ", source[test].coefs.coef_a);
        printf("%lg ", source[test].coefs.coef_b);
        printf("%lg ", source[test].coefs.coef_c);
        printf("%d ", source[test].sol.QES_root_count);
        printf("%lg ", source[test].sol.root1);
        printf("%lg ", source[test].sol.root2);
    }
    printf("\n");
}
