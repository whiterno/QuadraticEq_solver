#ifndef _CPRINT
#define _CPRINT

enum Color_flag{
    DEFAULT,        ///< Показывает, что используется стандартный цвет
    DEFAULT_IN,     ///< Показывает, что используется стандартный цвет после ввода флага -c 1
    DISABLE_COLOR   ///< Показывает, что цвет отключен
};

enum Colors{
    COLOR_ERROR = -1,   ///< Показывает, что появилась ошибка во время ввода цвета
    BLANK,              ///< Показывает, что вывод без цвета
    RED,                ///< Показывает, что вывод красного цвета
    GREEN               ///< Показывает, что вывод зеленого цвета
};
//!
//! @brief Цветной вывод
//!
//! @param [in] col   Цвет вывода
//! @param [out] fmt     Строка вывода
//!
//! @return void
//!
void cprint(const int col, const char* fmt, ...);

//!
//! @brief Включает или отключает cprint()
//!
//! @param [in] col     Флаг показывает, включен или выключен цветной вывод
//!
//! @return void
//!
void set_color_flag(const int col);

#endif
