#ifndef _USEFUL
#define _USEFUL

const double EPS = 0.000001;

//!
//! @brief compares double number with 0
//!
//! @param [in] num the double number
//!
//! @return 1 if the number is equal to 0, 0 if not
//!
bool isZero(const double num);

//!
//! @brief compares two double numbers
//!
//! @param [in] num1 the double number
//! @param [in] num2 the double number
//!
//! @return 1 if numbers are equal, 0 if not
//!
bool fequal(const double num1, const double num2);

#endif
