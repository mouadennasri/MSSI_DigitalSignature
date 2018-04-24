#include <stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include"_Headers/ntheory.h"
#include"_Headers/elgamalgmp.h"
#include<time.h>
#include<string.h>
#include<assert.h>
#include"_Headers/helpers.h"
#include"_Headers/ecdsagmp.h"
#define bufSize 1024

int main(int argc,char **argv)
{
	int h=11;
	mpz_t S,x;
	char *e=NULL;
	char f[]="Hello MSSI";
	mpz_t a_eq,b_eq,prime_field, b_point_x, b_point_y,n,x3,y3,res,d,qx,qy,r;
	mpz_init(a_eq);
	mpz_init(b_eq);
	mpz_init(prime_field);
	mpz_init(b_point_x);
	mpz_init(b_point_y);
	mpz_init(n);
	mpz_init(x3);
	mpz_init(y3);
	mpz_init(res);
	mpz_init(d);
	mpz_init(qx);
	mpz_init(qy);
	mpz_init(r);
		mpz_init(S);	mpz_init(x);
	mpz_set_ui(res,5);
/*
	mpz_set_ui(b_point_x,5);
	mpz_set_ui(b_point_y,1);
	mpz_set_ui(qx,6);
	mpz_set_ui(qy,2);
	mpz_set_ui(prime_field,17);
	mpz_set_ui(a_eq,2);
	mpz_set_ui(res,2658);*/



printf("Message to sign -> %s \n",f);
_ECDSAInit(a_eq,b_eq,prime_field,b_point_x,b_point_y,n);

gmp_printf("a_eq: %Zd\n",a_eq);
gmp_printf("b_eq: %Zd\n",b_eq);
gmp_printf("prime_field: %Zd\n",prime_field);
gmp_printf("b_point_x: %Zd\n",b_point_x);
gmp_printf("b_point_y: %Zd\n",b_point_y);
gmp_printf("n: %Zd\n",n);

//doubleAndAdd(x3,y3,b_point_x,b_point_y,prime_field,a_eq,res);
//displayPoint(x3,y3);
//pointDoubling(x3,y3,b_point_x,b_point_y,prime_field,a_eq);
//pointAddition(x3,y3,b_point_x,b_point_y,qx,qy,prime_field);

printf("Curve param init completed\n\n");
//displayPoint(b_point_x,b_point_y);
//gmp_printf("res -> %Zd\n",res);
//pointDoubling(x3,y3,b_point_x,b_point_y,prime_field,a_eq);
//doubleAndAdd(x3,y3,b_point_x,b_point_y,prime_field,a_eq,res);
_ECDSAKeyGeneration(d,qx,qy,n,b_point_x,b_point_y,prime_field,a_eq);

gmp_printf("private key: %Zd\n",d);
printf("public key ---:\n");
displayPoint(qx,qy);

printf("Key generation completed\n\n");
_ECDSASign(f,&e,S,r,b_point_x,b_point_y,n,d,a_eq,prime_field);

printf("hash message -> %s\n",e);
gmp_printf("S -> %Zd\n",S);
gmp_printf("r -> %Zd\n",r);
printf("Message sign completed\n");
/*for(int i=0;i<mpz_get_ui(rex[0]);i++){
	gmp_printf("%Zd\n",rex[i+1]);
}*/
//printf("ee -> %s",e);*

printf("//////////////////////////////////////////////\n");
_ECDSAUnsign(S,x,e,r,b_point_x,b_point_y,n,qx,qy,a_eq,prime_field);

	mpz_mod(res,x,n);
	gmp_printf("x1 -> %Zd\n",res);
	gmp_printf("r -> %Zd\n",r);
	if(_ECDSAVerification(r,x,n))
		printf("Valid Signature\n");//step 5
		else
		printf("Invalid signature\n");
return 0;
}
