#include "/usr/local/include/pbc/pbc.h"
#include "wAbeSetup.h"
#include "elementIO.h"
#include<stdio.h>
void generatePrime(mpz_t *p,int sBit){
	mpz_init(*p);//initial the prime p
    pbc_mpz_randomb(*p,sBit);//random choose p with 512-bit
	mpz_nextprime(*p,*p);	
	return;
}

void setupPairing(pairing_t *pairing){
	mpz_t p;
	generatePrime(&p,512);//generate 512-bit prime
	pbc_param_t param;
	pbc_param_init_a1_gen(param,p);//using type a1 curve
	pairing_init_pbc_param(*pairing,param);
//	FILE *fPrime = fopen("prime.data","w");//the group order of prime p
//	gmp_fprintf(fPrime,"%Zd",p);
//	fclose(fPrime);
//	pbc_param_out_str(stdout, param);
	return;
}

void wSetup(int attrNo,pairing_t *pairing){
	int count = 0;//the index of the attribute array
	setupPairing(pairing);//setup pairing first
    element_t g;//the generator of G
    element_init_G2(g,*pairing);//initial the generator g
    element_random(g);
    /* initial the random group elements h_1...h_attrNo 
    which belog to G and are associated with the attrNo 
    attributes in the system.
    */
      
    element_t h[attrNo];
	while(count!=attrNo){
		element_init_G2(h[count],*pairing);
		element_random(h[count]);
			count++;
	}//end of while, finish generating the h_1...h_attrNo
	element_t alpha;
	element_t a;
	//initial the alpha and a in Z_p        
	element_init_Zr(alpha,*pairing);
	element_init_Zr(a,*pairing);
	element_random(alpha);
	element_random(a);
	//public key e(g,g)^alpha
	element_t pubKey;
	element_t gAlpha;
	element_t gA;
    element_init_GT(pubKey,*pairing);//initial the publicKey
	element_init_G2(gAlpha,*pairing);//initial the gAlpha
	element_init_G2(gA,*pairing);//initial the gA
	element_pow_zn(gAlpha,g,alpha);//gAlpha=g^alpha
	element_pow_zn(gA,g,a);//gA=g^a
	weilPairing(&pubKey,g,gAlpha,pairing);//publicKey = e(g,g^alpha) = e(g,g)^alpha
	//Master secret key
	element_t msk;
	element_init_G2(msk,*pairing);
	element_set(msk,gAlpha);//msk = g^alpha
	//write the master key and public key to file
	FILE* fG = fopen("publicKey/g.key","w");//file pointer to the public key g
	FILE* fGA = fopen("publicKey/gA.key","w");//file pointer to the public key gA
	FILE* fPub = fopen("publicKey/eGG.key","w");//file pointer to the public key e(g,gALPHA)
	FILE* fH = fopen("publicKey/h.key","w");//file pointer to the public key h
	FILE* fMsk = fopen("MSK/msk.key","w");//file pointer to the master key
	element_fprintf(fG,"%B\n",g);
	element_fprintf(fPub,"%B\n",pubKey);
	element_fprintf(fGA,"%B\n",gA);
	count = 0;
	while(count!=attrNo){
		element_fprintf(fH,"%B\n",h[count]);
		element_clear(h[count]);
		count++;
	}
	element_fprintf(fMsk,"%B\n",msk);
	//close the file pointer and clear all the element
	fclose(fG);
	fclose(fGA);
	fclose(fPub);
	fclose(fH);
	fclose(fMsk);
	element_clear(g);
	element_clear(a);
	element_clear(alpha);
	element_clear(gAlpha);
	element_clear(gA);
	element_clear(pubKey);
	element_clear(msk);

}//end of setup

