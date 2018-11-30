#include <stdio.h>
#include <stdlib.h>
#include<gmp.h>
#include"_Headers/ntheory.h"
#include"_Headers/elgamalgmp.h"
#include<time.h>
#include<string.h>
#include<assert.h>
#include"_Headers/helpers.h"
#include"_Headers/ecdsagmp.h"
#include"_Headers/sha1.h"
#define bufSize 3072

int _ECDSAInit(mpz_t a_eq,mpz_t b_eq,mpz_t prime_field,mpz_t b_point_x,mpz_t b_point_y,mpz_t n){
		FILE* fp;
		int i=0;
	  char buf[bufSize];
		char **tokens=NULL;
		mpz_init(a_eq);
		mpz_init(b_eq);
		mpz_init(prime_field);
		mpz_init(b_point_x);
		mpz_init(b_point_y);
    mpz_init(n);
	  if ((fp = fopen("ecequation.csv", "r")) == NULL)
	  {
	    perror("FOPEN ERROR\n");
	    return 1;
	  }

	  while (fgets(buf, sizeof(buf), fp) != NULL)
	  {
	    buf[strlen(buf) - 1] = '\0';
			tokens = str_split(buf, ';');//split string with ';' delimiter (csv file)
			mpz_set_str(a_eq,tokens[0],16);//coefficient a
			mpz_set_str(b_eq,tokens[1],16);//coefficient  b
			mpz_set_str(prime_field,tokens[2],16);//modulo p
			mpz_set_str(b_point_x,tokens[3],16);//generator point x
			mpz_set_str(b_point_y,tokens[4],16);//generator point y
      mpz_set_str(n,tokens[5],16);//order of the curve
				break;//limited edition xD no time
	  }
	  fclose(fp);
}

void pointAddition(mpz_t x3,mpz_t y3,mpz_t x2,mpz_t y2,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a){
	mpz_t s,tmp,m;
	mpz_init(s);
	mpz_init(tmp);
	mpz_init(m);

if(!point_cmp(x1,y1,x2,y2)){//if (x1,x2)!=(y1,y2)
	if((mpz_cmp_ui(x2,0)==0 && mpz_cmp_ui(y2,0)==0 )||(mpz_cmp_ui(x1,0)==0 && mpz_cmp_ui(y1,0)==0 ))
					// if some point is (0.0)
				{
						if(mpz_cmp_ui(x2,0)==0 && mpz_cmp_ui(y2,0)==0 ){//P=(0,0)
							mpz_set(x3,x1);mpz_set(y3,y1);}
						else{//Q=(0,0)
							mpz_set(x3,x2);mpz_set(y3,y2);
						}
				}
		else{//P!=Q and P,Q!=(0,0)
	      mpz_sub(s,y2,y1);//y2-y1
	      mpz_sub(tmp,x2,x1);//x2-x1
	      mpz_invert(tmp,tmp,p);//(x2-x1)^-1 mod p
	      mpz_mul(s,s,tmp);//(y2-y1)(x2-x1)^-1
				mpz_mod(s,s,p);//(y2-y1)(x2-x1)^-1 mod p
	      mpz_mul(m,s,s);//s^2
	      mpz_sub(m,m,x1);//S^2-x1
	      mpz_sub(m,m,x2);//S^2-x1-x2
	      mpz_mod(m,m,p);//S^2-x1-x2 mod p
	      mpz_sub(tmp,x1,m);//x1-x3
	      mpz_mul(tmp,s,tmp);//S(x1-x3)
	      mpz_sub(tmp,tmp,y1);//S(x1-x3)-y1
	      mpz_mod(y3,tmp,p);//S(x1-x3)-y1 mod p
				mpz_set(x3,m);
					}
		}else
				pointDoubling(x3,y3,x2,y2,p,a);//P=Q => PointDoubling
			mpz_clear(tmp);
			mpz_clear(m);
}
void pointDoubling(mpz_t x3,mpz_t y3,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a){
	mpz_t s,m,n;
	mpz_init(s);
	mpz_init(m);
	mpz_init(n);

	if(mpz_cmp_ui(x1,0)==0 && mpz_cmp_ui(y1,0)==0 ){//(x1,y1)=(0,0)
		mpz_set_ui(x3,0);mpz_set_ui(y3,0);
	}else{//(x1,y1)!=(0,0)
		mpz_mul(m,x1,x1);//x1^2
		mpz_mul_ui(m,m,3);//3*x1^2
		mpz_add(m,m,a);//3*x1^2+a
		mpz_mul_ui(n,y1,2);//2*y1
		mpz_invert(n,n,p);//(2*y1)^-1
		mpz_mul(s,n,m);//(3*x1^2+a)*(2*y1)^-1
		mpz_mod(s,s,p);//(3*x1^2+a)*(2*y1)^-1 mod p
		//gmp_printf("The slope -> %Zd\n",s);//testing
		mpz_mul(m,s,s);//S^2
		mpz_sub(m,m,x1);//S^2-x1
		mpz_sub(m,m,x1);//S^2-x1-x1
		mpz_mod(m,m,p);//S^2-x1-x1 mod p
		mpz_sub(n,x1,m);//x1-x3
		mpz_mul(n,n,s);//S(x1-x3)
		mpz_sub(n,n,y1);//S(x1-x3)-y1
		mpz_mod(y3,n,p);//S(x1-x3)-y1 mod p
		mpz_set(x3,m);//x3=S^2-x1-x1 mod p
		//gmp_printf("x3 -> %Zd\n",m);//testing
		//gmp_printf("y3 -> %Zd\n",y3);//testing
	}
	mpz_clear(m);
	mpz_clear(n);
	mpz_clear(s);
}

void doubleAndAdd(mpz_t x3,mpz_t y3,mpz_t x1,mpz_t y1,mpz_t p,mpz_t a,mpz_t scalar){
	char binaryScalar[bufSize];
	int i=0;
	mpz_t n_x,n_y,q_x,q_y;

	mpz_init(n_x);
	mpz_init(n_y);
	mpz_init(q_x);
	mpz_init(q_y);
	mpz_init(x3);
	mpz_init(y3);
	mpz_set(n_x,x1);
	mpz_set(n_y,y1);
	mpz_get_str(binaryScalar,2,scalar);//convert the scalar to a binary representation
	i=strlen(binaryScalar)-1;//i = length of the binary string - 1

while(i>=0){
  if(binaryScalar[i]=='1')//if '1' double and add otherwise double only
    pointAddition(q_x,q_y,q_x,q_y,n_x,n_y,p,a);

    pointDoubling(n_x,n_y,n_x,n_y,p,a);
		--i;
}

	mpz_set(x3,q_x);
	mpz_set(y3,q_y);

	mpz_clear(n_x);
	mpz_clear(n_y);
	mpz_clear(q_x);
	mpz_clear(q_y);
}

int point_cmp(mpz_t x1,mpz_t y1,mpz_t x2,mpz_t y2){
  return mpz_cmp(x1,x2)==0 && mpz_cmp(y1,y2)==0;
}

void displayPoint(mpz_t x,mpz_t y){
  printf("[");
  gmp_printf("x = %Zd\n",x);
  gmp_printf("y = %Zd",y);
  printf("]\n");
}

void _ECDSAKeyGeneration(mpz_t d,mpz_t qx,mpz_t qy,mpz_t n,mpz_t gx,mpz_t gy,mpz_t p,mpz_t a){
  unsigned long seed=time(NULL);
  gmp_randstate_t state;//rand state declaration
	mpz_init(qx);
	mpz_init(qy);

	gmp_randinit_mt(state);//init rand state
	gmp_randseed_ui(state, seed);
  do{
  	mpz_urandomm (d,state, n);//generate d in [1,n-1]
	}while(mpz_cmp_ui(d,0)==0);

	doubleAndAdd(qx,qy,gx,gy,p,a,d);//generate Q=(qx,qy) the public key as d*G
}

void _ECDSASign(char *msg,char **e,mpz_t S,mpz_t r,mpz_t gx,mpz_t gy,mpz_t n,mpz_t d,mpz_t a,mpz_t p){
	mpz_t ke,tp;
	mpz_t kx,ky,tmp;
	int i=0;
	unsigned long seed=time(NULL);

	mpz_init(tp);
	*e=_SHA1Hash(msg);//generate the SHA-1 hash of the msg
	mpz_set_str(tp,*e,16);//save it to tp

  gmp_randstate_t state;//rand state declaration
	mpz_init(ke);
	mpz_init(kx);
	mpz_init(ky);
	mpz_init(tmp);
	mpz_init(S);
	mpz_init(r);

	gmp_randinit_mt(state);//init rand state
	gmp_randseed_ui(state, seed);
	do{
		do{
		mpz_urandomm (ke,state, n);//generates random ke in [1,n-1]
	}while(mpz_cmp_ui(ke,0)==0 || mpz_cmp(ke,d)==0);

	gmp_printf("ke -> %Zd\n",ke);
	doubleAndAdd(kx,ky,gx,gy,p,a,ke);//calculate (kx,ky) as ke*G

				mpz_mod(r,kx,n);//r=kx mod n
				mpz_mul(tmp,d,r);//tmp=d*r
				mpz_add(tmp,tp,tmp);//tmp=e+dr
				mpz_mod(tmp,tmp,n);//tmp = e+dr mod n
				mpz_invert(tp,ke,n);//tmp2 = Ke^-1 mod n
				mpz_mul(tmp,tmp,tp);//tmp = (e+dr)Ke^-1
				mpz_mod(S,tmp,n);//tmp = (e+dr)Ke^-1  mod n

	}while(mpz_cmp_ui(r,0)==0 || mpz_cmp_ui(S,0)==0 );//repeat while S=0 or r=0
}

void _ECDSAUnsign(mpz_t S,mpz_t x,char *e,mpz_t r,mpz_t gx,mpz_t gy,mpz_t n,mpz_t qx,mpz_t qy,mpz_t a,mpz_t p){
	mpz_t w,u1,u2;
	mpz_t tmp,tp;
	mpz_t ux,uy;
	mpz_t vx,vy;
	mpz_init(w);
	mpz_init(u1);
	mpz_init(u2);
	mpz_init(ux);
	mpz_init(uy);
	mpz_init(vx);
	mpz_init(vy);
	mpz_init(tmp);
	mpz_init(tp);
	mpz_init(x);

	mpz_set_str(tp,e,16);//Hex to Dec

	mpz_invert(w,S,n);//w = S^-1 mod n
	mpz_mul(u1,w,tp);//u1 = w*e
	mpz_mod(u1,u1,n);//u1 = w*e mod n
	mpz_mul(u2,r,w);//u2 = w*r
	mpz_mod(u2,u2,n);//u2=w*r mod n

	doubleAndAdd(ux,uy,gx,gy,p,a,u1);//calculate (ux,uy) as u1*G
	doubleAndAdd(vx,vy,qx,qy,p,a,u2);//calculate (vx,vy) as u2*Q
	pointAddition(x,tmp,ux,uy,vx,vy,p,a);//calculate (x,tmp) as (ux,uy)*(vx,vy)

	mpz_clear(w);
	mpz_clear(u1);
	mpz_clear(u2);
	mpz_clear(ux);
	mpz_clear(uy);
	mpz_clear(vx);
	mpz_clear(vy);
	mpz_clear(tmp);
	mpz_clear(tp);
}
int _ECDSAVerification(mpz_t r,mpz_t x,mpz_t n){
		mpz_t res;
		mpz_init(res);
		mpz_mod(res,x,n);//calculate x mod n
		return mpz_cmp(res,r)==0;// is r \equiv x mod n
}
