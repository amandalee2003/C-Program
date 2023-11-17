//rsa.c
#include <string.h>
#include "numtheory.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>
#include <stdlib.h>
#include "randstate.h"
#include "rsa.h"
#include <gmp.h>

void rsa_sign(mpz_t s, mpz_t m, mpz_t d, mpz_t n){
    pow_mod(s,m,d,n);
}

bool rsa_verify(mpz_t m, mpz_t s, mpz_t e, mpz_t n){
    mpz_t t;
    mpz_init_set_ui(t,0);
    pow_mod(t,s,e,n);
    if(mpz_cmp(t,m)==0){
	mpz_clear(t);
	return true;
    }else{
	mpz_clear(t);
	return false;
    }}

void rsa_make_pub(mpz_t p, mpz_t q, mpz_t n, mpz_t e, uint64_t nbits, uint64_t iters){
    mpz_t result_val, absolute_val;
    //mpz_init_set_ui(e,0);
    //mpz_init_set_ui(n,0);
    //mpz_init(test);
    //uint64_t rand = random();
    //uint64_t equation = ((3*nbits)/4)+1;
    //printf("n bits is: %lu\n",nbits);
    //printf("(3*nbits)/4)+1 is %lu\n",equation);
    //printf("printing random() %lu\n",rand);
    //uint64_t p_bits = (rand % (((3*nbits)/4)+1)-(nbits/4));
    uint64_t p_bits = (random() % ((3*nbits)/4)-(nbits/4)+1)+(nbits/4);
    uint64_t q_bits = nbits-p_bits;
    //printf("p_bits -s: %lu\nq_bits is: %lu\n", p_bits,q_bits);
    mpz_init_set_ui(absolute_val,0);
    mpz_init_set_ui(result_val,0);
    //printf("before both make primes\n");
    make_prime(p,p_bits,iters);
    //printf("after make prime 1\n");
    make_prime(q,q_bits,iters);
    //printf("after make prime 2 and before mul 1\n");
    //gmp_printf("p start: %Zd\nq start: %Zd\n", p,q);
    mpz_mul(n,p,q);
    mpz_t return_val, p_math, q_math,total_val;
    mpz_init_set_ui(p_math,0);
    mpz_init_set_ui(total_val,0);
    mpz_init_set_ui(q_math,0);
    mpz_sub_ui(p_math, p,1);
    mpz_sub_ui(q_math,q,1);
    mpz_mul(total_val,q_math,p_math);
    mpz_abs(absolute_val,total_val);
    gcd(return_val,p_math,q_math);
    //mpz_gcd(test, p_math, q_math);
    //gmp_printf("my gcd: %Zd\ntheirs: %Zd\n", return_val, test);
    mpz_fdiv_q(result_val,absolute_val,return_val);
    //gmp_printf("result_val outside is: %Zd\n",result_val);
    ///////mpz_urandomb(e, state, nbits);
    //////gcd(return_val, e, result_val);
    mpz_t coprime;
    mpz_init(coprime);
    while(mpz_cmp_ui(coprime,1)!=0){//return_val
    //while(mpz_cmp_ui(coprime,1)!=0){
        //printf("in while loop\n");
	mpz_urandomb(e, state, nbits);
        gcd(coprime, e, result_val);//return_val
	//gmp_printf("result_val inside is: %Zd\n",result_val);
	//gmp_printf("e inside is: %Zd\n",e);
    }mpz_clears(result_val, coprime, q_math, p_math, absolute_val, return_val, total_val, NULL);
}

void rsa_write_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
    //pbfile = fopen("pbfile","r+");//pdfile.txt??
    gmp_fprintf(pbfile,"%Zx\n%Zx\n%Zx\n%s\n",n,e,s,username);//lower or upper case x
    //gmp_fprintf(pbfile,"%s\n",username);
    //printf("username is: %s", username);
    // %s = char??
    //written in hexstring
}

void rsa_read_pub(mpz_t n, mpz_t e, mpz_t s, char username[], FILE *pbfile){
    //pbfile = fopen("pbfile","r");
    gmp_fscanf(pbfile,"%Zx\n%Zx\n%Zx\n%s\n",n,e,s,username);//use FILE*pbfile??
    //gmp_fscanf(pbfile,"%s\n",username);
    //printf("username is: %s", username);
}

void rsa_make_priv(mpz_t d, mpz_t e, mpz_t p, mpz_t q){
    mpz_t return_value, p_lcm, q_lcm, absolute_value, total_value;
    mpz_init_set_ui(p_lcm,0);
    //mpz_init(test);
    //gmp_printf("p: %Zd\nq: %Zd\n", p,q);
    mpz_init_set_ui(absolute_value,0);
    mpz_init_set_ui(q_lcm,0);
    mpz_sub_ui(p_lcm, p,1);
    mpz_sub_ui(q_lcm,q,1);
    mpz_init_set_ui(total_value,0);
    mpz_mul(total_value, q_lcm, p_lcm);
    //gmp_printf("total_value is: %Zd\n", total_value);
    mpz_abs(absolute_value,total_value);
    //gmp_printf("absolute_value is: %Zd\n",absolute_value);
    gcd(return_value,p_lcm,q_lcm);//???
    //gmp_printf("return value before div is: %Zd\n", return_value);
    mpz_div(return_value,absolute_value,return_value);//???
    //gmp_printf("return val is: %Zd\n",return_value);
    //gmp_printf("e before mod inverse: %Zd",e);
    mod_inverse(d,e,return_value);
    //mpz_invert(test, e, return_value);
    //gmp_printf("d is: %Zd\ne is:%Zd\n",d,e);
    //gmp_printf("theirs: %Zd\n", test);
    mpz_clears(return_value, p_lcm, absolute_value, q_lcm, total_value, NULL);
}

void rsa_write_priv(mpz_t n, mpz_t d, FILE *pvfile){
    //pvfile = fopen("pvfile", "r+");
    gmp_fprintf(pvfile, "%Zx\n%Zx\n",n,d);
    //written in hexstring
}

void rsa_read_priv(mpz_t n, mpz_t d, FILE *pvfile){
    //pvfile = fopen("pvfile","r");
    gmp_fscanf(pvfile,"%Zx\n%Zx\n",n,d);//use FILE*pvfile??
}

void rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n){
    pow_mod(c,m,e,n);
}

void rsa_encrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t e){
    mpz_t m,c;
    mpz_inits(m,c,NULL);
    //uint8_t size = sizeof(uint8_t);
    size_t log = mpz_sizeinbase(n,2);
    size_t k = log;
    k-= 1;
    k/= 8;
    size_t size = sizeof(uint8_t);
    uint8_t *encrypt_arr =(uint8_t *)calloc(k, size);
    encrypt_arr[0] = 0xff;
    size_t j;
    while((j = fread(encrypt_arr+1,size,k-1,infile))>0){
	//printf("inside rsa encrypt file while");
	mpz_import(m,j+1,1,size,1,0,encrypt_arr);//1 instead of size??
	rsa_encrypt(c,m,e,n);
	//printf("\n");///////////////////////////new line??
	gmp_fprintf(outfile, "%Zx\n",c);////////??????
    }free(encrypt_arr);
    mpz_clears(m, c, NULL);
}

void rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n){
    pow_mod(m,c,d,n);
}
/*
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d){
    int size = sizeof(k);
    uint8_t *decrypt_arr =(uint8_t *)calloc(1, size);
    for (int i=0, i<size,i++){//k instead of size??
        rsa_decrypt(m,c,d,n);
    }
    mpz_clears(m, c, d, NULL)
}
*/
void rsa_decrypt_file(FILE *infile, FILE *outfile, mpz_t n, mpz_t d){
    mpz_t m,c;
    mpz_inits(m,c,NULL);
    uint8_t size = sizeof(uint8_t);
    size_t log = mpz_sizeinbase(n,2);
    size_t k = log;
    k-= 1;
    k/= 8;
    uint8_t *decrypt_arr =(uint8_t *)calloc(k, size);
    decrypt_arr[0] = 0xff;
    while(!feof(infile)){
        gmp_fscanf(infile,"%Zx\n",c);
	rsa_decrypt(m,c,d,n);
	size_t j=0;
	//mpz_t j;
	//mpz_init_set_ui(j,0);
	mpz_export(decrypt_arr,&j,1,size,1,0,m);
	//printf("\n");////////////////////////////////new line??
	fwrite(decrypt_arr+1, size, j-1, outfile);
    }//printf("\n");///////////////////////////////print a new line?? to fix git lab error
    mpz_clears(m,c,NULL);
    free(decrypt_arr);
}
