//encrypt.c
#include <string.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "rsa.h"
#include <time.h>
#include <stdio.h>
#include <gmp.h>
#include <sys/stat.h>
#include "randstate.h"
#include "numtheory.h"
#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv){
    //printf("in main\n");
    //printf("before file\n");
    //printf("after stdout");
    FILE *infile = stdin;
    FILE *outfile = stdout;
    //char input[256];
    //fgets(input,256,stdin);
    //printf("input is: %s\n",input);
    FILE *pbfile;
    //printf("after files");
    int v_flag = 0;
    int n_flag = 0;
    int opt=0;
    //int private_file = 0;
    while((opt=getopt(argc,argv,OPTIONS)) != -1){
        //printf("after encrypt while");
	switch(opt){
            case 'i':
		infile = fopen(optarg,"r");//r????
                if(infile == NULL){
                    fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(infile); 
		    return 1;
                 }break;
	    case 'o':
		outfile = fopen(optarg,"w");
                if(outfile == NULL){
                    fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(outfile); 
		    return 1;
                 }break;
	    case 'n':
		pbfile = fopen(optarg,"r");//r????????
                if(pbfile == NULL){
                    fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(pbfile); 
		    return 1;
                 }n_flag =1;
                break;
	    case 'v':
		v_flag = 1;
		break;
	    case 'h':
		//fprintf(stderr,"SYNOPSIS\n");
               /*	fprintf(stderr,"   A collection of encryption algorithms.\n\n");
                fprintf(stderr,"USAGE\n");
                fprintf(stderr,"   ./encrypt [-ionvh]\n\n");
                fprintf(stderr,"OPTIONS\n");
                fprintf(stderr,"   -i              specifies the input file to encrypt (default: stdin).\n");
                fprintf(stderr,"   -o              specifies the output file to encrypt (default: stdout).\n");
                fprintf(stderr,"   -n              specifies the file containing the public key (default: rsa.pub).\n");
                fprintf(stderr,"   -v              enables verbose output.\n");
                fprintf(stderr,"   -h              displays program synopsis and usage.\n");
                exit(-1); 
	*/	fprintf(stderr, "Usage: ./encrypt [options]\n");
                fprintf(stderr,"  ./encrypt encrypts an input file using the specified public key file,\n");
                fprintf(stderr,"  writing the result to the specified output file.\n");
                fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr,"    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n");
                fprintf(stderr,"    -v          : Enable verbose output.\n");
                fprintf(stderr,"    -h          : Display program synopsis and usage.\n");///4 spaces???
            	return 0;
	    default:
		fprintf(stderr, "Usage: ./encrypt [options]\n");
                fprintf(stderr,"  ./encrypt encrypts an input file using the specified public key file,\n");
                fprintf(stderr,"  writing the result to the specified output file.\n");
                fprintf(stderr,"    -i <infile> : Read input from <infile>. Default: standard input.\n");
                fprintf(stderr,"    -o <outfile>: Write output to <outfile>. Default: standard output.\n");
                fprintf(stderr,"    -n <keyfile>: Public key is in <keyfile>. Default: rsa.pub.\n");
                fprintf(stderr,"    -v          : Enable verbose output.\n");
                fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
		return 0;
	/*	fprintf(stderr,"SYNOPSIS\n");
                fprintf(stderr,"   A collection of encryption algorithms.\n\n");
                fprintf(stderr,"USAGE\n");
                fprintf(stderr,"   ./encrypt [-ionvh]\n\n");
                fprintf(stderr,"OPTIONS\n");
                fprintf(stderr,"   -i              specifies the input file to encrypt (default: stdin).\n");
                fprintf(stderr,"   -o              specifies the output file to encrypt (default: stdout).\n");
                fprintf(stderr,"   -n              specifies the file containing the public key (default: rsa.pub).\n");
                fprintf(stderr,"   -v              enables verbose output.\n");
                fprintf(stderr,"   -h              displays program synopsis and usage.\n");
                exit(-1);*/
	}}
    if(n_flag == 0){
        pbfile = fopen("rsa.pub", "r");//r?????
        if(pbfile == NULL){
            fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
            fclose(pbfile);
	    return 1;
        }}mpz_t n,e,s,username,d;
    mpz_inits(n,e,s,username,d,NULL);
    char user[32];
    //printf("before read pub");
    rsa_read_pub(n,e,s,user,pbfile);
    //printf("after read pub");
    //mpz_set_str(username,user,62);
    //rsa_read_pub(n,e,s,user,pbfile);
    if(v_flag == 1){
//	printf("username = %s\n",user);
	fprintf(stderr,"username: %s\n",user);
        gmp_printf("user signature (%zu bits): %Zd\nn - modulus (%zu bits): %Zd\ne - public exponent (%zu bits): %Zd\n", mpz_sizeinbase(s,2), s,mpz_sizeinbase(n,2), n, mpz_sizeinbase(e,2),e);
    }mpz_set_str(username,user,62);
    if(rsa_verify(username,s,e,n)==false){
        fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
        return 1;
    }//printf("\n");////////////////////////new line??
    rsa_encrypt_file(infile,outfile,n,e);
    fclose(pbfile);
    fclose(infile);
    fclose(outfile);
    mpz_clears(n,e,s,username,NULL);
    }
