#ifndef NTHEORY_H_INCLUDED
#define NTHEORY_H_INCLUDED
#include <gmp.h>
void randomPrime( mpz_t res,mp_bitcnt_t n,int reps);
void randomNumber( mpz_t res,mpz_t n,int reps);
void randomPrimeConditional( mpz_t res,mpz_t n,int reps);
void eulerTotient(mpz_t res,mpz_t p,mpz_t q);
void groupPrimeOGenerator(mpz_t p,mpz_t alpha,mp_bitcnt_t klength,int reps);
#endif
