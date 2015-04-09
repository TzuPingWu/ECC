#define PBC_DEBUG
#include "/usr/local/include/pbc/pbc.h"
#include "abeSetup.h"

void generatePrime(mpz_t *p,int sBit){
	mpz_init(*p);//initial the prime p
        pbc_mpz_randomb(*p,sBit);//random choose p with 512-bit
        mpz_nextprime(*p, *p);//set p to be a prime
	return;
}

void setupPairing(pairing_t *pairing){
	mpz_t p,q,N;
	mpz_init(N);
	generatePrime(&p,512);//generate 512-bit prime
	generatePrime(&q,512);//generate 512-bit prime
	mpz_mul(N,p,q);
	pbc_param_t param;
	pbc_param_init_a1_gen(param,N);//using type a1 curve
	pairing_init_pbc_param(*pairing,param);
//	pbc_param_out_str(stdout, param);
	return;
}
/*
void setup(int attrNo,pairing_t pairing){
	
	int count = 0;
	setupPairing(&pairing);//setup pairing first
	if(pairing_is_symmetric(pairing)){
		element_t g;//the generator of G
		element_init_G1(g,pairing);//initial the generator g
		// initial the random group elements h_1...h_attrNo 
		//which belog to G and are associated with the attrNo 
		//attributes in the system.
		//
		element_t h[attrNo];
		while(count!=attrNo){
			element_init_G1(h[count],pairing);
			count++;
		}//end of while, finish generating the h_1...h_attrNo
		element_t alpha;
		element_t a;
		//initial the alpha and a in Z_p	
		element_init_Zr(alpha,pairing);
		element_init_Zr(a,pairing);
		//public key e(g,g)^alpha
		element_t pubKey;
		element_t gAlpha;
		element_init_GT(pubKey,pairing);
		element_init_G1(gAlpha);
		element_t gAlpha =  element_mul(gAlpha,g,alpha);//g^alpha
		element_pairing(pubKey,g,g^alpha);//e(g,g^alpha) = e(g,g)^alpha
		//Master secret key
		element_t msk = gAlpha;
		
	}else{
		PBC_ASSERT(pairing_is_symmetric(pairing),"The pairing isn't symmetric!");
	}
}//end of setup
*/
