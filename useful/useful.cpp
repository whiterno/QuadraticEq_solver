#include <stdio.h>
#include <math.h>
#include "useful.h"
#include "../consts.h"

bool isZero(const double num){
    return fabs(num) < EPS;
}

bool fequal(const double num1, const double num2){
    if (fabs(num1 - num2) < EPS){
        return true;
    }
    return false;
}
