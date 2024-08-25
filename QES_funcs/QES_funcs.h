#ifndef _QES_FUNCS
#define _QES_FUNCS

//!
//! @brief solves quadratic equation
//!
//! @param [in] const struct QuadraticEquationCoef* coefs   contains 3 coefs for equation
//! @param [out] struct QuadraticEquationSol* sol   contains quadratic equation solution
//!
//! @return void
//!
void QuadraticEquationSolver(const struct QuadraticEquationCoef* coefs, struct QuadraticEquationSol* sol);

#endif
