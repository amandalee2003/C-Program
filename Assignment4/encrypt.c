//encrypt.c
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "ss.h"
#include <time.h>
#include <stdio.h>
#include <gmp.h>
#include <sys/stat.h>
#include "randstate.h"
#include "numtheory.h"
#define OPTIONS "i:o:n:vh"
//make a main function with all of the needed case files
//use user input or the default cases if not called
//the acceptable user inputs include the pb and pv file, the number of iters and its
//the set seed is also given by time (NULL)
//fopen the needed files and print a failure message if needed
//print a help message if h is called, or a non case letter
int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pbfile;
    int v_flag = 0;
    int n_flag = 0;
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            infile = fopen(optarg, "r"); //r????
            if (infile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(infile);
                return 1;
            }
            break;
        case 'o':
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(outfile);
                return 1;
            }
            break;
        case 'n':
            pbfile = fopen(optarg, "r");
            if (pbfile == NULL) {
                fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(pbfile);
                return 1;
            }
            n_flag = 1;
            break;
        case 'v': v_flag = 1; break;
        case 'h':
            //INSERT SYNOPSIS HERE
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 1;
        default:
            //INSERT SYNOPSIS HERE
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 1;
        }
    } //check for the pb file and return a help message if it errors/fails to open
    //close the file and return 0 if needed
    if (n_flag == 0) {
        pbfile = fopen("ss.pub", "r");
        if (pbfile == NULL) {
            fprintf(stderr, "Failure opening the file(s), run ./keygen -H for more help.\n");
            fclose(pbfile);
            return 1;
        }
    }
    //set the user to a char 32
    //read the public file and return the n mpz
    //if the verbose flag is activated, print out the values
    //encrypt the file
    //fclose the files and clear the needed mpz variables
    mpz_t n;
    mpz_init(n);
    char user[32];
    ss_read_pub(n, user, pbfile);
    if (v_flag == 1) {
        fprintf(stderr, "user = %s\n", user);
        gmp_printf("n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
    }
    ss_encrypt_file(infile, outfile, n);
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);
    mpz_clear(n);

    return 0;
}
