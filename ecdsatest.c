#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "_Headers/ntheory.h"
#include "_Headers/elgamalgmp.h"
#include <time.h>
#include <string.h>
#include <assert.h>
#include "_Headers/helpers.h"
#include "_Headers/ecdsagmp.h"
#define bufSize 1024

int main(int argc, char **argv)
{
	int h = 11;
	mpz_t S, x;
	char *e = NULL;
	char *message = 0;
	long length;
	FILE *f = NULL;
	mpz_t a_eq, b_eq, prime_field, b_point_x, b_point_y, n, x3, y3, res, d, qx, qy, r;
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
	mpz_init(S);
	mpz_init(x);
	mpz_set_ui(res, 5);

	if (argc > 1)
	{
		for (int i = 0; i < argc; i++)
		{

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

	printf("Message to sign -> %s \n", message);
	_ECDSAInit(a_eq, b_eq, prime_field, b_point_x, b_point_y, n);

	gmp_printf("a_eq: %Zd\n", a_eq);
	gmp_printf("b_eq: %Zd\n", b_eq);
	gmp_printf("prime_field: %Zd\n", prime_field);
	gmp_printf("b_point_x: %Zd\n", b_point_x);
	gmp_printf("b_point_y: %Zd\n", b_point_y);
	gmp_printf("n: %Zd\n", n);

	printf("Curve param init completed\n\n");

	_ECDSAKeyGeneration(d, qx, qy, n, b_point_x, b_point_y, prime_field, a_eq);

	gmp_printf("private key: %Zd\n", d);
	printf("public key ---:\n");
	displayPoint(qx, qy);

	printf("Key generation completed\n\n");
	_ECDSASign(message, &e, S, r, b_point_x, b_point_y, n, d, a_eq, prime_field);

	printf("hash message -> %s\n", e);
	gmp_printf("S -> %Zd\n", S);
	gmp_printf("r -> %Zd\n", r);
	printf("Message sign completed\n");

	printf("//////////////////////////////////////////////\n");
	_ECDSAUnsign(S, x, e, r, b_point_x, b_point_y, n, qx, qy, a_eq, prime_field);

	mpz_mod(res, x, n);
	gmp_printf("x1 -> %Zd\n", res);
	gmp_printf("r -> %Zd\n", r);
	if (_ECDSAVerification(r, x, n))
		printf("Valid Signature\n"); //step 5
	else
		printf("Invalid signature\n");
	return 0;
}
