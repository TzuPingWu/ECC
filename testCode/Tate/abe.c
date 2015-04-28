#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"/usr/local/include/pbc/pbc.h"
#include"abeSetup.h"
#include"keyGen.h"
#include"LSSS.h"
#include"encrypt.h"
#include"decrypt.h"
int main(){
	//construct a CP-ABE scheme
	//Pre-computation -> read the file of users
	float difftime= 0.0;
	//char policy[] = "A OR ((B OR C) AND (D AND E))";
	int i,j,k = 0;//the index of the following loop
	clock_t tStart,tEnd;
	tStart = clock();
	MSP msp;//the monotone spanning program	
	mspSetup(&msp);
	int rows = msp.rows;
	FILE *fUser = fopen("user.file","r");//the pointer to read the user files
	int userNo = 0;//the number of users
	int* attrNo;//the number of attributes
	char **userName;
	char **attribute;
	fscanf(fUser,"%d\n",&userNo);
	attrNo = (int *)malloc(sizeof(int)*userNo);
	userName = (char **)malloc(sizeof(char *)*userNo);
	attribute = (char **)malloc(sizeof(char *)*userNo);
	for( i = 0 ; i < userNo ; i++){
		userName[i] = (char *)malloc(sizeof(char)*100);
		fscanf(fUser,"%s\n",userName[i]);
		fscanf(fUser,"%d\n",&attrNo[i]);
		attribute[i] = (char *)malloc(sizeof(char)*attrNo[i]);
		j = 0;//initialize the index of j
		k = attrNo[i];
		while(k != 0){
			fscanf(fUser,"%c\n",&attribute[i][j]);
			j++;
			k--;
		}
	}
	//1. Setup	
	pairing_t pairing;
	setup(rows,&pairing,&msp);//the first step to set up the public key and master key
	//2. KeyGen
	for( i = 0; i<userNo;i++){
		keyGen(pairing,attrNo[i],attribute[i],userName[i]);//genereate the private key according to user's attribute
	}
	element_t message;//the plaintext message;
	element_init_GT(message,pairing);
	element_random(message);
	element_printf("M1 = %B\n",message);
	//3.Encrypt
	encrypt(message,pairing,&msp);
	//4.Decrypt
	decrypt(pairing,&msp,message,attrNo[1],attribute[1],userName[1]);	
	tEnd = clock();	
	//5.Time calculation presents
	difftime = (float)(tEnd-tStart)/CLOCKS_PER_SEC;
	printf("The cost time of tate pairing: %fs\n",difftime);



	return 0;
}
