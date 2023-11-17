//mathlib-test.c
#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#define OPTIONS "haebmrvns"

int main(int argc, char **argv) {
    int opt = 0;
    int a_flag = 0;
    int e_flag = 0;
    int b_flag = 0;
    int m_flag = 0;
    int r_flag = 0;
    int v_flag = 0;
    int n_flag = 0;
    int s_flag = 0;
    int h_flag = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            a_flag += 1;
            //this makes sure a has been called
            if (a_flag > 1) {
                break;
            }
        case 'e':
            e_flag += 1;
            //this makes sure e has been called
            if (a_flag == 0) {
                //if a is not called, then dont continue to next case automatically
                break;
            }
        case 'b':
            b_flag += 1;
            //this makes sure b has been called
            if (a_flag == 0) {
                //if a is not called, then dont continue to next case automatically
                break;
            }
        case 'm':
            m_flag += 1;
            //this makes sure m has been called
            if (a_flag == 0) {
                //if a is not called, then dont continue to next case automatically
                break;
            }
        case 'r':
            r_flag += 1;
            //this makes sure r has been called
            if (a_flag == 0) {
                //if a is not called, then dont continue to next case automatically
                break;
            }
        case 'v':
            v_flag += 1;
            //this makes sure v has been called
            if (a_flag == 0) {
                //if a is not called, then dont continue to next case automatically
                break;
            }
        case 'n':
            n_flag += 1;
            break;
            //this makes sure n has been called
        case 's': s_flag += 1; break;
        case 'h':
            h_flag = 1;
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library.\n");
            printf("USAGE\n");
            printf("   ./mathlib-test [-aebmrvnsh]\n");
            printf("OPTIONS\n");
            printf("  -a   Runs all tests.\n");
            printf("  -e   Runs e test.\n");
            printf("  -b   Runs BBP pi test.\n");
            printf("  -m   Runs Madhava pi test.\n");
            printf("  -r   Runs Euler pi test.\n");
            printf("  -v   Runs Viete pi test.\n");
            printf("  -n   Runs Newton square root tests.\n");
            printf("  -s   Print verbose statistics.\n");
            printf("  -h   Display program synopsis and usage.\n");
            return 0;
            break;
        default:
            h_flag = 1;
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library.\n");
            printf("USAGE\n");
            printf("   ./mathlib-test [-aebmrvnsh]\n");
            printf("OPTIONS\n");
            printf("  -a   Runs all tests.\n");
            printf("  -e   Runs e test.\n");
            printf("  -b   Runs BBP pi test.\n");
            printf("  -m   Runs Madhava pi test.\n");
            printf("  -r   Runs Euler pi test.\n");
            printf("  -v   Runs Viete pi test.\n");
            printf("  -n   Runs Newton square root tests.\n");
            printf("  -s   Print verbose statistics.\n");
            printf("  -h   Display program synopsis and usage.\n");
            return 0;
            break;
        }
    }
    //if nothing is called, then print a help message
    if (a_flag == 0 && e_flag == 0 && b_flag == 0 && m_flag == 0 && r_flag == 0 && v_flag == 0
        && n_flag == 0 && s_flag == 0 && h_flag == 0) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
        return 0;
    }
    //if the help flag is called, print help message, and return
    if (h_flag > 0) {
        printf("SYNOPSIS\n");
        printf("   A test harness for the small numerical library.\n");
        printf("USAGE\n");
        printf("   ./mathlib-test [-aebmrvnsh]\n");
        printf("OPTIONS\n");
        printf("  -a   Runs all tests.\n");
        printf("  -e   Runs e test.\n");
        printf("  -b   Runs BBP pi test.\n");
        printf("  -m   Runs Madhava pi test.\n");
        printf("  -r   Runs Euler pi test.\n");
        printf("  -v   Runs Viete pi test.\n");
        printf("  -n   Runs Newton square root tests.\n");
        printf("  -s   Print verbose statistics.\n");
        printf("  -h   Display program synopsis and usage.\n");
        return 0;
    }

    if (e_flag > 0) {
        double difference = absolute(M_E - e());
        //print out the value, math.h value, and the difference
        printf("e() = %1.15lf, M_E = %1.15lf, diff = %1.15lf\n", e(), M_E, difference);
        if (s_flag > 0) {
            //if the s flag was called, then print the terms too
            printf("e terms = %d\n", e_terms());
        }
    }

    if (r_flag > 0) {
        double difference = absolute(M_PI - pi_euler());
        //print out the value, math.h value, and the difference
        printf(
            "pi_euler() = %1.15lf, M_PI = %1.15lf, diff = %1.15lf\n", pi_euler(), M_PI, difference);
        if (s_flag > 0) {
            //if the s flag was called, then print the terms too
            printf("pi_euler terms = %d\n", pi_euler_terms());
        }
    }

    if (b_flag > 0) {
        double difference = absolute(M_PI - pi_bbp());
        //print out the value, math.h value, and the difference
        printf("pi_bbp() = %1.15lf, M_PI = %1.15lf, diff = %1.15lf\n", pi_bbp(), M_PI, difference);
        if (s_flag > 0) {
            //if the s flag was called, then print the terms too
            printf("pi_bbp terms = %d\n", pi_bbp_terms());
        }
    }

    if (m_flag > 0) {
        double difference = absolute(M_PI - pi_madhava());
        //print out the value, math.h value, and the difference
        printf("pi_madhava() = %1.15lf, M_PI %1.15lf, diff = %1.15lf\n", pi_madhava(), M_PI,
            difference);
        if (s_flag > 0) {
            //if the s flag was called, then print the terms too
            printf("pi_madhava terms = %d\n", pi_madhava_terms());
        }
    }

    if (v_flag > 0) {
        double difference = absolute(M_PI - pi_viete());
        //print out the value, math.h value, and the difference
        printf(
            "pi_viete() = %1.15lf, M_PI = %1.15lf, diff = %1.15lf\n", pi_viete(), M_PI, difference);
        if (s_flag > 0) {
            //if the s flag was called, then print the terms too
            printf("pi_viete terms = %d\n", pi_viete_factors());
        }
    }

    if (n_flag > 0) {
        for (double x = 0; x < 10; x += 0.1) {
            //for loop through the values 0-10
            //print out the value, math.h value, and the difference
            double difference = absolute(sqrt(x) - sqrt_newton(x));
            printf("sqrt_newton(%f) = %1.15lf, sqrt(%f) = %1.15lf, diff %1.15lf\n", x,
                sqrt_newton(x), x, sqrt(x), difference);
            if (s_flag > 0) {
                //if the s flag was called, then print the terms too
                printf("sqrt_newton %d\n", sqrt_newton_iters());
            }
        }
    }

    return 0;
}
