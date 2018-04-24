#include <stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include"_Headers/ntheory.h"
#include"_Headers/elgamalgmp.h"
#include<time.h>
#include<string.h>
#include<assert.h>
//#define REPS 10
//#define KLENGTH 30
//#define REPS 40
//#define KLENGTH 100
//#define REPS 120
//#define KLENGTH 300
int main(int argc,char **argv)
{
mpz_t p,alpha,d,beta,r,S,tp;
mpz_t res;
mpz_t* resxx=NULL;
int REPS=10,KLENGTH=30;
char *e;
mpz_t t;
char f[]="Hello MSSI";
mpz_init(res);
mpz_init(d);
mpz_init(beta);
mpz_init(r);
mpz_init(t);
mpz_init(S);
mpz_init(tp);

assert(argc==2);
switch(atoi(argv[1])){
	case 1:
	break;
	case 2:
	REPS = 40;
	KLENGTH = 100;
	break;
	case 3:
	REPS = 120;
	KLENGTH = 300;
	break;
	default:
	exit(0);
	} 
printf("Message to sign -> %s \n",f);
	 // gmp_printf("p1: %Zd\n",p);
groupPrimeOGenerator(p,alpha,KLENGTH,REPS);//   step 1
gmp_printf("P Large prime  -> %Zd\n",p);
gmp_printf("Alpha generator of Z*_p -> %Zd\n",alpha);
//printf("Hi\n");
_ElGamalKeyGeneration(d,beta,p,alpha);// step 2
gmp_printf("Private key d -> -> %Zd\n",d);
gmp_printf("Public key Beta -> %Zd\n",beta);

_ElGamalSign(f,&e,S,r,p,alpha,d);//step 3
printf("Signed Ss:\n");
mpz_set_str(tp,e,10);
	gmp_printf("%Zd| ",S);
	printf("\n");
	printf("Unigned ts:\n");
_ElGamalUnsign(S,t,r,beta,p);//step 4

    gmp_printf("%Zd| ",t);
			//printf("\n");
//mpz_powm_ui(res,alpha,f[i-1],p);//
//gmp_printf("alpha^X mod p = %Zd\n",res);

printf("\n");
printf("Elgamal verify:\n");

	printf("\n");
	if(_ElGamalVer(t,e,alpha,p))
		printf("Valid Signature\n");//step 5
		else
		printf("Invalid signature\n");
/*
for(int i=0;i<mpz_get_ui(p);i++){
	mpz_powm_ui (res,alpha,i ,p);
	gmp_printf("elt %d -> %Zd\n",i,res);
}*/
mpz_clear(p);
mpz_clear(alpha);
return 0;
}
