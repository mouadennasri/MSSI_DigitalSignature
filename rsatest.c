#include<stdio.h>
#include<stdlib.h>
#include "_Headers/rsagmp.h"
#include<time.h>
#include<float.h>
#include <gmp.h>
#include<assert.h>
#include<time.h>
#include<string.h>
//#define REPS 0
//#define BITCNT 5
//#define REPS 10
//#define BITCNT 100
//#define REPS 25
//#define BITCNT 300

int main(int argc,char **argv){
gmp_randstate_t state;//rand state declaration
//unsigned long seed;
mpz_t e,n,d,p,q,res;
mpz_t *S,*x;
int flag,limit,REPS=0,BITCNT=5;
char f[]="Hello MSSI";

//gmp_randinit_mt(state);
/* 1. Initialize the number */
mpz_init(e);
mpz_init(n);
mpz_init(d);
mpz_init(res);

assert(argc==2);
switch(atoi(argv[1])){
	case 1:
	break;
	case 2:
	REPS = 10;
	BITCNT = 100;
	break;
	case 3:
	REPS = 25;
	BITCNT = 300;
	break;
	default:
	exit(0);
	}
//mpz_set_ui(e,311);
//mpz_set_ui(n,391);
//mpz_set_ui(d,103);

//_RSAPQrandomPrime(e,n,5,0);
//gmp_printf("p: %Zd\n", e);
//gmp_printf("q: %Zd\n", n);
printf("Message to sign -> %s \n",f);
printf("RSA Key Generation \n");
do{
_RSAKeyGeneration(e,n,d,BITCNT,REPS);
}while(mpz_cmp_ui(d,0)==0 || mpz_cmp(d,e)==0);
printf("Public Key (e,n):\n");
gmp_printf("(%Zd,%Zd)\n", e,n);
printf("Private key (d,n):\n");
gmp_printf("(%Zd,%Zd)\n", d,n);
S=_RSASign(f,n,d);
printf("Signed Ss:\n");
limit=mpz_get_ui(S[0]);
for(int i=1;i<=limit;i++)
    gmp_printf("%Zd| ",S[i]);
    printf("\n");
    if(_RSAVerification(f,S,n,e))
      printf("Valid signature\n");
    else
      printf("Invalid signature\n");

//mpz_init(res);
//for(int i=0;i<12;i++){
//mpz_set_ui(e,i);
//mpz_set_ui(n,12);

//mpz_gcd(res,e,n);
// gmp_printf("randomly generated numberRES: %Zd\n", res);}
  /* 2. Parse the input string as a base 10 number */
//flag = mpz_set_str(a,argv[1], 10);
//assert (flag == 0); /* If flag is not 0 then the operation failed */
/* 2. Parse the input string as a base 10 number */
//flag = mpz_set_str(b,argv[2], 10);
//assert (flag == 0); /* If flag is not 0 then the operation failed */
//mpz_mul(res,a,a);
 /*gmp_randinit_mt(rstate);//init rand state
 gmp_randseed_ui(rstate, seed);
 do{
mpz_urandomb (res,rstate, 300);
 gmp_printf("randomly generated number: %Zd\n", res);
}while(!mpz_probab_prime_p(res,25));*/
//randomPrime(res,300,25);
/* Print n */
//randomPrimeConditional(res,a,25);
//mpz_gcdext (res,s,t,a,b);
  //gmp_printf("e: %Zd\n\n", e);
  //  gmp_printf("n: %Zd\n\n", n);
    //  gmp_printf("d: %Zd\n\n", d);

/*eulerTotient(res,a,b);
  printf ("res = ");
  mpz_out_str(stdout,10,res);
  printf ("\n");
//printf("%s\n\n\n\n",karaStr("27854754744548725424254574275244521979674643114","9989568959875569858557478555885569887633254"));
//printf("\n%lf",DBL_MAX);
//gmp_randclear(rstate);*/
   mpz_clear(e);
      mpz_clear(d);
            mpz_clear(n);

  return 0;
}
