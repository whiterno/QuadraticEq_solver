#ifndef _TERMINAL
#define _TERMINAL

struct Flag{
    int flag, flag_cnt;
};

struct Color{
    int color, color_cnt;
};

enum Terminal_input_results{
    HELP,
    MANUAL_SCAN,
    UNIT_TESTING,
    TERMINAL_ERROR
};

enum Colors{
    COLOR_ERROR = -2,
    DEFAULT,
    BLANK,
    RED,
    GREEN
};

//!
//! @brief reads and checks terminal input
//!
//! @param [in] const int argc   amount of terminal input
//! @param [in] char* argv[]     terminal input
//! @param [out] Flag* fl   flag from terminal input
//! @param [out] Color* col     color flag from terminal input
//!
//! @return int     terminal input check result
//!
int checkArgs(const int argc, char* argv[], Flag* fl, Color* col);

//!
//! @brief prints terminal input
//!
//! @param [in] const int argc  amount of terminal input
//! @param [in] char* argv[]    terminal input
//!
//! @return void
//!
void printArgs(const int argc, char* argv[]);

#endif
