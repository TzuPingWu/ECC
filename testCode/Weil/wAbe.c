#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"weilPairing.h"
#include"wAbeSetup.h"
#include"keyGen.h"
#include"LSSS.h"
#include"encrypt.h"
#include"wDecrypt.h"

int main(){
	//construct a CP-ABE scheme
	//1.Setup
	pairing_t pairing;
	float difftime= 0.0;
	//char policy[] = "A OR ((B OR C) AND (D AND E))";
	int attrNo = 5;//the number of attributes
	int i = 0;//index for the following for loop
	clock_t wStart,wEnd;
	wStart = clock();
	wSetup(attrNo,&pairing);//the first step to set up the public key and master key
	//2.KeyGen
	MSP msp;//the monotone spanning program	
	mspSetup(&msp);
	keyGen(pairing,attrNo,&msp);//genereate the private key according to user's attribute
	element_t message;//the plaintext message;
	element_init_GT(message,pairing);
	element_random(message);
	element_printf("M1 = %B\n",message);
	//3.Encrypt
	encrypt(message,pairing,&msp,attrNo);
	//4.Decrypt
	wDecrypt(pairing,&msp,message);	
	wEnd = clock();	
	//5.Time calculation presents
	difftime = (float)(wEnd-wStart)/CLOCKS_PER_SEC;
	printf("The cost time of weil pairing: %fs\n",difftime);



	return 0;
}