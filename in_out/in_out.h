#ifndef _IN_OUT
#define _IN_OUT

//!
//! @brief prints quadratic equation roots and their amount
//!
//! @param [in] const struct QuadraticEquationSol* sol  equation roots and their roots
//!
//! @return int     0
//!
int printQdrEqRoots(const struct QuadraticEquationSol* sol);

//!
//! @brief gets 3 coefs for quadratic equation
//!
//! @param [out] struct QuadraticEquationCoef* coefs    3 coefs for quadratic equation
//!
//! @return int     0
//!
int get_coefs(struct QuadraticEquationCoef* coefs);

//!
//! @brief prints color escape sequence
//!
//! @param [in] const int col   printed color
//!
//! @return void
//!
void printColor(const int col);

#endif
