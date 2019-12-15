#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "_Headers/ntheory.h"
#include "_Headers/elgamalgmp.h"
#include <time.h>
#include <string.h>
#include <assert.h>
//#define REPS 10
//#define KLENGTH 30
//#define REPS 40
//#define KLENGTH 100
//#define REPS 120
//#define KLENGTH 300
int main(int argc, char **argv)
{
	mpz_t p, alpha, d, beta, r, S, tp;
	mpz_t res;
	mpz_t *resxx = NULL;
	int REPS = 10, KLENGTH = 30;
	char *e;
	mpz_t t;
	char *message = 0;
	long length;
	FILE *f = NULL;
	mpz_init(res);
	mpz_init(d);
	mpz_init(beta);
	mpz_init(r);
	mpz_init(t);
	mpz_init(S);
	mpz_init(tp);

	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{
			if (strcmp(argv[i], "--reps") == 0 || strcmp(argv[i], "-r") == 0)
			{
				REPS = atoi(argv[i + 1]);
			}
			if (strcmp(argv[i], "--klength") == 0 || strcmp(argv[i], "-k") == 0)
			{
				KLENGTH = atoi(argv[i + 1]);
				if (KLENGTH < 5)
				{
					printf("key length must be greater or equal to 15\n");
					printf("defaulting to k = 30\n");
					KLENGTH = 30;
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
	else
	{
		message = malloc((6 * sizeof(char)));
				strcpy(message, "hello");
	}
	printf("Message to sign -> %s \n", f);
	printf("_____________________________\n\n");
	groupPrimeOGenerator(p, alpha, KLENGTH, REPS); //   step 1
	gmp_printf("P Large prime  -> %Zd\n", p);
	gmp_printf("Alpha generator of Z*_p -> %Zd\n", alpha);
	printf("_____________________________\n\n");
	_ElGamalKeyGeneration(d, beta, p, alpha); // step 2
	gmp_printf("Private key d -> -> %Zd\n", d);
	gmp_printf("Public key Beta -> %Zd\n", beta);
	printf("_____________________________\n\n");
	_ElGamalSign(message, &e, S, r, p, alpha, d); //step 3
	printf("Signed Ss:\n");
	mpz_set_str(tp, e, 10);
	gmp_printf("%Zd : ", S);
	printf("\n");
	printf("Unigned ts:\n");
	_ElGamalUnsign(S, t, r, beta, p); //step 4
	gmp_printf("%Zd : ", t);
	printf("\n");
	printf("_____________________________\n\n");
	printf("Elgamal verify:\n");
	printf("\n");
	if (_ElGamalVer(t, e, alpha, p))
		printf("Valid Signature\n"); //step 5
	else
		printf("Invalid signature\n");

	mpz_clear(p);
	mpz_clear(alpha);
	return 0;
}
