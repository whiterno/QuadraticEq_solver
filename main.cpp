#include <stdio.h>
#include <math.h>

const int QES_INF_ROOTS = -1;
const double EPS = 0.0001;

int QuadraticEquationSolver(double, double, double, double*, double*);

int main(void){
    printf("Quadratic Equation solver\n");

    printf("Enter a, b, c: \n");
    double a = 0, b = 0, c = 0;
    scanf("%lg %lg %lg", &a, &b, &c);

    double x1 = 0, x2 = 0;
    int nRoots = QuadraticEquationSolver(a, b, c, &x1, &x2);

    switch(nRoots){
        case 0:{
            printf("Equation has no roots\n");
            break;
        }
        case 1:{
            printf("x = %lg\n", x1);
            break;
        }
        case 2:{
            printf("x1 = %lg, x2 = %lg\n", x1, x2);
            break;
        }
        case QES_INF_ROOTS:{
            printf("Any number\n");
            break;
        }
        default:{
            printf("Error: nRoots = %d\n", nRoots);
            return 1;
        }
    }


    return 0;
}

int QuadraticEquationSolver(double a, double b, double c, double* x1, double* x2){
    if (fabs(a - 0) < EPS){
        if (fabs(b - 0) < EPS){
            return (fabs(c - 0) < EPS)? QES_INF_ROOTS : 0;
        }
        else{   // if (fabs(b - 0) > EPS)
            *x1 = *x2 = -c/b;
            return 1;
        }
    }
    else{   // if (fabs(a - 0) > EPS)
        double d = b * b - 4 * a * c;
        if (fabs(d - 0) < EPS){
            *x1 = *x2 = -b / (2 * a);
            return 1;
        }
        else if (d > 0){
            *x1 = (-b + sqrt(d)) / (2 * a);
            *x2 = (-b - sqrt(d)) / (2 * a);
            return 2;
        }
        else{   // if (d < 0)
            return 0;
        }
    }
}
