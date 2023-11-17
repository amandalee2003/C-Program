#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <stdbool.h>
#include <gmp.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
//craete a function that will find the greatest common divisor.
//use mpz modulus and compare to do so
void gcd(mpz_t g, const mpz_t a, const mpz_t b) {
    mpz_t b_value, a_value, t_value;
    mpz_init_set(b_value, b);
    mpz_init_set(a_value, a);
    while (mpz_cmp_ui(b_value, 0) != 0) {
        mpz_init_set(t_value, b_value);
        mpz_mod(b_value, a_value, b_value);
        mpz_set(a_value, t_value);
        mpz_clear(t_value);
    }
    mpz_init_set(g, a_value);
    mpz_clears(b_value, a_value, NULL);
}
//create a pow mod function
//use compares, odd, multiply, modulus, and floor divison to accomplish this.
void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {
    mpz_t v_value, p_value, e_value;
    mpz_init_set_ui(v_value, 1);
    mpz_init_set(p_value, a);
    mpz_init_set(e_value, d);
    while (mpz_cmp_ui(e_value, 0) > 0) {
        if (mpz_odd_p(e_value) != 0) {
            mpz_mul(v_value, v_value, p_value);
            mpz_mod(v_value, v_value, n);
        }
        mpz_mul(p_value, p_value, p_value);
        mpz_mod(p_value, p_value, n);
        mpz_fdiv_q_ui(e_value, e_value, 2);
    }
    mpz_set(o, v_value);
    mpz_clears(v_value, p_value, e_value, NULL);
}
//use the mpz commands such as floor division, multiply, subtract, and comapre in order to create a modulus inverse function to use in ss.c to encrypt and decrypt
void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    mpz_t t_value, t_prime, r_value, r_prime;
    mpz_init_set_ui(t_prime, 1);
    mpz_init_set(r_value, n);
    mpz_init_set(r_prime, a);
    mpz_init_set_ui(t_value, 0);
    while (mpz_cmp_ui(r_prime, 0) != 0) {
        mpz_t var_one, var_two, r_temp, r_replace, t_temp, q_value, t_replace;
        mpz_init_set(r_replace, r_prime);
        mpz_init_set(r_temp, r_value);
        mpz_init_set(t_replace, t_prime);
        mpz_init_set(t_temp, t_value);
        mpz_init_set_ui(q_value, 0);
        mpz_fdiv_q(q_value, r_value, r_prime);
        mpz_init_set(r_value, r_replace);
        mpz_init_set_ui(var_one, 0);
        mpz_init_set_ui(var_two, 0);
        mpz_mul(var_one, q_value, r_replace);
        mpz_sub(r_prime, r_temp, var_one);
        mpz_init_set(t_value, t_prime);
        mpz_mul(var_two, q_value, t_replace);
        mpz_sub(t_prime, t_temp, var_two);
        mpz_clears(var_one, var_two, r_replace, r_temp, q_value, t_replace, t_temp, NULL);
    }
    if (mpz_cmp_ui(r_value, 1) > 0) {
        mpz_init_set_ui(t_value, 0);
    }
    if (mpz_cmp_ui(t_value, 0) < 0) {
        mpz_add(t_value, t_value, n);
    }
    mpz_init_set(o, t_value);
    mpz_clears(t_value, r_value, r_prime, t_prime, NULL);
}
//check if a number is prime with the given number to check as well as the iters to loop through (in some cases this will be a default number)
bool is_prime(const mpz_t n, uint64_t iters) {
    if (mpz_cmp_ui(n, 2) < 0) { //hard code for a number less than 2 to be false
        return false;
    }
    if (mpz_cmp_ui(n, 2) == 0) { //if the number is 2, then it is prime
        return true;
    }
    if (mpz_cmp_ui(n, 3) == 0) {
        return true;
    }
    if (mpz_even_p(n)) { //if the number is even, then it is prime
        return false;
    }
    mpz_t s, r, a, two, n_temp, temp, temp_mod;
    mpz_init_set(n_temp, n);
    mpz_sub_ui(n_temp, n_temp, 1);
    mpz_init_set_ui(two, 2);
    mpz_init_set_ui(s, 0);
    mpz_init(a);
    mpz_init_set_ui(r, 0);
    mpz_init_set(temp, n_temp);
    mpz_init_set_ui(temp_mod, 0);
    mpz_t minus_three;
    mpz_init_set(minus_three, n);
    mpz_mod_ui(temp_mod, n_temp, 2);
    while (mpz_cmp_ui(temp_mod, 1) != 0) {
        mpz_add_ui(s, s, 1);
        mpz_fdiv_q_ui(n_temp, n_temp, 2);
        mpz_mod_ui(temp_mod, n_temp, 2);
    }
    mpz_set(r, n_temp);
    for (uint64_t i = 1; i <= iters; i++) { //loop through the given iters value
        mpz_sub(minus_three, minus_three, two);
        mpz_urandomm(a, state, minus_three);
        mpz_add(a, a, two);
        mpz_t y;
        mpz_init(y);
        pow_mod(y, a, r, n);
        if ((mpz_cmp_ui(y, 1) != 0) && (mpz_cmp(y, temp)) != 0) {
            mpz_t j, s_minus;
            mpz_init_set(s_minus, s);
            mpz_sub_ui(s_minus, s_minus, 1);
            mpz_init_set_ui(j, 1);
            while (mpz_cmp(j, s_minus) <= 0 && mpz_cmp(y, temp) != 0) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(s, r, a, n_temp, two, y, j, s_minus, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, temp) != 0) {
                mpz_clears(s, j, r, a, n_temp, two, y, s_minus, NULL);
                return false;
            }
            mpz_clear(j);
        }
        mpz_clear(y);
    }
    mpz_clears(s, r, a, n_temp, two, NULL);
    return true;
}
//use urandomb and state from randstate to create a number that is prime to use for keygen
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_urandomb(p, state, bits);
    while ((is_prime(p, iters) == false) || (mpz_sizeinbase(p, 2) < bits)) {
        mpz_urandomb(p, state, bits);
    }
}
