#ifndef _QES_STRUCTS
#define _QES_STRUCTS

struct QuadraticEquationSol{
    int QES_root_count;
    double root1, root2;
};

struct QuadraticEquationCoef{
    double coef_a, coef_b, coef_c;
};

#endif
