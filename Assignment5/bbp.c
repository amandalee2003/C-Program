//bbp.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double terms;

double pi_bbp(void) {
    double k = 0.0;
    double total = 0.0;
    double previous_value = -1;
    double sub1, sub2, sub3, sub4, sub;
    for (k = 0; absolute(total - previous_value) > EPSILON; k++) {
        previous_value = k;
        previous_value = total;
        //set the previous value to the old current value
        double x;
        double power = 1;
        for (x = 1; x <= k; ++x) {
            power = power * 16;
            //set the power value to multiple by 16 based on the for loop of the current number of k
        }
        power = 1 / power;
        //since k is negative, divide 1/power
        terms += 1;
        sub1 = 4 / ((8 * k) + 1);
        sub2 = 2 / ((8 * k) + 4);
        sub3 = 1 / ((8 * k) + 5);
        sub4 = 1 / ((8 * k) + 6);
        //set all the subtraction values to a different variable
        sub = sub1 - sub2 - sub3 - sub4;
        //subtract all these values to one another
        total += (power * sub);
        //add them to a total counter
    }
    return total;
}

int pi_bbp_terms(void) {
    return terms;
    //return the static value
}
