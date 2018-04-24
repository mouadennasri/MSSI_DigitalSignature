#include<stdio.h>
#include<stdlib.h>
#include "_Headers/ntheory.h"
#include<time.h>
#include<float.h>
#include <gmp.h>
#include<assert.h>
#include<time.h>
#include<string.h>
#define REPS 0
#define BITCNT 5
//#define REPS 10
//#define BITCNT 100
//#define REPS 25
//#define BITCNT 300

/*random prime generator using gmp modified on 24/03/2018 ENNASRI Mouad */
void randomPrime( mpz_t res,mp_bitcnt_t n,int reps){
  unsigned long seed;
  gmp_randstate_t state;//rand state declaration
/* 1. Initialize the number 'res' */
  mpz_init(res);
  //mpz_set_ui(res,0);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);

  do{
  mpz_urandomb (res,state, n);
  //gmp_printf("randomly generated number: %Zd\n", res);
}while(!mpz_probab_prime_p(res,reps));
gmp_randclear(state);
}
/*random generator using gmp modified on 24/03/2018 ENNASRI Mouad */
void randomNumber( mpz_t res,mpz_t n,int reps){
  unsigned long seed;
  gmp_randstate_t state;//rand state declaration
/* 1. Initialize the number 'res' */
  mpz_init(res);
  //mpz_set_ui(res,0);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);

  mpz_urandomm (res,state, n);
  //gmp_printf("randomly generated number: %Zd\n", res);

gmp_randclear(state);
}


/*random prime generator using gmp modified on 25/03/2018 ENNASRI Mouad */
void randomPrimeConditional( mpz_t res,mpz_t n,int reps){
  unsigned long seed;
  gmp_randstate_t state;//rand state declaration
/* 1. Initialize the number 'res' */
  mpz_init(res);
  //mpz_set_ui(res,0);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);

  do{
  mpz_urandomm (res,state, n);
  //gmp_printf("randomly generated number: %Zd\n", res);
}while(mpz_probab_prime_p(res,reps)<1 || mpz_cmp_ui(res,2)<1);
gmp_randclear(state);
}

void eulerTotient(mpz_t res,mpz_t p,mpz_t q){
  /* 1. Initialize the number 'res' */
    mpz_init(res);
        //gmp_printf("p: %Zd\n",p);
    mpz_sub_ui(p,p,1);
        //gmp_printf("p-1: %Zd\n",p);
            //gmp_printf("q: %Zd\n", q);
    mpz_sub_ui(q,q,1);
        //gmp_printf("q-1: %Zd\n", q);
    mpz_mul(res,p,q);
    //gmp_printf("eulerTotient: %Zd\n", res);
}

/*4.86 Algorithm Selecting a k-bit safe prime p and a generator α of Z ∗ p*/
void groupPrimeOGenerator(mpz_t p,mpz_t alpha,mp_bitcnt_t klength,int reps){
mpz_t q;
int tmp=(klength*30)/100;
unsigned long seed;
gmp_randstate_t state;//rand state declaration
//mpz_set_ui(res,0);
gmp_randinit_mt(state);//init rand state
gmp_randseed_ui(state, seed);
mpz_init(p);
mpz_init(alpha);
mpz_init(q);
klength=((tmp-1)*100)/30;
  //gmp_printf("pt: %Zd\n",p);

do{
mpz_urandomb (q,state, klength);
	//gmp_printf("randomly generated number q : %Zd\n", q);
	mpz_mul_ui(p,q,2);
		//gmp_printf("randomly generated number p : %Zd\n", p);
	mpz_add_ui(p,p,1);
			//gmp_printf("randomly generated number p : %Zd\n", p);
}while(!mpz_probab_prime_p(p,reps));

  //gmp_printf("pt: %Zd\n",p);
do{
mpz_urandomm(alpha,state, p);

}while(mpz_cmp_ui(alpha,1)==0 || mpz_cmp_ui(alpha,0)==0);

gmp_printf("randomly generated number alpha : %Zd\n", alpha);
gmp_randclear(state);
mpz_clear(q);
}
