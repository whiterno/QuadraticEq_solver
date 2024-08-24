#include "../QES_structs.h"
#include "../consts.h"

#ifndef _TESTS
#define _TESTS

struct Test{
    struct QuadraticEquationCoef coefs;
    struct QuadraticEquationSol sol;
};

Test* freadTests();
void runAllTests();
void Testspr(Test* source, int size);


// const struct Test TESTS[]= {
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 0,
//                    .coef_c = 0},
//          .sol = {.QES_root_count = ES_INF_ROOTS,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 0,
//                    .coef_c = 1},
//          .sol = {.QES_root_count = 0,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 1,
//                    .coef_c = 0},
//          .sol = {.QES_root_count = 1,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 1,
//                    .coef_c = 1},
//          .sol = {.QES_root_count = 1,
//                  .root1 = -1,
//                  .root2 = -1}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 0,
//                    .coef_c = 1.2},
//          .sol = {.QES_root_count = 0,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 1.2,
//                    .coef_c = 0},
//          .sol = {.QES_root_count = 1,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 0,
//                    .coef_b = 1.2,
//                    .coef_c = 4.8},
//          .sol = {.QES_root_count = 1,
//                  .root1 = -4,
//                  .root2 = -4}},
//
//         {.coefs = {.coef_a = 4,
//                    .coef_b = -4,
//                    .coef_c = 1},
//          .sol = {.QES_root_count = 1,
//                  .root1 = 0.5,
//                  .root2 = 0.5}},
//
//         {.coefs = {.coef_a = 1,
//                    .coef_b = -2,
//                    .coef_c = -15},
//          .sol = {.QES_root_count = 2,
//                  .root1 = -3,
//                  .root2 = 5}},
//
//         {.coefs = {.coef_a = 1,
//                    .coef_b = 2,
//                    .coef_c = 10},
//          .sol = {.QES_root_count = 0,
//                  .root1 = 0,
//                  .root2 = 0}},
//
//         {.coefs = {.coef_a = 1,
//                    .coef_b = 7,
//                    .coef_c = 10},
//          .sol = {.QES_root_count = 2,
//                  .root1 = -2,
//                  .root2 = -5}},
//
//         {.coefs = {.coef_a = 1,
//                    .coef_b = 7,
//                    .coef_c = 10},
//          .sol = {.QES_root_count = 2,
//                  .root1 = -5,
//                  .root2 = -2}}
//
//     };
enum Test_results{
    SOLUTION_SUCCESS,
    SOLUTION_ERROR
};

//const int TEST_AMOUNT =  (sizeof TESTS) / (sizeof TESTS[0]);

#endif
