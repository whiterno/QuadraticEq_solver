#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "tests.h"


void QuadraticEquationSolver(const struct QuadraticEquationCoef* pnt_QEC, struct QuadraticEquationSol* pnt_QES);
bool isZero(const double num);
double discriminant(const double coef_a, const double coef_b, const double coef_c);
int LinearEquationSolver(const double coef_a, const double coef_b, double* root);
int printQdrEqRoots(const struct QuadraticEquationSol* pnt_eq);
int get_double(double* num);
void clearBuff();
int get_coefs(struct QuadraticEquationCoef* pnt_QEC);
int runTest(const int serial_num);
int checkTest(const int serial_num, const struct QuadraticEquationSol* roots);
void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots);
void runAllTests();
void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots);
int checkArgs(const int argc, char* argv[]);
void printArgs(const int argc, char* argv[]);

const double EPS = 0.0001;
enum Terminal_input_results{
    HELP,
    MANUAL_SCAN,
    UNIT_TESTING,
    TERMINAL_ERROR
};

int main(int argc, char* argv[]){
    int check_res = checkArgs(argc, argv);

    switch(check_res){
        case HELP:{
            break;
        }
        case MANUAL_SCAN:{
            printf("Quadratic Equation solver\n\n");
            struct QuadraticEquationCoef coefs;
            get_coefs(&coefs);

            struct QuadraticEquationSol equation;
            QuadraticEquationSolver(&coefs, &equation);
            printQdrEqRoots(&equation);
            break;
        }
        case UNIT_TESTING:{
            runAllTests();
            break;
        }
        case TERMINAL_ERROR:{
            printf("Commamd not found: ");
            printArgs(argc, argv);
        }
    }
    return 0;
}

void QuadraticEquationSolver(const struct QuadraticEquationCoef* coefs, struct QuadraticEquationSol* sol){
    assert(coefs != NULL);
    assert(sol != NULL);

    if (isZero(coefs->coef_a)){
        int LES_root_count = LinearEquationSolver(coefs->coef_b, coefs->coef_c, &sol->root1);
        sol->root2 = sol->root1;
        sol->QES_root_count = LES_root_count;
    }
    else{   // if (!isZero(a))
        double d = discriminant(coefs->coef_a, coefs->coef_b, coefs->coef_c);
        if (isZero(d)){
            sol->root1 = -coefs->coef_b / (2 * coefs->coef_a);
            sol->root2 = -coefs->coef_b / (2 * coefs->coef_a);
            sol->QES_root_count = 1;
        }
        else if (d > 0){
            double sqrt_d = sqrt(d);
            sol->root1 = (-coefs->coef_b + sqrt_d) / (2 * coefs->coef_a);
            sol->root2 = (-coefs->coef_b - sqrt_d) / (2 * coefs->coef_a);
            sol->QES_root_count = 2;
        }
        else{   // if (d < 0)
            sol->QES_root_count = 0;
        }
    }
}

int LinearEquationSolver(const double coef_a, const double coef_b, double* root){
    assert(root != NULL);

    if (isZero(coef_a)){
        return (isZero(coef_b))? ES_INF_ROOTS : 0;
    }
    else{   // if (!isZero(a))
        *root = -coef_b / coef_a;
        return 1;
    }
}

bool isZero(const double num){
    return fabs(num) < EPS;
}

double discriminant(const double coef_a, const double coef_b, const double coef_c){
    return coef_b * coef_b - 4 * coef_a * coef_c;
}

int printQdrEqRoots(const struct QuadraticEquationSol* sol){
    assert(sol != NULL);

    switch(sol->QES_root_count){
        case 0:{
            printf("Equation has no roots\n");
            break;
        }
        case 1:{
            printf("Equation has 1 root: x = %lg\n", sol->root1);
            break;
        }
        case 2:{
            printf("Equation has 2 roots: x1 = %lg, x2 = %lg\n", sol->root1, sol->root2);
            break;
        }
        case ES_INF_ROOTS:{
            printf("The root of the equation is any number\n");
            break;
        }
        default:{
            printf("Error: nRoots = %d\n", sol->QES_root_count);
            return 1;
        }
    }
    return 0;
}

bool strIsSpace(){
    int character = 0;
    bool flag = true;

    while ((character = getchar()) != '\n' && character != EOF){
        if (!isspace(character)) flag = false;
    }
    return flag;
}

void clearBuff(){
    int character;

    while ((character = getchar()) != '\n' && character != EOF){
        continue;
    }
}

int get_double(double* num){
    assert(num != NULL);

    while (true){
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

int get_coefs(struct QuadraticEquationCoef* coefs){
    assert(coefs != NULL);

    printf("Enter a:\n");
    get_double(&coefs->coef_a);
    printf("Enter b:\n");
    get_double(&coefs->coef_b);
    printf("Enter c:\n");
    get_double(&coefs->coef_c);
    return 0;
}

int runTest(const int serial_num){
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    struct QuadraticEquationSol roots = {0, 0, 0};

    QuadraticEquationSolver(&TESTS[serial_num].coefs, &roots);

    int result = checkTest(serial_num, &roots);
    printTestResult(result, serial_num, &roots);
    return result;
}

int checkTest(const int serial_num, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    if (roots->QES_root_count == TESTS[serial_num].sol.QES_root_count){
        if (roots->root1 == TESTS[serial_num].sol.root1 && roots->root2 == TESTS[serial_num].sol.root2){
            return SOLUTION_SUCCESS;
        }
        if(roots->root1 == TESTS[serial_num].sol.root2 && roots->root2 == TESTS[serial_num].sol.root1){
            return SOLUTION_SUCCESS;
        }
    }
    return SOLUTION_ERROR;
}

void printTestResult(const int result, const int serial_num, const struct QuadraticEquationSol* roots){
    assert(roots != NULL);
    assert((serial_num >= 0) && (serial_num < TEST_AMOUNT));

    switch (result){
        case SOLUTION_SUCCESS: {
            printf("Test %d: successful!\n", serial_num + 1);
            break;
        }
        case SOLUTION_ERROR: {
            printSolutionError(serial_num, roots);
            break;
        }
        default:{
            printf("Unknown ERROR!\n");
        }
    };
}

void runAllTests(){
    for(int test_count = 0; test_count < TEST_AMOUNT; test_count++){
        runTest(test_count);
    }
}

void printSolutionError(const int serial_num, const struct QuadraticEquationSol* roots){
    printf("Test %d: ERROR\n", serial_num + 1);
    printf("Test coefficients: a = %lg, b = %lg, c = %lg\n",
    TESTS[serial_num].coefs.coef_a, TESTS[serial_num].coefs.coef_b, TESTS[serial_num].coefs.coef_c);
    printf("Got result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    roots->QES_root_count, roots->root1, roots->root2);
    printf("Expected result: nRoot = %d, root1 = %lg, root2 = %lg\n",
    TESTS[serial_num].sol.QES_root_count, TESTS[serial_num].sol.root1, TESTS[serial_num].sol.root2);
}

int checkArgs(const int argc, char* argv[]){
    if (argc == 1){
        return MANUAL_SCAN;
    }
    if (argc == 2 && strcmp(argv[1], "--help") == 0){
        printf("For manual scanning: ./a.out -m 0\n");
        printf("For Unit Testing: ./a.out -m 1\n");
        return HELP;
    }
    if (argc == 3 && strcmp(argv[1], "-m") == 0){
        if (strcmp(argv[2], "0") == 0){
            return MANUAL_SCAN;
        }
        if (strcmp(argv[2], "1") == 0){
            return UNIT_TESTING;
        }
        return TERMINAL_ERROR;
    }
    return TERMINAL_ERROR;
}

void printArgs(const int argc, char* argv[]){
    for (int arg = 0; arg < argc; arg++){
        printf("%s ", argv[arg]);
    }
    printf("\n");
}
