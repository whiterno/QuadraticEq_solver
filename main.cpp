#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

const int ES_INF_ROOTS = -1;
const double EPS = 0.0001;

int QuadraticEquationSolver(double coef_a, double coef_b, double coef_c,
                            double* root1, double* root2);
bool isZero(double num);
double discriminant(double coef_a, double coef_b, double coef_c);
int LinearEquationSolver(double coef_a, double coef_b, double* root);
int printQdrEqRoots(struct QuadraticEquation* pnt_eq);
int get_double(double* num);
void clearBuff();
int get_coefs(double* coef_a, double* coef_b, double* coef_c);

struct QuadraticEquation{
    double root1, root2;
    int QES_root_count;
};

int main(void){
    printf("Quadratic Equation solver\n\n");

    double coef_a = 0, coef_b = 0, coef_c = 0;
    get_coefs(&coef_a, &coef_b, &coef_c);

    struct QuadraticEquation equation;
    equation.QES_root_count = QuadraticEquationSolver(coef_a, coef_b, coef_c,
                                                      &equation.root1, &equation.root2);

    struct QuadraticEquation* pnt_eq = &equation;
    printQdrEqRoots(pnt_eq);

    return 0;
}

int QuadraticEquationSolver(double coef_a, double coef_b, double coef_c, double* root1, double* root2){
    assert(isfinite(coef_a));
    assert(isfinite(coef_b));
    assert(isfinite(coef_c));

    assert(root1 != NULL);
    assert(root2 != NULL);
    assert(root1 != root2);

    if (isZero(coef_a)){
        int LES_root_count = LinearEquationSolver(coef_b, coef_c, root1);
        *root2 = *root1;
        return LES_root_count;
    }
    else{   // if (!isZero(a))
        double d = discriminant(coef_a, coef_b, coef_c);
        if (isZero(d)){
            *root1 = -coef_b / (2 * coef_a);
            *root2 = -coef_b / (2 * coef_a);
            return 1;
        }
        else if (d > 0){
            double sqrt_d = sqrt(d);
            *root1 = (-coef_b + sqrt_d) / (2 * coef_a);
            *root2 = (-coef_b - sqrt_d) / (2 * coef_a);
            return 2;
        }
        else{   // if (d < 0)
            return 0;
        }
    }
}

int LinearEquationSolver(double coef_a, double coef_b, double* root){
    assert(root != NULL);

    if (isZero(coef_a)){
        return (isZero(coef_b))? ES_INF_ROOTS : 0;
    }
    else{   // if (!isZero(a))
        *root = -coef_b / coef_a;
        return 1;
    }
}

bool isZero(double num){
    return fabs(num) < EPS;
}

double discriminant(double coef_a, double coef_b, double coef_c){
    return coef_b * coef_b - 4 * coef_a * coef_c;
}

int printQdrEqRoots(struct QuadraticEquation* pnt_eq){
    switch(pnt_eq->QES_root_count){
        case 0:{
            printf("Equation has no roots\n");
            break;
        }
        case 1:{
            printf("Equation has 1 root: x = %lg\n", pnt_eq->root1);
            break;
        }
        case 2:{
            printf("Equation has 2 roots: x1 = %lg, x2 = %lg\n", pnt_eq->root1, pnt_eq->root2);
            break;
        }
        case ES_INF_ROOTS:{
            printf("The root of the equation is any number\n");
            break;
        }
        default:{
            printf("Error: nRoots = %d\n", pnt_eq->QES_root_count);
            return 1;
        }
    }
    return 0;
}

bool strIsSpace(){
    int c;
    bool flag = 1;

    while ((c = getchar()) != '\n' && c != EOF){
        if (!isspace(c)) flag = 0;
    }
    return flag;
}

void clearBuff(){
    int c;

    while ((c = getchar()) != '\n' && c != EOF){
        continue;
    }
}

int get_double(double* num){
    assert(num != NULL);

    while (1){
        while (scanf("%lg", num) != 1){
            printf("This is not a number! Try 2.2 or 6\n");
            clearBuff();
        }
        if (!strIsSpace()){
            printf("This is not a number! Try 2.2 or 6\n");
        }
        else{   // if (strIsSpace())
            return 0;
        }
    }
}

int get_coefs(double* coef_a, double* coef_b, double* coef_c){
    assert(coef_a != NULL);
    assert(coef_b != NULL);
    assert(coef_c != NULL);

    printf("Enter a:\n");
    get_double(coef_a);
    printf("Enter b:\n");
    get_double(coef_b);
    printf("Enter c:\n");
    get_double(coef_c);
    return 0;
}
