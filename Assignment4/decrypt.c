//decrypt
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "ss.h"
#include <stdio.h>
#include "randstate.h"
#include <gmp.h>
#define OPTIONS "i:o:n:vh"
//main function with case files taking in user input or setting value to the default.
//fopen the files, or print an error message if needed
//if a non case file is called, print the help message
//the user input will take in a pb and pv file, the number of iters, and the numbers of bits to use in the other c file functions.
int main(int argc, char **argv) {
    int opt = 0;
    int v_flag = 0;
    int n_flag = 0;
    FILE *input = stdin;
    FILE *output = stdout;
    FILE *pvfile;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            input = fopen(optarg, "r"); //r????
            if (input == NULL) {
                printf("Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(input);
                return 1;
            }
            break;
        case 'o':
            output = fopen(optarg, "w");
            if (output == NULL) {
                printf("Failure opening the file(s), run ./keygen -H for more help.\n");
                fclose(output);
                return 1;
            }
            break;
        case 'n':
            pvfile = fopen(optarg, "r"); //r????????
            if (pvfile == NULL) {
                printf("Failure opening the file(s), run ./decrypt -h for more help.\n");
                fclose(pvfile);
                return 1;
            }
            n_flag = 1;
            break;
        case 'v': v_flag = 1; break;
        case 'h': //change to fit this assignment
            //INSERT SYNOPSIS HERE
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Encrypted data is encrypted by the encrypt program.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to decrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for decrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pvfile       Private key file (default: ss.priv).\n");
            return 1;
        default:
            //INSERT SYNOPSIS HERE
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Encrypted data is encrypted by the encrypt program.\n");
            fprintf(stderr, "\nUSAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n");
            fprintf(stderr, "\nOPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to decrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for decrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pvfile       Private key file (default: ss.priv).\n");
            return 1;
        }
    }
    //if the public file is provided, try to fopen and read, and if failure, print an error message.
    if (n_flag == 0) {
        pvfile = fopen("ss.priv", "r");
        if (pvfile == NULL) {
            printf("Failure opening the file(s), run ./decrypt -h for more help.\n");
            fclose(pvfile);
            return 1;
        }
    }
    mpz_t pq, d;
    mpz_inits(pq, d, NULL);
    ss_read_priv(pq, d, pvfile);
    //print out the verbose output if needed.
    //use size in base for log 2 for the bits portion
    if (v_flag == 1) {
        gmp_printf("pq (%zu bits) = %Zd\nd  (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq,
            mpz_sizeinbase(d, 2), d);
    }
    //decrypt the file
    //close and clear all other mpz and files as needed
    ss_decrypt_file(input, output, pq, d);
    fclose(pvfile);
    mpz_clears(pq, d, NULL);
    return 0;
}
