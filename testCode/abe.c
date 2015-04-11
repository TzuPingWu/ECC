#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"weilPairing.h"
#include"abeSetup.h"
#include"keyGen.h"

int main(){
	//construct a CP-ABE scheme
	//1.Setup
	pairing_t pairing;
	int attrNo = 3;//the number of attributes
	setup(attrNo,&pairing);//the first step to set up the public key and master key
	//2.KeyGen
	FILE *fPrime = fopen("prime.data","r");
//	mpz_t prime;
//	mpz_init(prime);
//	gmp_fscanf(fPrime,"%Zd",prime);
	keyGen(pairing,0,attrNo);//genereate the private key according to user's attributes
	keyGen(pairing,1,attrNo);
	keyGen(pairing,2,attrNo);
	//3.Encrypt
	//4.Decrypt
	//5.Time calculation presents



	return 0;
}
