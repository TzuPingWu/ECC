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
	int attrNo = 5;//the number of attributes
	setup(attrNo,&pairing);//the first step to set up the public key and master key
	//2.KeyGen
	//3.Encrypt
	//4.Decrypt
	//5.Time calculation presents



	return 0;
}
