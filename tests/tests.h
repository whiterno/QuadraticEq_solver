#include "../QES_structs.h"
#include "../consts.h"

#ifndef _TESTS
#define _TESTS

//! @brief Структура, содержащая в себе номер теста, коэффициенты квадратного уравнения и его корни
struct Test{
    int serial_num;                         ///< Номер теста
    struct QuadraticEquationCoef coefs;     ///< Коэффициенты квадратного уравнения
    struct QuadraticEquationSol sol;        ///< Решение квадратного уравнения
};

//!
//! @brief Считывает тесты из файла
//!
//! @param [out] test_amount   Количество тестов в файле
//! @param [in] file_name   Имя файла
//! @param [out] is_calloc  Проверяет, использовалась ли функция calloc()
//!
//! @return Массив тестов
//!
Test* freadTests(int* test_amount, char* file_name, bool* is_calloc);

//!
//! @brief Проверяет все тесты
//!
//! @param [in] TESTS     Массив всех тестов
//! @param [in] test_amount    Количество тестов в массиве
//!
//! @return void
//!
void runAllTests(Test TESTS[], const int test_amount);

enum Test_results{
    SOLUTION_SUCCESS,   ///< Показывает, что решение сошлось с ответом
    SOLUTION_ERROR      ///< Показывает, что решение не сошлось с ответом
};

#endif
