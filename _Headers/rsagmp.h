#ifndef RSAGMP_H_INCLUDED
#define RSAGMP_H_INCLUDED
#include <gmp.h>

void _RSAPQrandomPrime(mpz_t p,mpz_t q,mp_bitcnt_t n,int reps);
void rsaPublicExponentGenerator(mpz_t e,mpz_t phi,int reps);
void _RSAKeyGeneration(mpz_t e,mpz_t n,mpz_t d,int BITCNT,int REPS);
mpz_t* _RSAEncryption(char *msg,mpz_t n,mpz_t e);
char* _RSADecryption(mpz_t *cipher,mpz_t n,mpz_t d);
mpz_t* _RSASign(char *msg,mpz_t n,mpz_t d);
mpz_t* _RSAUnsign(mpz_t *S,mpz_t n,mpz_t e);
int _RSAVerification(char* xm,mpz_t *S,mpz_t n,mpz_t e);

#endif
