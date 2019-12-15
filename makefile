clean:
	rm -f elgamaltest rsatest ecdsatest
elgamaltest:
	gcc elgamaltest.c elgamalgmp.c ntheory.c sha1.c -lgmp -o elgamaltest
rsatest:
	gcc rsatest.c rsagmp.c ntheory.c sha1.c -lgmp -o rsatest 
ecdsatest:
	gcc ecdsatest.c helpers.c ecdsagmp.c sha1.c -lgmp -o ecdsatest 
all:
	gcc ecdsatest.c helpers.c ecdsagmp.c sha1.c -lgmp -o ecdsatest
	gcc elgamaltest.c elgamalgmp.c ntheory.c sha1.c -lgmp -o elgamaltest
	gcc rsatest.c rsagmp.c ntheory.c sha1.c -lgmp -o rsatest 
freshrsa: clean rsatest
freshelgamal: clean elgamaltest
freshecdsa: clean ecdsatest
