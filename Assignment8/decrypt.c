//decrypt.c
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "rsa.h"
#include <stdio.h>
#include "randstate.h"
#include <gmp.h>
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv){
    int opt=0;
    int v_flag = 0;
    int n_flag =0;
    FILE *input = stdin;
    FILE *output = stdout;
    FILE *pvfile;
    while((opt=getopt(argc,argv,OPTIONS)) != -1){
        switch(opt){
	    case 'i':
                input = fopen(optarg,"r");//r????
                if(input == NULL){
                    printf("Failure opening the file(s), run ./keygen -H for more help.\n");
		    fclose(input);
                    return 0;
                 }break;
            case 'o':
                output = fopen(optarg,"w");
                if(output == NULL){
                    printf("Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(output); 
		    return 0;
                 }break;
            case 'n':
                pvfile = fopen(optarg,"r");//r????????
                if(pvfile == NULL){
                    printf("Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(pvfile); 
		    return 0;
                 }n_flag =1;
                break;
            case 'v':
		v_flag = 1;
		break;
		//gmp_fprintf(stderr,"%d\n%d\n",n,d);
            case 'h': //change to fit this assignment
		fprintf(stderr, "Usage: ./decrypt [options]\n");
                fprintf(stderr,"  ./decrypt decrypts an input file using the specified private key file,\n");
                fprintf(stderr,"  writing the result to the specified output file.\n");
                fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr,"    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n");
                fprintf(stderr,"    -v          : Enable verbose output.\n");
                fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
                return 0;

              /*  printf("SYNOPSIS\n");
                printf("   A collection of decryption algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./encrypt [-ionvh]\n\n");
                printf("OPTIONS\n");
                printf("   -i              specifies the input file to decrypt (default: stdin).\n");
                printf("   -o              specifies the output file to decrypt (default: stdout).\n");
                printf("   -n              specifies the file containing the public key (default: rsa.priv).\n");
                printf("   -v              enables verbose output.\n");
                printf("   -h              displays program synopsis and usage.\n");
                return 0;*/
            default:
		fprintf(stderr, "Usage: ./decrypt [options]\n");
                fprintf(stderr,"  ./decrypt decrypts an input file using the specified private key file,\n");
                fprintf(stderr,"  writing the result to the specified output file.\n");
                fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr,"    -n <keyfile>: Private key is in <keyfile>. Default: rsa.priv.\n");
                fprintf(stderr,"    -v          : Enable verbose output.\n");
                fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
                return 0;
               /* printf("SYNOPSIS\n");
                printf("   A collection of decryption algorithms.\n\n");
                printf("USAGE\n");
                printf("   ./encrypt [-ionvh]\n\n");
                printf("OPTIONS\n");
                printf("   -i              specifies the input file to decrypt (default: stdin).\n");
                printf("   -o              specifies the output file to decrypt (default: stdout).\n");
                printf("   -n              specifies the file containing the public key (default: rsa.priv).\n");
                printf("   -v              enables verbose output.\n");
                printf("   -h              displays program synopsis and usage.\n");
                return 1;*/
        }}
    if(n_flag ==0){
	pvfile = fopen("rsa.priv","r");
        if(pvfile == NULL){
	printf("Failure opening the file(s), run ./keygen -H for more help.\n");
        fclose(pvfile);
	return 0;
    }}mpz_t n,d;
    mpz_inits(n,d,NULL);
    rsa_read_priv(n,d,pvfile);
    if(v_flag == 1){
        gmp_printf("n (%zu bits) = %Zd\ne (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n, mpz_sizeinbase(d, 2), d);
    }rsa_decrypt_file(input,output,n,d);
    fclose(pvfile);
    mpz_clears(n,d,NULL);
}

