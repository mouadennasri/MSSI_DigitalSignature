# MSSI Digital Signature
This project represent a GMP implementation of the digital signature algorithms (RSA, ELGAMAL, ECDSA),
This is a C code implementation, easy and ready to use
# GMP Library
GMP or [The GNU Multiple Precision Arithmetic Library ](https://gmplib.org/) is a free library for arbitrary precision arithmetic, operating on signed integers, rational numbers, and floating-point numbers. 
# RSA
The RSA is one of the famous asymmetric algorithms, and it’ is widely used. this algorithm is 
based on the practical difficulty of the factorization of the product of two large
prime numbers, the "factoring problem".

## Implementation

`make freshrsa` This will clear any previous version of the rsatest binary, and compile another version.  
`make rsatest` This will compile the rsatest binary.  

`./rsatest [option] [argument]`  

`options` :  
    `[ -m | --message ] [message]*`  
    `[ -f | --file ] [path]*`  
    `[ -r | --reps ][Miller Rabin REPS value]`  
    `[ -p | --randpow ] [Primes generation interval]`  
    
    note:  higher REPS value will reduce the chances of a non-prime being identified as “probably prime”
           -p or --randpow specifies the integer generation interval in the range 0 to 2^n-1, inclusive 
           where n == randpow value
           
# ELGAMAL
The ElGamal signature scheme is a digital signature scheme
which was described by Taher ElGamal in 1984. Based on the difficulty of computing discrete logarithms.

## Implementation

`make freshelgamal` This will clear any previous version of the elgamaltest binary, and compile another version.  
`make elgamaltest` This will compile the elgamaltest binary.  

`./elgamaltest [option] [argument]`  

`options` :  
    `[ -m | --message ] [message]*`  
    `[ -f | --file ] [path]*`  
    `[ -r | --reps ][Miller Rabin REPS value]`  
    `[ -k | --klength ] [Key length]`  
    
    note:  higher REPS value will reduce the chances of a non-prime being identified as “probably prime”
           klength must be greater or equal to 15
# ECDSA
The ECDSA (Elliptic Curve Digital Signature Algorithm) is a cryptographically secure digital signature scheme, based on the elliptic-curve cryptography (ECC). ECDSA relies on the math of the cyclic groups of elliptic curves over finite fields and on the difficulty of the ECDLP problem (elliptic-curve discrete logarithm problem).

## Implementation

`make freshecdsa` This will clear any previous version of the ecdsatest binary, and compile another version.  
`make ecdsatest` This will compile the ecdsatest binary.  

`./ecdsatest [option] [argument]`  

`options` :  
    `[ -m | --message ] [message]*`  
    `[ -f | --file ] [path]*`  
    
Maintainer
----
ENNASRI Mouad mouad.ennasri@gmail.com
[Linkedin](https://www.linkedin.com/in/mouad-ennasri/) 