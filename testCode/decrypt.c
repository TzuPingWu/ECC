#include "/usr/local/include/pbc/pbc.h"
#include "decrypt.h"
#include "elementIO.h"
#include "LSSS.h"
#include <stdio.h>
#include <stdlib.h>

void decrypt(pairing_t pairing,MSP *msp,element_t message){
	
	//file pointer to read the ciphertext and private key
	FILE *fG = fopen("publicKey/g.key","r");
	FILE *fGA = fopen("publicKey/gA.key","r");
	FILE *fC = fopen("cipher/C.cipher","r");
	FILE *fC_0 = fopen("cipher/C_0.cipher","r");
	FILE *fC_rows = fopen("cipher/C_rows.cipher","r");
	FILE *fD_rows = fopen("cipher/D_rows.cipher","r");
	FILE *fK = fopen("privateKey/K.key","r");
	FILE *fL = fopen("privateKey/L.key","r");
	FILE *fK_0= fopen("privateKey/Kx0.key","r");
	FILE *fOmega = fopen("privateKey/omega.key","r");
	FILE *fT = fopen("privateKey/t.key","r");
	
	int i = 0;//the index for the following for-loop
	int rows = msp->rows;//the rows of msp
	element_t gA;//gA = g^a
	element_t g;//g
	element_t C;//C = M*e(g,g)^(aplha*s)
	element_t gS;//gS = g^s
	element_t cipher_r[rows];
	element_t d_r[rows];
	element_t K;//private key K
	element_t L;//private key L
	element_t Kx0;//private key for attribute A user
	element_t omega[rows];//omega *lambda = s
	element_init_G2(g,pairing);
	element_init_G2(gA,pairing);
	element_init_GT(C,pairing);
	element_init_G2(gS,pairing);
	element_init_G2(K,pairing);
	element_init_G2(L,pairing);
	element_init_G2(Kx0,pairing);
	element_fread(fG,"%s %s",&g,10);
	element_fread(fGA,"%s %s",&gA,10);
	element_fread(fC,"%s %s",&C,10);
	element_fread(fC_0,"%s %s",&gS,10);
	element_fread(fK,"%s %s",&K,10);
	element_fread(fL,"%s %s",&L,10);
	element_fread(fK_0,"%s %s",&Kx0,10);
	
	for(i = 0; i < rows; i++){
		element_init_G2(cipher_r[i],pairing);
		element_init_G2(d_r[i],pairing);
		element_init_Zr(omega[i],pairing);
		element_fread(fC_rows,"%s %s\n",&cipher_r[i],10);
		element_fread(fD_rows,"%s %s\n",&d_r[i],10);
		element_fread(fOmega,"%s\n",&omega[i],10);
	}
	///////finish reading the ciphertext and key from file////////
	//////close the file poitner
	fclose(fGA);
	fclose(fC);
	fclose(fC_0);
	fclose(fC_rows);
	fclose(fD_rows);
	fclose(fK);
	fclose(fL);
	fclose(fK_0);
	//test
	
	element_t t;
	element_t mid;
	element_t eGGAST;
	element_init_Zr(t,pairing);
	element_init_GT(mid,pairing);	
	element_init_GT(eGGAST,pairing);
	element_fread(fT,"%s",&t,10);
//	element_printf("t = %B\n",t);
	element_pairing(mid,gA,gS);
	element_pow_zn(eGGAST,mid,t);
	element_printf("denominator1 = %B\n",eGGAST);
	//test
	//start to decrypt the ciphertext
	element_t eGGAlphaS;//e(g,g)^alphaS
	element_t eGGgSK;//e(C',K)
	element_t eCL;//e(C_i,L)
	element_t eDKx;//e(D_i,Kx)
	element_t denominator;
	element_t temp;
	element_t plaintext;
	//numerator
	element_init_GT(eGGAlphaS,pairing);
	element_init_GT(eGGgSK,pairing);
	//denominator
	element_init_GT(eCL,pairing);
	element_init_GT(eDKx,pairing);
	element_init_GT (temp,pairing);
	element_init_GT(denominator,pairing);
	//plaintext
	element_init_GT(plaintext,pairing);
	//start to calculate
	element_pairing(eGGgSK,gS,K);
	element_pairing(eCL,cipher_r[0],L);
	element_pairing(eDKx,d_r[0],Kx0);
	element_set0(temp);
	element_mul(temp,eCL,eDKx);
	element_pow_zn(denominator,temp,omega[0]);
	element_printf("denominator2 = %B\n",denominator);
	element_div(eGGAlphaS,eGGgSK,denominator);
	
	element_printf("eGGalphaS2 = %B\n",eGGAlphaS);
	element_div(plaintext,C,eGGAlphaS);
	element_printf("M2 = %B\n",plaintext);


}
