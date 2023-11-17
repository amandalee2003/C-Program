#include <stdio.h>
#include "numtheory.h"
#include <stdbool.h>
#include <stdarg.h>
#include <gmp.h>
#include "rsa.h"
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "randstate.h"

void gcd(mpz_t d, mpz_t a, mpz_t b){
    mpz_t b_value, a_value, t_value;
    mpz_init_set(b_value, b);
    mpz_init_set(a_value, a);
    while(mpz_cmp_ui(b_value,0)!= 0){
        mpz_init_set(t_value,b_value);
        mpz_mod(b_value,a_value,b_value);
	mpz_set(a_value, t_value); //??
        //mpz_init_set_ui(d,0);
    }//return a
    mpz_init_set(d,a_value);
    mpz_clears(b_value, a_value, t_value, NULL);
}
void pow_mod(mpz_t out, mpz_t base, mpz_t exponent, mpz_t modulus){
    mpz_t v_value, p_value, d_value;
    mpz_init_set_ui(v_value,1);
    mpz_init_set(p_value, base);
    //gmp_printf("exponent is: %Zd\n", exponent);
    mpz_init_set(d_value, exponent);
    //printf("before while in pow mod\n");
    while(mpz_cmp_ui(d_value,0)>0){
	//gmp_printf("d (exponent) in while is: %Zd\n", d_value);
	//printf("in pow mod while\n");
	if(mpz_odd_p(d_value) != 0){
            //printf("in if pow mod\n");
	    mpz_mul(v_value, v_value, p_value);
            mpz_mod(v_value, v_value, modulus);
	}mpz_mul(p_value,p_value,p_value);
	//printf("before if 2 in pow mod\n");
        //if(mpz_cmp_ui(modulus,0)==0){
	    //printf("in if 2 in pow mod\n");
	    mpz_mod(p_value, p_value, modulus);
	    mpz_fdiv_q_ui(d_value,d_value,2);
    }//return v
    mpz_set(out, v_value);
    mpz_clears(v_value, p_value, d_value, NULL);
    }

void mod_inverse(mpz_t i, mpz_t a, mpz_t n){
    mpz_t t_value, t_prime, r_value, r_prime;
    mpz_init_set_ui(t_prime, 1);
    mpz_init_set(r_value,n);
    mpz_init_set(r_prime,a);
    mpz_init_set_ui(t_value,0);
    while(mpz_cmp_ui(r_prime,0) !=0){
        mpz_t var_one, var_two, r_temp, r_replace, t_temp, q_value, t_replace;
        mpz_init_set(r_replace, r_prime);
        mpz_init_set(r_temp,r_value);
	mpz_init_set(t_replace,t_prime);
	mpz_init_set(t_temp,t_value);
	mpz_init_set_ui(q_value,0);
        mpz_fdiv_q(q_value, r_value, r_prime);
        mpz_init_set(r_value,r_replace);
        mpz_init_set_ui(var_one,0);
        mpz_init_set_ui(var_two,0);
        mpz_mul(var_one,q_value,r_replace);
        mpz_sub(r_prime, r_temp, var_one); 
        //mpz_init_set(r_prime, r_temp);
        //mpz_init_set(t_temp, t_prime);
        mpz_init_set(t_value,t_prime);
        mpz_mul(var_two,q_value,t_replace);
        mpz_sub(t_prime, t_temp, var_two);
        //mpz_init_set(t_prime, t_temp);
        mpz_clears (var_one, var_two, r_replace, r_temp, q_value, t_replace, t_temp, NULL); 
    }if(mpz_cmp_ui(r_value,1) >0){
        mpz_init_set_ui(t_value,0);
    }if(mpz_cmp_ui(t_value,0)<0){
        mpz_add(t_value, t_value, n);
    }mpz_init_set(i, t_value);
    mpz_clears(t_value,  r_value, r_prime, t_prime, NULL);
}
/*
void find_totient(mpz_t s, mpz_t r,mpz_t n){
    printf("is in totient\n");
    mpz_t temp, temp_mod;
    mpz_init_set(temp,n);
    mpz_init_set_ui(temp_mod,0);
    mpz_sub_ui(temp, temp,1);////???????
    mpz_mod_ui(temp_mod,temp,2);//??????
    //while(mpz_cmp_ui(temp,1) != 0){
    while(mpz_cmp_ui(temp_mod,0) == 0){
    //while(mpz_odd_p(temp)!=0){
        printf("in totient while loop\n");
	mpz_add_ui(s,s,1);
        mpz_fdiv_q_ui(temp,temp,2);
        mpz_mod_ui(temp_mod,temp,2);
        if(mpz_odd_p(temp)==0){
	    printf("in totient if loop\n");
            mpz_set(r,temp);
    }}mpz_clears(temp, temp_mod, NULL);
}
*/
bool is_prime(mpz_t n, uint64_t iters){
    if(mpz_cmp_ui(n,2)<0){
	return false;
    }if(mpz_cmp_ui(n,2)==0){
	return true;
    }if(mpz_cmp_ui(n,3)==0){
        return true;
    }if(mpz_even_p(n)){
	return false;
    }//printf("after hard code\n");
    mpz_t s, r, a, two, n_temp, temp, temp_mod;
    mpz_init_set(n_temp,n);
    mpz_sub_ui(n_temp,n_temp,1);
    mpz_init_set_ui(two,2);
    mpz_init_set_ui(s,0);
    mpz_init(a);
    mpz_init_set_ui(r,0);
    mpz_init_set(temp,n_temp);
    mpz_init_set_ui(temp_mod,0);
    mpz_t minus_three;
    mpz_init_set(minus_three,n);//temp
    mpz_mod_ui(temp_mod,n_temp,2);
    while(mpz_cmp_ui(temp_mod,1) != 0){
        //printf("in first while\n");
	mpz_add_ui(s,s,1);
        mpz_fdiv_q_ui(n_temp,n_temp,2);
        mpz_mod_ui(temp_mod,n_temp,2);
    }mpz_set(r,n_temp);
    for(uint64_t i=1;i<=iters;i++){//=??
	//printf("in for loop\n");
	//mpz_t minus_three;
	//mpz_init_set(minus_three,n);//temp
	mpz_sub(minus_three,minus_three,two);
	//mpz_add_ui(a,a,2);
	//printf("before u random\n");
	//gmp_printf("a is: %Zd\n state is: %Zd\n n is: %Zd\nminus_three is: %Zd\n",a,state,n,minus_three);
	//mpz_add_ui(a,a,2);
	mpz_urandomm(a, state, minus_three);
	//printf("after u random\n");
	mpz_add(a,a,two); //maybe do add_ui and use 2 instead
	mpz_t y;
	mpz_init(y);
	//printf("before pow mod\n");
	pow_mod(y,a,r,n);
	//printf("after pow mod\n");
	if((mpz_cmp_ui(y,1)!=0) && (mpz_cmp(y,temp))!=0){
	    mpz_t j, s_minus;
	    mpz_init_set(s_minus,s);
	    mpz_sub_ui(s_minus,s_minus,1);
	    mpz_init_set_ui(j,1);
	    //printf("before while loop 2\n");
	    while(mpz_cmp(j,s_minus)<=0 && mpz_cmp(y,temp)!=0){
		//printf("in second while");
		pow_mod(y,y,two,n);
		if(mpz_cmp_ui(y,1)==0){ 
		    mpz_clears(s, r, a, n_temp, two, y, j, s_minus, NULL);
		    return false;
		}mpz_add_ui(j,j,1);
	    }if(mpz_cmp(y,temp)!=0){ 
		mpz_clears(s, j, r, a, n_temp, two, y, s_minus, NULL);
		return false;
    }mpz_clear(j);
    }mpz_clear(y);
    }mpz_clears(s, r, a, n_temp, two, NULL);
    return true;
}


void make_prime(mpz_t p, uint64_t bits, uint64_t iters){
    //mpz_t prime_bits;
    //mpz_init_set_ui(prime_bits,bits);
    mpz_urandomb(p, state, bits);
    //gmp_printf("p is: %Zd\n", p);
    //printf("passed first urandomb");
    //ONLYRUN THROUGH IF ODD...even function that will run new random if so.
    while(is_prime(p,iters)==false){ //|| (mpz_sizeinbase(p, 2) < bits)){
            //gmp_printf("p is: %Zd\n", p);
	    mpz_urandomb(p,state,bits);
	    //printf("passed second urandomb\n");
    }}
