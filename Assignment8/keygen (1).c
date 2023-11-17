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
#include "rsa.h"
#define OPTIONS "b:i:n:d:s:vh"
int main(int argc, char **argv){
    int opt=0;
    int v_flag = 0;
    int n_flag = 0;
    int d_flag = 0;
    uint64_t min_bits = 1024;
    uint64_t num_is_prime = 50;
    FILE *pbfile;
    FILE *pvfile;
    uint64_t seed = time(NULL);
    while((opt=getopt(argc,argv,OPTIONS)) != -1){
        switch(opt){
            case 'b':
		//min_bits = atoi(optarg);
		min_bits = strtol(optarg, NULL, 10);
		break;
            case 'i':
		//num_is_prime = atoi(optarg);//strtol??
		num_is_prime = strtol(optarg, NULL, 10);
		break;
            case 'n':
		pbfile = fopen(optarg,"w");
	        if(pbfile == NULL){
	            fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
       		    fclose(pbfile); 
		    return 1;
   		 }n_flag =1;
		break;
            case 'd':
		pvfile = fopen(optarg, "w");
		if(pvfile == NULL){
                    fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
                    fclose(pvfile); 
		    return 1;
                 }d_flag =1;
		int fpriv = fileno(pvfile);
                fchmod(fpriv,S_IRUSR|S_IWUSR);//int fd = fileno(pvfile); fchmod(fd,0600); 		     // only priv?
		break;
            case 's':
		seed = strtol(optarg, NULL, 10);
		break;
            case 'v':
		v_flag = 1;
	        break;
	    case 'h':
		/*
                fprintf(stderr,"Usage: ./keygen [options]\n");
		fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
                //fprintf(stderr,"   ./encrypt [-bisvh] [-n pbfile] [-d pvfile]\n\n");
                //fprintf(stderr,"OPTIONS\n");
                fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
		fprintf(stderr,"  the program options.\n");
		fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
		fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
		fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
		fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
		fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
		fprintf(stderr,"    -v          : Enable verbose output.\n");
		fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
		//fprintf(stderr,"   -b              specifies the minimum bits needed for the public modulus n(default: 1024)\n");
                //fprintf(stderr,"   -i              specifies the number of Miller-Rabin iterations for testing primes (default: 50).\n");
                //fprintf(stderr,"   -n pbfile       specifies the public key file (default: rsa.pub).\n");
                //fprintf(stderr,"   -d pvfile       specifies the private key file (default: rsa.priv)\n");
                //fprintf(stderr,"   -s              specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL)).\n");
                //fprintf(stderr,"   -v              enables verbose output.\n");
                //fprintf(stderr,"   -h              displays program synopsis and usage.\n");
		*/
		fprintf(stderr, "Usage: ./keygen [options]\n");
                fprintf(stderr, "  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
                fprintf(stderr, "  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
                fprintf(stderr, "  the program options.\n");
                fprintf(stderr, "    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
                fprintf(stderr, "    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
                fprintf(stderr, "    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
                fprintf(stderr, "    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
                fprintf(stderr, "    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
                fprintf(stderr, "    -v          : Enable verbose output.\n");
                fprintf(stderr, "    -h          : Display program synopsis and usage.\n");
		return 0;
            default:
            /*    fprintf(stderr,"SYNOPSIS\n");
                fprintf(stderr,"   A collection of comparison-based encryption algorithms.\n\n");
                fprintf(stderr,"USAGE\n");
                fprintf(stderr,"   ./encrypt [-bisvh] [-n pbfile] [-d pvfile]\n\n");
                fprintf(stderr,"OPTIONS\n");
                fprintf(stderr,"   -b              specifies the minimum bits needed for the public modulus n(default: 1024)\n");
                fprintf(stderr,"   -i              specifies the number of Miller-Rabin iterations for testing primes (default: 50).\n");
                fprintf(stderr,"   -n pbfile       specifies the public key file (default: rsa.pub).\n");
                fprintf(stderr,"   -d pvfile       specifies the private key file (default: rsa.priv)\n");
                fprintf(stderr,"   -s              specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL)).\n");
                fprintf(stderr,"   -v              enables verbose output.\n");
                fprintf(stderr,"   -h              displays program synopsis and usage.\n");
                exit(-1);
		fprintf(stderr,"Usage: ./keygen [options]\n");
                fprintf(stderr,"  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
                //fprintf(stderr,"   ./encrypt [-bisvh] [-n pbfile] [-d pvfile]\n\n");
                //fprintf(stderr,"OPTIONS\n");
                fprintf(stderr,"  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
                fprintf(stderr,"  the program options.\n");
                fprintf(stderr,"    -s <seed>   : Use <seed> as the random number seed. Default: time()\n");
                fprintf(stderr,"    -b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
                fprintf(stderr,"    -i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
                fprintf(stderr,"    -n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
                fprintf(stderr,"    -d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
                fprintf(stderr,"    -v          : Enable verbose output.\n");
                fprintf(stderr,"    -h          : Display program synopsis and usage.\n");
                //fprintf(stderr,"   -b              specifies the minimum bits needed for the public modulus n(default: 1024)\n");
                //fprintf(stderr,"   -i              specifies the number of Miller-Rabin iterations for testing primes (default: 50).\n");
                //fprintf(stderr,"   -n pbfile       specifies the public key file (default: rsa.pub).\n");
                //fprintf(stderr,"   -d pvfile       specifies the private key file (default: rsa.priv)\n");
                //fprintf(stderr,"   -s              specifies the random seed for the random state initialization (default: the seconds since the UNIX epoch, given by time(NULL)).\n");
                //fprintf(stderr,"   -v              enables verbose output.\n");
                //fprintf(stderr,"   -h              displays program synopsis and usage.\n");
                return 0;
	*/		
		fprintf(stderr, "Usage: ./keygen [options]\n");
                fprintf(stderr, "  ./keygen generates a public / private key pair, placing the keys into the public and private\n");
                fprintf(stderr, "  key files as specified below. The keys have a modulus (n) whose length is specified in\n");
                fprintf(stderr, "  the program options.\n");
                fprintf(stderr, "	-s <seed>   : Use <seed> as the random number seed. Default: time()\n");
                fprintf(stderr, "	-b <bits>   : Public modulus n must have at least <bits> bits. Default: 1024\n");
                fprintf(stderr, "	-i <iters>  : Run <iters> Miller-Rabin iterations for primality testing. Default: 50\n");
                fprintf(stderr, "	-n <pbfile> : Public key file is <pbfile>. Default: rsa.pub\n");
                fprintf(stderr, "	-d <pvfile> : Private key file is <pvfile>. Default: rsa.priv\n");
                fprintf(stderr, "	-v     	: Enable verbose output.\n");
                fprintf(stderr, "	-h          : Display program synopsis and usage.\n");
        	return 0;
	}}
    if(n_flag == 0){
        pbfile = fopen("rsa.pub","w");
	if(pbfile == NULL){
             fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
             fclose(pbfile);
	     return 1;
        }}if(d_flag ==0){
        pvfile = fopen("rsa.priv","w");
        if(pvfile == NULL){
            fprintf(stderr,"Failure opening the file(s), run ./keygen -H for more help.\n");
            fclose(pvfile);
	    return 1;
        }int private_file = fileno(pvfile);
        fchmod(private_file,S_IRUSR|S_IWUSR); 
    }//printf("seed is %lu\n",seed);
    randstate_init(seed);
    //gmp_printf("state is: %Zd",state);
    mpz_t p,q,n,e,d;
    mpz_inits(q,p,n,e,d, NULL);
    rsa_make_pub(p,q,n,e,min_bits,num_is_prime);
    rsa_make_priv(d,e,p,q);
    char *user;
    user = getenv("USER");
    mpz_t username;
    mpz_init(username);
    //printf("user is: %s\n", user);
    mpz_set_str(username,user,62);//getenv(&username)
    //gmp_printf("username is:%Zd\n", username);
    mpz_t s;
    mpz_init(s);
    rsa_sign(s,username,d,n);
    //rsa_write_priv(n,d,pvfile);//n,d,pvfile
    rsa_write_pub(n,e,s,user,pbfile);
    rsa_write_priv(n,d,pvfile);//n,d,pvfile
    if (v_flag == 1){ 
	//gmp_fprintf(stderr,"%s\n%d\n%d\n%d\n%d\n%d\n",username,s,q,n,e,d);
        gmp_printf("(%zu bits) username = %Zd\n(%zu bits) s = %Zd\n(%zu bits) q = %Zd\n(%zu bits) n = %Zd\n(%zu bits) e = %Zd\n(%zu bits) d = %Zd\n", mpz_sizeinbase(username,2), username, mpz_sizeinbase(s,2), s, mpz_sizeinbase(q,2), q, mpz_sizeinbase(n,2), n, mpz_sizeinbase(e,2), e, mpz_sizeinbase(d,2), d);
        //gmp_printf("(%d bits) q = %Zd\n", q_bits, q);
        //gmp_printf("(%d bits) n = %Zd\n", n_bits, n);
        //gmp_printf("(%d bits) e = %Zd\n", e_bits, e);
        //gmp_printf("(%d bits) d = %Zd\n", e_bits, d);
        //gmp_printf("(%d bits) username = %Zd\n", username_bits, username);
    }
    fclose(pvfile);
    fclose(pbfile);
    randstate_clear();//state??
    mpz_clears(p,q,n,e,d,s,username, NULL); 
} 
/*    
 
    //////////////////////////////////////////////////////////////////
    mpz_t a, b, d;
    mpz_inits(a, b, d, NULL);
    mpz_set_ui(a, 135);
    mpz_set_ui(b, 50);
    gcd(d, a, b);
    gmp_printf("gcd(%Zd, %Zd) = %Zd\n", a, b, d);
    mpz_clears(a, b, d, NULL);
    /////////////////////////////////////////////////////////////////////////
*/
/*
int main(void){  	
    mpz_t out, base, exp, mod;
    mpz_inits(out, base, exp, mod, NULL);
    mpz_set_ui(base, 89293837);
    mpz_set_ui(exp, 38474256);
    mpz_set_ui(mod, 94287);
    pow_mod(out, base, exp, mod);
    gmp_printf("pow_mod(%Zd, %Zd, %Zd) = %Zd\n", base, exp, mod, out);
    mpz_clears(out, base, exp, mod, NULL);
}

/////////////////////////////////////////////////////////////////////////
    mpz_t i, a, n;
    mpz_inits(i, a, n, NULL);
    mpz_set_ui(a, 10);
    mpz_set_ui(n, 3);
    mod_inverse(i, a, n);
    gmp_printf("mod_inverse(%Zd, %Zd) = %Zd\n", a, n, i);
    mpz_clears(i, a, n, NULL);
    return 0;

int main(void){
    randstate_init(66);
    mpz_t n; 
    uint64_t iters = 50;
    mpz_init_set_ui(n, 224945997283873);
    bool answer = is_prime(n,iters);
    gmp_printf("is_prime(%Zd, %d) = %B\n", n, iters, answer);
    mpz_clear(n);
}


int main(void){
    randstate_init(66);
    mpz_t p;
    uint64_t bits = 99;
    uint64_t iters = 50;
    mpz_init_set_ui(p, 27);
    make_prime(p,bits,iters);
    gmp_printf("make_prime: %Zd\n", p);
    mpz_clear(p);
    return 0;
}

*/
