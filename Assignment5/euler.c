//euler.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double terms;
double pi_euler(void) {
    double value = 1.0;
    double power = 1.0;
    double new_number = 1.0;
    double total = 1.0;
    double totals = 0;
    double previous_value = 0;
    double k;
    for (k = 1; absolute(total - previous_value) > EPSILON; k++) {
        previous_value = total;
        power = k * k;
        //set the power of k to 2 as k times k
        value = 1.0 / power;
        //since k is negative, divide 1/power
        totals += value;
        //add this value to a total variable
        terms += 1;
        total = sqrt_newton(6 * totals);
    }
    new_number = (6.0 * totals);
    //multiply the total value by 6
    double final_result = sqrt_newton(new_number);
    //sqrt this value to get pi
    return final_result;
}

int pi_euler_terms(void) {
    return terms;
    //return the static terms
}
