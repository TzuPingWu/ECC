#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"/home/ping/Desktop/pbc-0.5.14/testCode/Weil/weilPairing.h"

int main(){
	pairing_t pairing;
	char param[1024];
	size_t count = fread(param,1,1024,stdin);
	int result = 0;
	clock_t tStart,tEnd;//tStart:the start of tate pairing, tEnd:the end of tate pairing
	clock_t wStart,wEnd;//wStart:the start of weil pairing, wEnd:the end of weil pairing
	float difftime = 0;
	printf("Hello!\n");
	if(!count) pbc_die("input error!\n");
	result = pairing_init_set_buf(pairing,param,count);
	if(result) printf("Finish!\n");
	element_t g,h;
	element_t public_key, secret_key;
	element_t sig;
	element_t temp1,temp2;

	element_init_G2(g, pairing);
	element_init_G2(public_key,pairing);
	element_init_G1(h,pairing);
	element_init_G1(sig,pairing);
	element_init_GT(temp1,pairing);
	element_init_GT(temp2,pairing);
	element_init_Zr(secret_key,pairing);

	element_random(g);
	element_random(secret_key);
	element_pow_zn(public_key, g, secret_key);
	element_from_hash(h, "ABCDEF", 6);
	element_pow_zn(sig, h, secret_key);
	//tate pairing
	tStart = clock();
	pairing_apply(temp1, sig, g, pairing);
	pairing_apply(temp2, h, public_key, pairing);
	if(!element_cmp(temp1, temp2)){
        	printf("T signature verifies\n");
	} else {
        	printf("T signautre does not verify\n");
	}
	tEnd = clock();
	difftime = (float)(tEnd-tStart)/CLOCKS_PER_SEC;
	printf("The cost time of tate pairing: %f\n",difftime);
	//clear the element temp1, temp2
	element_clear(temp1);
	element_clear(temp2);
	element_init_GT(temp1,pairing);
	element_init_GT(temp2,pairing);	
	//weil pairing
	wStart = clock();
	weilPairing(&temp1,sig,g,pairing);
	weilPairing(&temp2,h,public_key,pairing);
	if(!element_cmp(temp1,temp2)){
		printf("W signature verifies\n");
	} else {
		printf("W signature does not verify\n");
	}
	wEnd = clock();
	difftime = (float)(wEnd-wStart)/CLOCKS_PER_SEC;
	printf("The cost time of weil pairing: %f\n",difftime);
	
	return 0;
}
