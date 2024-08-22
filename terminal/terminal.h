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

int checkArgs(const int argc, char* argv[], Flag* fl, Color* col);
void printArgs(const int argc, char* argv[]);

#endif
