#include "_Headers/rsagmp.h"
#include <assert.h>
#include <float.h>
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#define REPS 0
//#define BITCNT 5
//#define REPS 10 // A higher reps value will reduce the chances of a non-prime
//being identified as “probably prime” #define BITCNT 100 #define REPS 25
//#define BITCNT 300

int main(int argc, char **argv)
{
  gmp_randstate_t state; // rand state declaration
  // unsigned long seed;
  mpz_t e, n, d, p, q, res;
  mpz_t *S, *x;
  int flag, limit, REPS = 10, BITCNT = 100;
  char *message = 0;

  // gmp_randinit_mt(state);
  /* 1. Initialize the numbers */
  mpz_init(e);
  mpz_init(n);
  mpz_init(d);
  mpz_init(res);

  char *buffer = 0;
  long length;
  FILE *f = NULL;

  if (argc > 1)
  {
    for (int i = 0; i < argc; i++)
    {
      if (strcmp(argv[i], "--reps") == 0 || strcmp(argv[i], "-r") == 0)
      {
        REPS = atoi(argv[i + 1]);
      }
      if (strcmp(argv[i], "--randpow") == 0 || strcmp(argv[i], "-p") == 0)
      {
        BITCNT = atoi(argv[i + 1]);
        if(BITCNT < 5){
          printf("randomness precision exponent must be greater or equal to 5\n");
          printf("defaulting to p = 100\n");
          BITCNT = 100;
        }
      }
      if (strcmp(argv[i], "--message") == 0 || strcmp(argv[i], "-m") == 0)
      {
        message = malloc((strlen(argv[i + 1]) + 1) * sizeof(char));
        strcpy(message, argv[i + 1]);
      }
      if (strcmp(argv[i], "--file") == 0 || strcmp(argv[i], "-f") == 0)
      {
        f = fopen(argv[i + 1], "rb");
        if (f)
        {
          fseek(f, 0, SEEK_END);
          length = ftell(f);
          fseek(f, 0, SEEK_SET);
          message = malloc(length);
          if (message)
          {
            fread(message, 1, length, f);
          }
          fclose(f);
        }
      }
    }
  }

  printf("Message to sign -> %s \n", message);
  printf("_____________________________\n\n");
  printf("RSA Key Generation: \n");
  do
  {
    _RSAKeyGeneration(e, n, d, BITCNT, REPS);
  } while (mpz_cmp_ui(d, 0) == 0 || mpz_cmp(d, e) == 0);
  printf("_____________________________\n\n");
  printf("Public Key (e,n):\n");
  gmp_printf("(%Zd,%Zd)\n", e, n);
  printf("_____________________________\n\n");
  printf("Private key (d,n):\n");
  gmp_printf("(%Zd,%Zd)\n", d, n);
  printf("_____________________________\n\n");
  S = _RSASign(message, n, d);
  printf("Signed Ss:\n");
  limit = mpz_get_ui(S[0]);
  for (int i = 1; i <= limit; i++)
  {
    gmp_printf("%Zd", S[i]);
    if (i < limit)
      printf(" : ");
  }
  printf("\n");
  printf("_____________________________\n\n");
  if (_RSAVerification(message, S, n, e))
    printf("Valid signature\n");
  else
    printf("Invalid signature\n");

  mpz_clear(e);
  mpz_clear(d);
  mpz_clear(n);

  return 0;
}
