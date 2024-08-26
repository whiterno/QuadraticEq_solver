#ifndef _TERMINAL
#define _TERMINAL

enum Terminal_input_results{
    NOTHING,        ///< Показывает, что в терминал ничего не вводили
    HELP,           ///< Показывает, что введен флаг --help
    MANUAL_SCAN,    ///< Показывает, что введен флаг -m 0
    UNIT_TESTING,   ///< Показывает, что введен флаг -m 1
    TERMINAL_ERROR  ///< Показывает, что был введен неизвестный флаг
};

//!
//! @brief Считывает пользовательский ввод
//!
//! @param [in] argc   Количество введенных аргуметов
//! @param [in] argv[]     Массив введенных аргументов
//! @param [out] flag   Флаг, полученный из пользовательского ввода
//! @param [out] col     Флаг цвета, полученный из пользовательского ввода
//! @param [out] file_name     Имя файла для считывание тестов, полученное из пользовательского ввода
//!
//! @return Флаг вывода (Unit testing, Manual scan или Help), полученный из пользовательского ввода
//!
int checkArgs(const int argc, char* argv[], int* flag, int* col, char* file_name);

//!
//! @brief Выводит пользовательский ввод
//!
//! @param [in] argc  Количество введенных аргуметов
//! @param [in] argv[]    Массив введенных аргументов
//!
//! @return void
//!
void printArgs(const int argc, char* argv[]);

#endif
