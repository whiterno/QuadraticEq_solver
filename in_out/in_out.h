#ifndef _IN_OUT
#define _IN_OUT

//!
//! @brief Выводит корни квадратного уравнения и их количество
//!
//! @param [in] sol  Корни квадратного уравнения и их количество
//!
//! @return 0, если не было непредусмотренных входных данных, иначе 1
//!
int printQdrEqRoots(const struct QuadraticEquationSol* sol);

//!
//! @brief Принимает на ввод 3 числа типа double
//!
//! @param [out] coefs    3 коэффициента квадратного уравнения
//!
//! @return 0
//!
int get_coefs(struct QuadraticEquationCoef* coefs);

#endif
