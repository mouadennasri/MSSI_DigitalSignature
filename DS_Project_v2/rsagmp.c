#include<stdio.h>
#include<stdlib.h>
#include "_Headers/rsagmp.h"
#include "_Headers/ntheory.h"
#include<time.h>
#include<float.h>
#include <gmp.h>
#include<assert.h>
#include<time.h>
#include<string.h>
#include"_Headers/sha1.h"
//#define REPS 0
//#define BITCNT 5
//#define REPS 10
//#define BITCNT 100
//#define REPS 25
//#define BITCNT 300

//RSA P Q _RSAKeyGeneration
void _RSAPQrandomPrime(mpz_t p,mpz_t q,mp_bitcnt_t n,int reps){
  unsigned long seed=time(NULL);
  gmp_randstate_t state;//rand state declaration
/* 1. Initialize the number 'res' */
  mpz_init(p);
  mpz_init(q);
  //mpz_set_ui(res,0);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);
  do{
    mpz_urandomb (p,state, n);
    //gmp_printf("randomly generated number: %Zd\n", res);//testing
  }while(mpz_probab_prime_p(p,reps)<1 || mpz_cmp_ui(p,12)<=0);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);
  do{
    mpz_urandomb (q,state, n);
    //gmp_printf("randomly generated number: %Zd\n", res);//testing
  }while(mpz_probab_prime_p(q,reps)<1 || mpz_cmp_ui(q,12)<=0 || mpz_cmp(q,p)==0 );
  gmp_randclear(state);
}

void rsaPublicExponentGenerator(mpz_t e,mpz_t phi,int reps){
  unsigned long seed=time(NULL);
  gmp_randstate_t state;//rand state declaration
  mpz_t gcd;
  mpz_init(gcd);
  mpz_init(e);
  gmp_randinit_mt(state);//init rand state
  gmp_randseed_ui(state, seed);
  do{
  mpz_urandomm (e,state, phi);//generate a random number e < phi
  //gmp_printf("random generated e: %Zd\n",e);//testing
  mpz_gcd(gcd,e,phi);//gcd(e,phi)
  //gmp_printf("gcd : %Zd\n",gcd);//testing
  //gmp_printf("randomly generated number: %Zd\n", res);//testing
}while(mpz_cmp_ui(e,1)==0 || mpz_cmp_ui(e,2)==0 || mpz_cmp_ui(gcd,1)!=0);
  //loop again if e==1 || e==2 || gcd(e,phi)!=1
  gmp_randclear(state);
}

void _RSAKeyGeneration(mpz_t e,mpz_t n,mpz_t d,int BITCNT,int REPS){
  mpz_t p,q,phi,tmp;
  //init numbers
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(e);
  mpz_init(d);
  mpz_init(phi);
  mpz_init(tmp);

  _RSAPQrandomPrime(p,q,BITCNT,REPS);//generate random P Q
  gmp_printf("p: %Zd\n", p);
  gmp_printf("q: %Zd\n", q);
  //calculate RSA modulus n
  mpz_mul(n,p,q);//n=p*q
  gmp_printf("n: %Zd\n", n);
  //calculate RSA modulus eulerTotient
  eulerTotient(phi,p,q);//phi=(p-1)*(q-1)
  gmp_printf("phi(n): %Zd\n",phi);
  rsaPublicExponentGenerator(e,phi,REPS);//1<e<phi and gcd(e,phi)==1
  gmp_printf("e: %Zd\n",e);
  mpz_invert(d,e,phi);//calculate the inverse of e mod phi
  gmp_printf("d: %Zd\n",d);
  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(phi);
  mpz_clear(tmp);
}

mpz_t* _RSAEncryption(char *msg,mpz_t n,mpz_t e){
  mpz_t base;
  mpz_t *cipher=(mpz_t*)malloc(sizeof(mpz_t)*(strlen(msg)+1));//mpz_t array holding
  //the equiv cipher of every letter of the msg
  mpz_init(base);
  for(int i=0;i<=strlen(msg);i++)//mpz_t array init
    mpz_init(cipher[i]);
    mpz_set_ui(cipher[0],strlen(msg));//set the first mpz_t of the array to
    //the length of the msg

  for(int i=1;i<=strlen(msg);i++){
    mpz_set_ui(base,msg[i-1]);//convert letters of the msg to an mpz_t number
    mpz_powm (cipher[i],base, e, n);//encryption of every letter X^e mod n
  }
    return cipher;
    mpz_clear(base);
}

char* _RSADecryption(mpz_t *cipher,mpz_t n,mpz_t d){
  int limit=mpz_get_ui(cipher[0]);//length of the cipher saved in the first mpz_t of the array
  char *msg=(char*)malloc(sizeof(char)*(limit+1));//allocate a string for the plain text
  msg[limit]='\0';
  for(int i=0;i<limit;i++){
    mpz_powm (cipher[i+1],cipher[i+1], d, n);//decryption of the cipher C^d mod n
    msg[i]=mpz_get_ui(cipher[i+1]);
  }
  return msg;
}
mpz_t* _RSASign(char *msg,mpz_t n,mpz_t d){
  mpz_t tp;
  mpz_t* S=(mpz_t*)malloc(sizeof(mpz_t)*(strlen(msg)+1));
  for(int i=0;i<=strlen(msg);i++) mpz_init(S[i]);
    mpz_init(tp);
  mpz_set_ui(S[0],strlen(msg));
  for(int i=1;i<=strlen(msg);i++){
    mpz_set_ui(tp,msg[i-1]);
    mpz_mod(tp,tp,n);
    mpz_powm (S[i],tp, d, n);//Signature S \equiv msg[i]^d mod n
  }
  mpz_clear(tp);
  return S;
}

mpz_t* _RSAUnsign(mpz_t *S,mpz_t n,mpz_t e){
    int limit=mpz_get_ui(S[0]);
    mpz_t* x=(mpz_t*)malloc(sizeof(mpz_t)*(limit+1));
    for(int i=0;i<=limit;i++)
      mpz_init(x[i]);

    mpz_set_ui(x[0],limit);
    for(int i=1;i<=limit;i++){
    mpz_powm (x[i],S[i], e, n);//calculatedMsg \equiv S^e mod n
    }
    return x;}

int _RSAVerification(char* xm,mpz_t *S,mpz_t n,mpz_t e){
  int limit=mpz_get_ui(S[0]);
  mpz_t *x;
  char *m=(char*)malloc(sizeof(char)*(limit+1));
  m[limit]='\0';
  x=_RSAUnsign(S,n,e);//reverse the signature
  gmp_printf("Unsigned message \n");
  for(int i=1;i<=limit;i++){
    gmp_printf("%Zd| ",x[i]);//calculatedMsg \equiv S^e mod n
    m[i-1]=mpz_get_ui(x[i]);
  }
  printf("\n%s\n",m);
  return strcmp(m,xm)==0;
}
