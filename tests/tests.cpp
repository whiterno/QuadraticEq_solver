#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../QES_funcs/QES_funcs.h"
#include "../useful/useful.h"
#include "tests.h"
#include "../consts.h"
#include "../terminal/terminal.h"
#include "../in_out/in_out.h"
#include "../cprint/cprint.h"

//! Размер массива тестов, встроенного в программу
static const int SIZE_IN_BUILT = 12;

//! Массив тестов, встроенный в программу
struct Test TESTS_IN_BUILT[]= {

        {.serial_num = 0,
        .coefs = {.coef_a = 0,
                   .coef_b = 0,
                   .coef_c = 0},
         .sol = {.QES_root_count = ES_INF_ROOTS,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 1,
        .coefs = {.coef_a = 0,
                   .coef_b = 0,
                   .coef_c = 1},
         .sol = {.QES_root_count = 0,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 2,
        .coefs = {.coef_a = 0,
                   .coef_b = 1,
                   .coef_c = 0},
         .sol = {.QES_root_count = 1,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 3,
        .coefs = {.coef_a = 0,
                   .coef_b = 1,
                   .coef_c = 1},
         .sol = {.QES_root_count = 1,
                 .root1 = -1,
                 .root2 = -1}},

        {.serial_num = 4,
        .coefs = {.coef_a = 0,
                   .coef_b = 0,
                   .coef_c = 1.2},
         .sol = {.QES_root_count = 0,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 5,
        .coefs = {.coef_a = 0,
                   .coef_b = 1.2,
                   .coef_c = 0},
         .sol = {.QES_root_count = 1,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 6,
        .coefs = {.coef_a = 0,
                   .coef_b = 1.2,
                   .coef_c = 4.8},
         .sol = {.QES_root_count = 1,
                 .root1 = -4,
                 .root2 = -4}},

        {.serial_num = 7,
        .coefs = {.coef_a = 4,
                   .coef_b = -4,
                   .coef_c = 1},
         .sol = {.QES_root_count = 1,
                 .root1 = 0.5,
                 .root2 = 0.5}},

        {.serial_num = 8,
        .coefs = {.coef_a = 1,
                   .coef_b = -2,
                   .coef_c = -15},
         .sol = {.QES_root_count = 2,
                 .root1 = -3,
                 .root2 = 5}},

        {.serial_num = 9,
        .coefs = {.coef_a = 1,
                   .coef_b = 2,
                   .coef_c = 10},
         .sol = {.QES_root_count = 0,
                 .root1 = 0,
                 .root2 = 0}},

        {.serial_num = 10,
        .coefs = {.coef_a = 1,
                   .coef_b = 7,
                   .coef_c = 10},
         .sol = {.QES_root_count = 2,
                 .root1 = -2,
                 .root2 = -5}},

        {.serial_num = 11,
        .coefs = {.coef_a = 1,
                   .coef_b = 7,
                   .coef_c = 10},
         .sol = {.QES_root_count = 2,
                 .root1 = -5,
                 .root2 = -2}}

    };

//!
//! @brief Проверяет один тест
//!
//! @param [in] test   Тест
//! @param [in] TEST_AMOUNT   Количество тестов в массиве тестов
//!
//! @return Результат проверки теста
//!
static int runTest(const Test test, const int TEST_AMOUNT);

//!
//! @brief  Сравнивает вывод QuadraticEquationSolver() с ответом
//!
//! @param [in] test     Тест с ответом
//! @param [in] roots    Корни, полученные с QuadraticEquationSolver()
//!
//! @return Сошелся ли решение функции с ответом или нет: SOLUTION_SUCCESS или SOLUTION_ERROR
//!
static int checkTest(const Test test, const struct QuadraticEquationSol* roots);

//!
//! @brief Выводит результаты проверки теста (success или error)
//!
//! @param [in] result    Результата проверки теста
//! @param [in] test     Тест с ответами
//! @param [in] roots    Корни, полученные с QuadraticEquationSolver()
//!
//! @return void
//!
static void printTestResult(const int result, const Test test, const struct QuadraticEquationSol* roots);

//!
//! @brief  Выводит сообщение, если найдена ошибка
//!
//! @param [in] test     Тест с ответом и коэффициентами
//! @param [in] roots    Корни, полученные с QuadraticEquationSolver()
//!
//! @return void
//!
static void printSolutionError(const Test test, const struct QuadraticEquationSol* roots);

//!
//! @brief Выводит массив тестов (debug функция)
//!
//! @param [in] source     Массив тестов
//! @param [in] size     Количество тестов в массиве
//!
//! @return void
//!
static void Testspr(Test* source, int size);

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

void runAllTests(Test Tests[], const int test_amount){
    for(int test_count = 0; test_count < test_amount; test_count++){
        runTest(Tests[test_count], test_amount);
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

Test* freadTests(int* test_amount, char* file_name, bool* is_calloc){
    FILE * fp = fopen(file_name, "r");
    if (fp == NULL){
        printf("Can't read file, use in-built tests\n");
        *is_calloc = false;
        *test_amount = SIZE_IN_BUILT;
        return TESTS_IN_BUILT;
    }

    if (fscanf(fp, "%d", test_amount) != 1){
        *is_calloc = false;
        printf("Wrong input file format\n");
        return NULL;
    }

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

static void Testspr(Test* source, int size){
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
