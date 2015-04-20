#include "/usr/local/include/pbc/pbc.h"
#include "keyGen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "elementIO.h"

void keyGen(pairing_t pairing,int attrNo){
	
	FILE *fMsk = fopen("MSK/msk.key","r");//fMsk to read the master key
	FILE *fG = fopen("publicKey/g.key","r");//fG to read the public key -genterator g
	FILE *fGA = fopen("publicKey/gA.key","r");//fGA to read the public key -gA
	FILE *fH = fopen("publicKey/h.key","r");//fH to read the public key-h[x]

	element_t g;//generator g
	element_t gA;//gA = g^A
	element_t msk;//msk = g^alpha
	element_t h[attrNo];//h[0]...h[attrNo-1]
	element_init_G2(g,pairing);
	element_fread(fG,"%s %s",&g,10);
	//element_printf("g= %B\n",g);
	element_init_G2(gA,pairing);
	element_fread(fGA,"%s %s",&gA,10);
	//element_printf("gA= %B\n",gA);
	element_init_G2(msk,pairing);
	
	int i = 0;
	for(i = 0;i < attrNo;i++){
		element_init_G2(h[i],pairing);
		element_fread(fH,"%s %s\n",&h[i],10);
		//element_printf("h[%d]=%B\n",i,h[i]);
	}

	element_fread(fMsk,"%s %s",&msk,10);
	//element_printf("MSK= %B\n",msk);
	//close all file pointer
	fclose(fG);
	fclose(fGA);
	fclose(fH);
	fclose(fMsk);
	//end of read file
	//start to calculate private key and write file
	element_t t;//the random t over Z_p
	element_t L;//L = g^t
	element_t K;//K = (g^alpha)*(g^at)
	element_t Kx;//Kx = hx^t
	element_t temp;
	element_init_Zr(t,pairing);
	element_init_G2(L,pairing);
	element_init_G2(K,pairing);
	element_init_G2(Kx,pairing);
	element_init_G2(temp,pairing);
	FILE *fL = fopen("privateKey/L.key","w");//fL to write the privateKey L
	FILE *fK = fopen("privateKey/K.key","w");//fK to write the privateKey K
	FILE *fKx = fopen("privateKey/Kx.key","w");//fKx to write the privateKey fKx
	
	element_random(t);
	element_pow_zn(L,g,t);
	element_fprintf(fL,"%B",L);
	element_pow_zn(temp,gA,t);//first K = g^at
	element_mul(K,temp,msk);//second K = K*g^alpha
	element_fprintf(fK,"%B",K);
	
	for( i = 0; i  < attrNo; i++){
		element_set0(Kx);
		element_pow_zn(Kx,h[i],t);//Kx = hx^t
		element_fprintf(fKx,"%B\n",Kx);//Kx = hx^t
	}
	//close all file pointer
	fclose(fL);
	fclose(fK);
	fclose(fKx);	
}//end of keyGen
