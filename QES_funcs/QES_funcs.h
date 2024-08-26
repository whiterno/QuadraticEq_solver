#ifndef _QES_FUNCS
#define _QES_FUNCS

//!
//! @brief Решает квадратное уравнение
//!
//! @param [in] coefs   Содержит 3 коэффициента квадратного уравнения
//! @param [out] sol   Содержит корни квадратного уравнения и количество корней
//!
//! @return void
//!
void QuadraticEquationSolver(const struct QuadraticEquationCoef* coefs, struct QuadraticEquationSol* sol);

#endif
