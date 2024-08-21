#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>

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


struct QuadraticEquationSol{
    int QES_root_count;
    double root1, root2;
};

struct QuadraticEquationCoef{
    double coef_a, coef_b, coef_c;
};

struct Test{
    struct QuadraticEquationCoef coefs;
    struct QuadraticEquationSol sol;
};

const int ES_INF_ROOTS = -1;
const double EPS = 0.0001;
const int TEST_AMOUNT = 11;
const struct Test TESTS[TEST_AMOUNT] = {
        {.coefs = {.coef_a = 0, .coef_b = 0, .coef_c = 0}, .sol = {.QES_root_count = ES_INF_ROOTS, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 0, .coef_b = 0, .coef_c = 1}, .sol = {.QES_root_count = 0, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 0, .coef_b = 1, .coef_c = 0}, .sol = {.QES_root_count = 1, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 0, .coef_b = 1, .coef_c = 1}, .sol = {.QES_root_count = 1, .root1 = -1, .root2 = -1}},
        {.coefs = {.coef_a = 0, .coef_b = 0, .coef_c = 1.2}, .sol = {.QES_root_count = 0, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 0, .coef_b = 1.2, .coef_c = 0}, .sol = {.QES_root_count = 1, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 0, .coef_b = 1.2, .coef_c = 4.8}, .sol = {.QES_root_count = 1, .root1 = -4, .root2 = -4}},
        {.coefs = {.coef_a = 4, .coef_b = -4, .coef_c = 1}, .sol = {.QES_root_count = 1, .root1 = 0.5, .root2 = 0.5}},
        {.coefs = {.coef_a = 1, .coef_b = -2, .coef_c = -15}, .sol = {.QES_root_count = 2, .root1 = -3, .root2 = 5}},
        {.coefs = {.coef_a = 1, .coef_b = 2, .coef_c = 10}, .sol = {.QES_root_count = 0, .root1 = 0, .root2 = 0}},
        {.coefs = {.coef_a = 1, .coef_b = 7, .coef_c = 10}, .sol = {.QES_root_count = 2, .root1 = -2, .root2 = -5}}
    };
enum Test_results{
    SOLUTION_SUCCESS,
    SOLUTION_ERROR
};

int main(void){
    printf("Quadratic Equation solver\n\n");

//     struct QuadraticEquationCoef coefs;
//     get_coefs(&coefs);
//
//     struct QuadraticEquationSol equation;
//     QuadraticEquationSolver(&coefs, &equation);
//     printQdrEqRoots(&equation);

    runAllTests();

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
        else if(roots->root1 == TESTS[serial_num].sol.root2 && roots->root2 == TESTS[serial_num].sol.root1){
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
            printf("Test %d: ERROR\n", serial_num + 1);
            printf("Test coefficients: a = %lg, b = %lg, c = %lg\n",
            TESTS[serial_num].coefs.coef_a, TESTS[serial_num].coefs.coef_b, TESTS[serial_num].coefs.coef_c);
            printf("Got result: nRoot = %d, root1 = %lg, root2 = %lg\n",
            roots->QES_root_count, roots->root1, roots->root2);
            printf("Expected result: nRoot = %d, root1 = %lg, root2 = %lg\n",
            TESTS[serial_num].sol.QES_root_count, TESTS[serial_num].sol.root1, TESTS[serial_num].sol.root2);
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
