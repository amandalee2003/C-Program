//madhava.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double terms;

double pi_madhava(void) {
    double k = 0.0;
    double value = 0.0;
    double total = 1;
    double previous_value = 0;
    for (k = 0; absolute(total - previous_value) > EPSILON; k++) {
        //new minus previous is less than epsilon, the loop stops
        previous_value = k;
        previous_value = total;
        double x;
        double power = 1;
        for (x = 1; x <= k; ++x) {
            power = power * -3;
            //multiply the power by -3 every loop of the value of k
            //if k is 0, the power value of 1 is returned
        }
        power = 1 / power;
        //since k is negative, divide 1 over the power result
        value += power / ((2 * k) + 1);
        //set the value to the past values of power divided by 2k +1
        terms += 1;
        total = sqrt_newton(12) * value;
    }
    total = sqrt_newton(12) * value;
    //set the total to the square root of 12 and multiple that by the value
    return total;
}

int pi_madhava_terms(void) {
    return terms;
    //return the terms static value
}
