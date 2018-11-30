#ifndef ECDSAGMP_H_INCLUDED
#define ECDSAGMP_H_INCLUDED
#include <gmp.h>


void displayPoint(mpz_t x,mpz_t y);
int point_cmp(mpz_t x1,mpz_t y1,mpz_t x2,mpz_t y2);
int _ECDSAInit(mpz_t a_eq,mpz_t b_eq,mpz_t prime_field,mpz_t b_point_x,mpz_t b_point_y,mpz_t n);
int point_cmp(mpz_t x1,mpz_t y1,mpz_t x2,mpz_t y2);
void pointAddition(mpz_t x3,mpz_t y3,mpz_t x2,mpz_t y2,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a);
void pointDoubling(mpz_t x3,mpz_t y3,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a);
void doubleAndAdd(mpz_t x3,mpz_t y3,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a,mpz_t scalar);
void _ECDSAKeyGeneration(mpz_t d,mpz_t qx,mpz_t qy,mpz_t n,mpz_t gx,mpz_t gy,mpz_t p,mpz_t a);
void _ECDSASign(char *msg,char **e,mpz_t S,mpz_t r,mpz_t gx,mpz_t gy,mpz_t n,mpz_t d,mpz_t a,mpz_t p);
void _ECDSAUnsign(mpz_t S,mpz_t x,char *e,mpz_t r,mpz_t gx,mpz_t gy,mpz_t n,mpz_t qx,mpz_t qy,mpz_t a,mpz_t p);
int _ECDSAVerification(mpz_t r,mpz_t x,mpz_t n);
#endif
