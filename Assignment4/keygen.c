//keygen
#include <string.h>
#include <sys/stat.h>
#include <gmp.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "randstate.h"
#include "numtheory.h"
#include "ss.h"
#define OPTIONS "b:i:n:d:s:vh"
//make a main function with all of the needed case files
//use user input or the default cases if not called
//the acceptable user inputs include the pb and pv file, the number of iters and its
//the set seed is also given by time (NULL)
//fopen the needed files and print a failure message if needed
//print a help message if h is called, or a non case letter
int main(int argc, char **argv) {
    int opt = 0;
    int v_flag = 0;
    int n_flag = 0;
    int d_flag = 0;
    uint64_t min_bits = 256;
    uint64_t num_is_prime = 50;
    FILE *pbfile;
    FILE *pvfile;
    uint64_t seed = time(NULL);
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': min_bits = strtoul(optarg, NULL, 10); break;
        case 'i': num_is_prime = strtoul(optarg, NULL, 10); break;
        case 'n':
            pbfile = fopen(optarg, "w");
            if (pbfile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(pbfile);
                return 1;
            }
            n_flag = 1;
            break;
        case 'd':
            pvfile = fopen(optarg, "w");
            if (pvfile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(pvfile);
                return 1;
            }
            d_flag = 1;
            //int fpriv = fileno(pvfile);
            //fchmod(fpriv, S_IRUSR | S_IWUSR); //int fd = fileno(pvfile);
            break;
        case 's': seed = strtoul(optarg, NULL, 10); break;
        case 'v': v_flag = 1; break;
        case 'h':
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr,
                "   -b bits         Minimum bits needed for public key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 1;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr,
                "   -b bits         Minimum bits needed for public key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 1;
        }
    }
    //check for the pb file and return a help message if it errors/fails to open
    //close the file and return 0 if needed
    if (n_flag == 0) {
        pbfile = fopen("ss.pub", "w");
        if (pbfile == NULL) {
            fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
            fclose(pbfile);
            return 1;
        }
    }
    //check for the pv file and return a help message if it errors/fails to open
    //close the file and return 0 if needed
    if (d_flag == 0) {
        pvfile = fopen("ss.priv", "w");
        if (pvfile == NULL) {
            fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
            fclose(pvfile);
            return 1;
        }
    }
    //get the permission codes to read and write
    //get a random number with the random seed set earlier
    //make the private and public keys
    //write to these public and private files
    //print the verbose if needed
    //fclose the files and clear the mpz variables as needed
    int private_file = fileno(pvfile);
    fchmod(private_file, S_IRUSR | S_IWUSR);
    randstate_init(seed);
    mpz_t p, q, n, pq, d;
    mpz_inits(q, p, n, pq, d, NULL);
    ss_make_pub(p, q, n, min_bits, num_is_prime); //took e out
    mpz_mul(pq, p, q);
    ss_make_priv(d, pq, p, q);
    char *user;
    user = getenv("USER");
    ss_write_pub(n, user, pbfile);
    ss_write_priv(pq, d, pvfile); //n,d,pvfile
    if (v_flag == 1) {
        gmp_printf("user = %s\np  (%zu bits) = %Zd\nq  (%zu bits) = %Zd\nn  (%zu bits) = %Zd\npq "
                   "(%zu bits) = %Zd\nd  (%zu bits) = %Zd\n",
            user, mpz_sizeinbase(p, 2), p, mpz_sizeinbase(q, 2), q, mpz_sizeinbase(n, 2), n,
            mpz_sizeinbase(pq, 2), pq, mpz_sizeinbase(d, 2), d);
    }
    fclose(pvfile);
    fclose(pbfile);
    randstate_clear(); //state??
    mpz_clears(p, q, n, pq, d, NULL);
    return 0;
}
