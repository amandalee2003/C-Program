//ss.c
#include "numtheory.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "randstate.h"
#include "ss.h"
#include <gmp.h>
//set the pbits with the given formula
//set qbits to the remainder
//make prime for p and q
//set n to p*p*q
void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    uint64_t p_bits = (random() % ((2 * nbits / 5) - (nbits / 5) + 1)) + (nbits / 5);
    uint64_t q_bits = nbits - (2 * p_bits);
    //uint64_t q_bits = p_bits-1;
    make_prime(p, p_bits, iters);
    make_prime(q, q_bits, iters);
    mpz_mul(n, p, p);
    mpz_mul(n, n, q);
}
//print out the n and username
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    gmp_fprintf(pbfile, "%Zx\n%s\n", n, username);
}
//read the n and username
void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    gmp_fscanf(pbfile, "%Zx\n%s\n", n, username);
}
//find the lcm of p-1 and q-1
//clear the mpz when done
void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    mpz_t return_value, p_lcm, n_temp, q_lcm, absolute_value, total_value;
    mpz_init(p_lcm);
    mpz_init(n_temp);
    mpz_init(absolute_value);
    mpz_init(q_lcm);
    mpz_sub_ui(p_lcm, p, 1);
    mpz_sub_ui(q_lcm, q, 1);
    mpz_init(total_value);
    mpz_mul(total_value, q_lcm, p_lcm);
    mpz_abs(absolute_value, total_value);
    gcd(return_value, p_lcm, q_lcm);
    mpz_fdiv_q(return_value, absolute_value, return_value);
    mpz_mul(pq, p, q);
    mpz_mul(n_temp, pq, p);
    mod_inverse(d, n_temp, return_value);
    mpz_clears(return_value, p_lcm, n_temp, absolute_value, q_lcm, total_value, NULL);
}
//print out the pq and d values
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", pq, d);
}
//read the pq and d values
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", pq, d);
}
//use power modulus of c,m,n,n to encrypt
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}
//while loop through fread which an ecrypted array using ss encrypt for one bit at a time, until the end of file is reached.
//print these encrypted values to the pbfile
void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    mpz_t m, c, n_temp;
    mpz_init_set(n_temp, n);
    mpz_inits(m, c, NULL);
    size_t k = (mpz_sizeinbase(n_temp, 2) / 2 - 1) / 8;
    uint8_t size = sizeof(uint8_t);
    uint8_t *encrypt_arr = (uint8_t *) calloc(k, size);
    encrypt_arr[0] = 0xff;
    size_t j;
    while ((j = fread(encrypt_arr + 1, size, k - 1, infile)) > 0) {
        mpz_import(m, j + 1, 1, size, 1, 0, encrypt_arr);
        ss_encrypt(c, m, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    }
    free(encrypt_arr);
    mpz_clears(m, c, n_temp, NULL);
}
//decrypt using pow mod of m,c,d,pq
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}
//while loop through fread which an derypted array using ss encrypt for one bit at a time, until         the end of file is reached.
//print these encrypted values to the pvfile
void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t pq, const mpz_t d) {
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    uint8_t size = sizeof(uint8_t);
    size_t log = mpz_sizeinbase(pq, 2);
    size_t k = log;
    k -= 1;
    k /= 8;
    size_t j = 0;
    uint8_t *decrypt_arr = (uint8_t *) calloc(k, size);
    decrypt_arr[0] = 0xff;
    while (!feof(infile)) {
        //size_t j = 0;
        gmp_fscanf(infile, "%Zx\n", c);
        ss_decrypt(m, c, d, pq);
        mpz_export(decrypt_arr, &j, 1, size, 1, 0, m);
        fwrite(decrypt_arr + 1, size, j - 1, outfile);
    }
    mpz_clears(m, c, NULL);
    free(decrypt_arr);
}
