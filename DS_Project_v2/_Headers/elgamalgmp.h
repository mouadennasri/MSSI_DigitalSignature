#ifndef ELGAMALGMP_H_INCLUDED
#define ELGAMALGMP_H_INCLUDED
#include <gmp.h>

void _ElGamalKeyGeneration(mpz_t d,mpz_t beta,mpz_t p,mpz_t alpha);
void _ElGamalSign(char *msg,char **e,mpz_t S,mpz_t r,mpz_t p,mpz_t alpha,mpz_t d);
void _ElGamalUnsign(mpz_t S,mpz_t t,mpz_t r,mpz_t beta,mpz_t p);
int _ElGamalVer(mpz_t t,char *e,mpz_t alpha,mpz_t p);
#endif
