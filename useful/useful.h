#ifndef _USEFUL
#define _USEFUL

const double EPS = 0.000001;

//!
//! @brief Сравнивает число типа double с 0
//!
//! @param [in] num     Число типа double
//!
//! @return 1, если число равно 0, иначе 0
//!
bool isZero(const double num);

//!
//! @brief Сравнивает два числа типа double
//!
//! @param [in] num1    Первое число типа double
//! @param [in] num2    Второе число типа double
//!
//! @return 1, если числа равны, иначе 0
//!
bool fequal(const double num1, const double num2);

#endif
