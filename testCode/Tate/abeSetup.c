#include "/usr/local/include/pbc/pbc.h"
#include "abeSetup.h"
#include "LSSS.h"
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

void setup(int attrNo,pairing_t *pairing, MSP *msp){
	int count = 0;//the index of the attribute array
	setupPairing(pairing);//setup pairing first
    element_t g;//the generator of G
    element_init_G2(g,*pairing);//initial the generator g
    element_random(g);
    /* initial the random group elements h_1...h_attrNo 
    which belog to G and are associated with the attrNo 
    attributes in the system.
    */
      
    element_t h;
	element_init_G2(h,*pairing);
	//initial the h
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
	element_pairing(pubKey,g,gAlpha);//publicKey = e(g,g^alpha) = e(g,g)^alpha
	//Master secret key
	element_t msk;
	element_init_G2(msk,*pairing);
	element_set(msk,gAlpha);//msk = g^alpha
	//write the master key and public key to file
	FILE* fG = fopen("publicKey/g.key","w");//file pointer to the public key g
	FILE* fGA = fopen("publicKey/gA.key","w");//file pointer to the public key gA
	FILE* fPub = fopen("publicKey/eGG.key","w");//file pointer to the public key e(g,gALPHA)
	FILE* fH;//file pointer the the attribute key
	FILE* fMsk = fopen("MSK/msk.key","w");//file pointer to the master key
	element_fprintf(fG,"%B\n",g);
	element_fprintf(fPub,"%B\n",pubKey);
	element_fprintf(fGA,"%B\n",gA);
	count = 0;
	char hCmd[100];//the command line for the pointer of FILE* fH
	char attrName[2];//the name of attribute
	memset(hCmd,'\0',100);
	memset(attrName,'\0',2);
	strcpy(hCmd,"publicKey/h");
	while(count!=attrNo){
		sprintf(attrName,"%c",msp->label[count]);
		strcat(hCmd,attrName);
		strcat(hCmd,".key");
		fH = fopen(hCmd,"w");		
		element_random(h);
		element_fprintf(fH,"%B",h);
		memset(hCmd,'\0',100);		
		strcpy(hCmd,"publicKey/h");
		memset(attrName,'\0',2);
		fclose(fH);
		count++;
	}
	element_clear(h);
	element_fprintf(fMsk,"%B\n",msk);
	//close the file pointer and clear all the element
	fclose(fG);
	fclose(fGA);
	fclose(fPub);
	fclose(fMsk);
	element_clear(g);
	element_clear(a);
	element_clear(alpha);
	element_clear(gAlpha);
	element_clear(gA);
	element_clear(pubKey);
	element_clear(msk);

}//end of setup

