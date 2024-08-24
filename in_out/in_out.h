#ifndef _IN_OUT
#define _IN_OUT

int printQdrEqRoots(const struct QuadraticEquationSol* pnt_eq);
int get_coefs(struct QuadraticEquationCoef* pnt_QEC);
void printColor(const int col);
void cprint(const int col, const char* fmt, ...);
void set_color_flag(const int col);

#endif
