#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"weilPairing.h"
#include"abeSetup.h"
#include"keyGen.h"
#include"LSSS.h"
#include"encrypt.h"
#include"decrypt.h"
int main(){
	//construct a CP-ABE scheme
	//1.Setup
	pairing_t pairing;
	//char policy[] = "A OR ((B OR C) AND (D AND E))";
	int attrNo = 5;//the number of attributes
	int i = 0;//index for the following for loop
	setup(attrNo,&pairing);//the first step to set up the public key and master key
	//2.KeyGen
	for( i = 0; i < attrNo; i++){
	     keyGen(pairing,i,attrNo);//genereate the private key according to user's attribute
	}
	MSP msp;//the monotone spanning program
	element_t M;//the plaintext message;
	element_init_G1(M,pairing);
	element_random(M);
	mspSetup(&msp);
	//3.Encrypt
	encrypt(M,pairing,&msp,attrNo);
	//4.Decrypt
	decrypt(pairing,&msp);
	//5.Time calculation presents



	return 0;
}
