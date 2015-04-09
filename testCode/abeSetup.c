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

void setup(int attrNo,pairing_t *pairing){
	int count = 0;//the index of the attribute array
	setupPairing(pairing);//setup pairing first
        if(pairing_is_symmetric(*pairing)){
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
                element_pairing(pubKey,g,gAlpha);//publicKey = e(g,g^alpha) = e(g,g)^alpha
                //Master secret key
                element_t msk;
                element_init_G2(msk,*pairing);
                element_set(msk,gAlpha);//msk = g^alpha
                //write the master key and public key to file
		FILE* fPubKey = fopen("publicKey.key","w");//file pointer to the public key
		FILE* fMsk = fopen("msk.key","w");//file pointer to the master key
		element_fprintf(fPubKey,"g=%B\n",g);
		element_fprintf(fPubKey,"e(g,gAlpha)=%B\n",pubKey);
		element_fprintf(fPubKey,"gA=%B\n",gA);
		count = 0;
		while(count!=attrNo){
			element_fprintf(fPubKey,"h[%d]=%B\n",count,h[count]);
			element_clear(h[count]);
			count++;
		}
		element_fprintf(fMsk,"MSK=%B\n",msk);
		//close the file pointer and clear all the element
		fclose(fPubKey);
		fclose(fMsk);
		element_clear(g);
		element_clear(a);
		element_clear(alpha);
		element_clear(gAlpha);
		element_clear(gA);
		element_clear(pubKey);
		element_clear(msk);
        }else{
                PBC_ASSERT(pairing_is_symmetric(*pairing),"The pairing isn't symmetric!\n");
        }

}//end of setup

