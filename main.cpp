#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

const int ES_INF_ROOTS = -1;
const double EPS = 0.0001;

int QuadraticEquationSolver(double, double, double, double*, double*);
bool isZero(double);
double discriminant(double, double, double);
int LinearEquationSolver(double, double, double*);
int printQdrEqRoots(int, double, double);
int get_double(double*);
void dumpBuff();
int get_coefs(double* ,double*, double*);


int main(void){
    printf("Quadratic Equation solver\n\n");

    double a = 0, b = 0, c = 0;
    get_coefs(&a, &b, &c);

    double x1 = 0, x2 = 0;
    int QES_root_count = QuadraticEquationSolver(a, b, c, &x1, &x2);

    printQdrEqRoots(QES_root_count, x1, x2);

    return 0;
}

int QuadraticEquationSolver(double a, double b, double c, double* x1, double* x2){
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    if (isZero(a)){
        int LES_root_count = LinearEquationSolver(b, c, x1);
        *x2 = *x1;
        return LES_root_count;
    }
    else{   // if (!isZero(a))
        double d = discriminant(a, b, c);
        if (isZero(d)){
            *x1 = -b / (2 * a);
            *x2 = -b / (2 * a);
            return 1;
        }
        else if (d > 0){
            double sqrt_d = sqrt(d);
            *x1 = (-b + sqrt_d) / (2 * a);
            *x2 = (-b - sqrt_d) / (2 * a);
            return 2;
        }
        else{   // if (d < 0)
            return 0;
        }
    }
}

int LinearEquationSolver(double a, double b, double* x){
    if (isZero(a)){
        return (isZero(b))? ES_INF_ROOTS : 0;
    }
    else{   // if (!isZero(a))
        *x = -b / a;
        return 1;
    }
}

bool isZero(double num){
    return fabs(num) < EPS;
}

double discriminant(double a, double b, double c){
    return b * b - 4 * a * c;
}

int printQdrEqRoots(int QES_root_count, double x1, double x2){
    switch(QES_root_count){
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
        case ES_INF_ROOTS:{
            printf("Any number\n");
            break;
        }
        default:{
            printf("Error: nRoots = %d\n", QES_root_count);
            return 1;
        }
    }
    return 0;
}

bool strIsSpace(){
    char c;
    bool flag = 1;

    while ((c = getchar()) != '\n'){
        if (!isspace(c)) flag = 0;
    }
    return flag;
}

void dumpBuff(){
    char c;

    while ((c = getchar()) != '\n'){
        continue;
    }
}

int get_double(double* num){
    while (1){
        while (scanf("%lg", num) != 1){
            printf("This is not a number! Try 2.2 or 6\n");
            dumpBuff();
        }
        if (!strIsSpace()){
            printf("This is not a number! Try 2.2 or 6\n");
        }
        else{   // if (strIsSpace())
            return 0;
        }
    }
}

int get_coefs(double* a, double* b, double* c){
    printf("Enter a:\n");
    get_double(a);
    printf("Enter b:\n");
    get_double(b);
    printf("Enter c:\n");
    get_double(c);
    return 0;
}
