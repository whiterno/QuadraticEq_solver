#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "../useful/useful.h"
#include "QES_funcs.h"
#include "../in_out/in_out.h"
#include "../consts.h"
#include "../QES_structs.h"

static double discriminant(const double coef_a, const double coef_b, const double coef_c);
static int LinearEquationSolver(const double coef_a, const double coef_b, double* root);

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

static int LinearEquationSolver(const double coef_a, const double coef_b, double* root){
    assert(root != NULL);

    if (isZero(coef_a)){
        return (isZero(coef_b))? ES_INF_ROOTS : 0;
    }
    else{   // if (!isZero(a))
        *root = -coef_b / coef_a;
        return 1;
    }
}

static double discriminant(const double coef_a, const double coef_b, const double coef_c){
    return coef_b * coef_b - 4 * coef_a * coef_c;
}
