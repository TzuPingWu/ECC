#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"weilPairing.h"
#include"abeSetup.h"

int main(){
	//construct a CP-ABE scheme
	//1.Setup
	pairing_t pairing;
	int attrNo = 10;
        int count = 0;
        setupPairing(&pairing);//setup pairing first
        if(pairing_is_symmetric(pairing)){
		printf("The pairing is symmetric!\n");
                element_t g;//the generator of G
                element_init_G2(g,pairing);//initial the generator g
		element_random(g);
		element_printf("g=%B\n",g);
                /* initial the random group elements h_1...h_attrNo 
                which belog to G and are associated with the attrNo 
                attributes in the system.
                */
                element_t h[attrNo];
                while(count!=attrNo){
                        element_init_G2(h[count],pairing);
			element_random(h[count]);
			element_printf("h[%d]=%B\n",count,h[count]);
			count++;
                }//end of while, finish generating the h_1...h_attrNo
		element_t alpha;
                element_t a;
                //initial the alpha and a in Z_p        
                element_init_Zr(alpha,pairing);
                element_init_Zr(a,pairing);
		element_random(alpha);
		element_random(a);
                //public key e(g,g)^alpha
                element_t pubKey;
                element_t gAlpha;
		element_init_GT(pubKey,pairing);//initial the publicKey
		element_init_G2(gAlpha,pairing);//initial the gAlpha
                element_pow_zn(gAlpha,g,alpha);//g^alpha
                element_pairing(pubKey,g,gAlpha);//publicKey = e(g,g^alpha) = e(g,g)^alpha
		element_printf("gAlpha=%B\n",gAlpha);
                //Master secret key
                element_t msk;
		element_init_G2(msk,pairing);
		element_set(msk,gAlpha);//msk = g^alpha
		//print out the master key and public key
		element_printf("MSK:%B\n",msk);
		element_printf("PUBKEY:%B\n",pubKey);
		element_t temp1;
		element_t temp2;
		element_init_GT(temp1,pairing);
		element_init_GT(temp2,pairing);
		element_pairing(temp1,g,gAlpha);
		element_pairing(temp2,gAlpha,g);
		if(!element_cmp(temp1,temp2)){
			printf("The bilinearity succeed!\n");
		}else{
			printf("The bilinearity failed!\n");
		}

        }else{
                PBC_ASSERT(pairing_is_symmetric(pairing),"The pairing isn't symmetric!\n");
        }
	
	//2.KeyGen
	//3.Encrypt
	//4.Decrypt
	//5.Time calculation presents



	return 0;
}
