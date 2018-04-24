#include <stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include"_Headers/ntheory.h"
#include"_Headers/elgamalgmp.h"
#include<string.h>
#include<time.h>
#include"_Headers/sha1.h"

void _ElGamalKeyGeneration(mpz_t d,mpz_t beta,mpz_t p,mpz_t alpha){
	unsigned long seed=time(NULL);

	gmp_randstate_t state;//rand state declaration
	gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);
	mpz_init(d);
	mpz_init(beta);
	do{
			mpz_urandomm(d,state, p);
			//gmp_printf("randomly generated number: %Zd\n", res);//testing
	}while(mpz_cmp_ui(d,1)==0 || mpz_cmp_ui(d,0)==0 || mpz_cmp_ui(d,2)==0 || mpz_cmp(d,p)==0);

	mpz_powm (beta,alpha,d,p);//beta \equiv alpha^d mod p
	gmp_randclear(state);
}

void _ElGamalSign(char *msg,char **e,mpz_t S,mpz_t r,mpz_t p,mpz_t alpha,mpz_t d){
  unsigned long seed=time(NULL);
  gmp_randstate_t state;//rand state declaration
	mpz_t gcd,Ke,tmp,tmp2,tp;

	mpz_init(gcd);
	mpz_init(Ke);
	mpz_init(tmp);
	mpz_init(tp);
	mpz_init(r);
	mpz_init(S);
	mpz_init(tmp2);
	gmp_randinit_mt(state);//init rand state
	gmp_randseed_ui(state, seed);

	*e=_SHA1Hash(msg);//SHA-1 hash of msg
	mpz_set_str(tp,*e,16);
	mpz_sub_ui(p,p,1);
  do{
	  mpz_urandomm (Ke,state,p);//generate Ke in [1,p-1] with gcd(Ke,p-1)=1
	  mpz_gcd(gcd,Ke,p);
	}while(mpz_cmp_ui(Ke,0)==0 || mpz_cmp_ui(gcd,1)!=0 || mpz_cmp(Ke,d)==0 );
	mpz_add_ui(p,p,1);
	mpz_powm (r,alpha,Ke,p);//r \equiv alpha^Ke mod p
	mpz_sub_ui(p,p,1);//p=p-1

      mpz_mul(tmp,d,r);//tmp=d*r
      mpz_set(tmp2,tp);
      mpz_sub(tmp,tmp2,tmp);//tmp=X-dr
      mpz_mod(tmp,tmp,p);//tmp = X-dr mod p-1
      mpz_invert(tmp2,Ke,p);//tmp2 = Ke^-1 mod p-1
      mpz_mul(tmp,tmp,tmp2);//tmp = (X-dr)Ke^-1
      mpz_mod(S,tmp,p);//tmp = (X-dr)Ke^-1  mod p-1

	mpz_add_ui(p,p,1);
	gmp_randclear(state);
	mpz_clear(gcd);
	mpz_clear(Ke);
	mpz_clear(tmp);
	mpz_clear(tp);
	mpz_clear(tmp2);
}

void _ElGamalUnsign(mpz_t S,mpz_t t,mpz_t r,mpz_t beta,mpz_t p){
  mpz_t tmp,tmp2;
  mpz_t tp;

  mpz_init(tmp);
	mpz_init(tp);
	mpz_init(t);
  mpz_init(tmp2);

		mpz_powm (tmp,beta,r,p);//beta^r mod p
    mpz_powm (tmp2,r,S,p);//r^S mod p
    mpz_mul(tmp,tmp,tmp2);//r^S*beta^r
    mpz_mod(t,tmp,p);//r^S*beta^r mod p

	mpz_clear(tmp);
	mpz_clear(tp);
	mpz_clear(tmp2);
}

int _ElGamalVer(mpz_t t,char *e,mpz_t alpha,mpz_t p){
  mpz_t res,tp;
  mpz_init(res);
	mpz_init(tp);
	mpz_set_str(tp,e,16);

  mpz_powm(res,alpha,tp,p);//res=alpha^tp mod p
	gmp_printf("alpha^tp mod p -> %Zd\n",res);
	gmp_printf("t -> %Zd\n",t);

  return mpz_cmp(t,res)==0;
}
