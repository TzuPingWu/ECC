#include "/usr/local/include/pbc/pbc.h"
#include "decrypt.h"
#include "elementIO.h"
#include "LSSS.h"
#include <stdio.h>
#include <stdlib.h>
void wSwap(int *A,int *B){
	int temp;
	temp = *A;
	*A = *B;
	*B = temp;
	return;
}

void wFindOmega(MSP *msp,element_t *omega){
	
	int rows = 3;
	int cols = msp->cols;
	int sum = 0;
	int k, i, j; //the index of the for-loop
	int tempMatrix[rows][rows*2];
	int inverseMatrix[rows][rows];
	int identity[rows];
	int result[rows];
	int middle[rows][rows];
	tempMatrix[0][0] = 1;
	tempMatrix[0][1] = 1;
	tempMatrix[0][2] = 0;
	tempMatrix[1][0] = 0;
	tempMatrix[1][1] = -1;
	tempMatrix[1][2] = 1;
	tempMatrix[2][0] = 0;
	tempMatrix[2][1] = 0;
	tempMatrix[2][2] = -1;
	identity[0] = 1;
	identity[1] = 0;
	identity[2] = 0;
	//initialize the target array
	//start to find the inverse matrix
    for (i=0; i<rows; ++i)
        for (j=0; j<rows; ++j)
            tempMatrix[i][rows+j] = 0;
 
    for (i=0; i<rows; ++i)
        tempMatrix[i][rows+i] = 1;
 
    for (i=0; i<rows; ++i)
    {
        if (tempMatrix[i][i] == 0)
            for (j=i+1; j<rows; ++j)
                if (tempMatrix[j][i] != 0)
                {
                    for (k=i; k<rows*2; ++k)
                        wSwap(&tempMatrix[i][k], &tempMatrix[j][k]);
                    break;
                }
 
        if (tempMatrix[i][i] == 0) return;
 
        double t = tempMatrix[i][i];
        for (k=i; k<rows*2; ++k)
            tempMatrix[i][k] /= t;
 
        for (j=0; j<rows; ++j)
            if (i != j && tempMatrix[j][i] != 0)
            {
                double t = tempMatrix[j][i];
                for (k=i; k<rows*2; ++k)
                    tempMatrix[j][k] -= tempMatrix[i][k] * t;
            }
    }
	
	for( i = 0 ; i < rows; i++){
		for( j = 0; j < rows; j++){
			inverseMatrix[i][j] = tempMatrix[i][rows+j];
	//		printf("temp[%d][%d] = %d",i,j,inverseMatrix[i][j]);
		}
	//		printf("\n");
	}
	for( i = 0 ; i < rows; i++){
		result[i] = 0;
		for( j = 0 ; j < rows; j++){
			result[i] += identity[j]*inverseMatrix[j][i];
		}
		if(result[i] == 0){
			element_set0(omega[i]);
		}else if(result[i] == 1){
			element_set1(omega[i]);
		}else if(result[i] == -1){
			element_set1(omega[i]);
			element_neg(omega[i],omega[i]);
		}
		//printf("result[%d] = %d\n",i,result[i]);
		//element_printf("omega[%d] = %B\n",i,omega[i]);
	}
	
	return;
}
void wDecrypt(pairing_t pairing,MSP *msp,element_t message){
	
	//file pointer to read the ciphertext and private key
	FILE *fG = fopen("publicKey/g.key","r");
	FILE *fGA = fopen("publicKey/gA.key","r");
	FILE *fC = fopen("cipher/C.cipher","r");
	FILE *fC_0 = fopen("cipher/C_0.cipher","r");
	FILE *fC_rows = fopen("cipher/C_rows.cipher","r");
	FILE *fD_rows = fopen("cipher/D_rows.cipher","r");
	FILE *fK = fopen("privateKey/K.key","r");
	FILE *fL = fopen("privateKey/L.key","r");
	FILE *fKx= fopen("privateKey/Kx.key","r");
	FILE *fOmega = fopen("privateKey/omega.key","r");
	
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
	element_t Kx[rows];//private key for attribute A user
	element_t omega[rows];//omega *lambda = s
	element_init_G2(g,pairing);
	element_init_G2(gA,pairing);
	element_init_GT(C,pairing);
	element_init_G2(gS,pairing);
	element_init_G2(K,pairing);
	element_init_G2(L,pairing);
	element_fread(fG,"%s %s",&g,10);
	element_fread(fGA,"%s %s",&gA,10);
	element_fread(fC,"%s %s",&C,10);
	element_fread(fC_0,"%s %s",&gS,10);
	element_fread(fK,"%s %s",&K,10);
	element_fread(fL,"%s %s",&L,10);
	
	for(i = 0; i < rows; i++){
		element_init_G2(cipher_r[i],pairing);
		element_init_G2(d_r[i],pairing);
		element_init_Zr(omega[i],pairing);
		element_init_G2(Kx[i],pairing);
		element_fread(fC_rows,"%s %s\n",&cipher_r[i],10);
		element_fread(fD_rows,"%s %s\n",&d_r[i],10);
	//	element_fread(fOmega,"%s\n",&omega[i],10);	
		element_fread(fKx,"%s %s",&Kx[i],10);
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
	fclose(fKx);
	
	wFindOmega(msp,omega);
	//test
	element_t mid;
	element_t eGGAST;
	element_t eGHRT;
	element_t eGGATL_eGHRT;
	element_t hTInverse;
	//element_init_Zr(t,pairing);
	element_init_GT(hTInverse,pairing);
	element_init_GT(mid,pairing);	
	element_init_GT(eGGAST,pairing);
	element_init_GT(eGHRT,pairing);
	element_init_GT(eGGATL_eGHRT,pairing);
	weilPairing(&mid,gA,gS,pairing);
	//element_pow_zn(eGGAST,mid,t);
	weilPairing(&eGHRT,Kx[0],d_r[0],pairing);
	element_invert(hTInverse,eGHRT);
	element_mul(eGGATL_eGHRT,eGGAST,hTInverse);
	//element_printf("t = %B\n",t);
	//element_printf("denominator1 = %B\n",eGGAST);
	//element_printf("eCL1 = %B\n",eGGATL_eGHRT);
	//test
	//start to decrypt the ciphertext
	element_t eGGAlphaS;//e(g,g)^alphaS
	element_t eGGgSK;//e(C',K)
	element_t eCL;//e(C_i,L)
	element_t eCL2;//e(C_i,L)
	element_t eCL3;//e(C_i,L)

	element_t eDKx;//e(D_i,Kx)
	element_t eDKx2;//e(D_i,Kx)
	element_t eDKx3;//e(D_i,Kx)

	element_t denominator;
	element_t temp;
	element_t temp2;
	element_t temp3;
	element_t temp4;
	element_t plaintext;
	//numerator
	element_init_GT(eGGAlphaS,pairing);
	element_init_GT(eGGgSK,pairing);
	//denominator
	element_init_GT(eCL,pairing);
	element_init_GT(eCL2,pairing);
	element_init_GT(eCL3,pairing);
	
	element_init_GT(eDKx,pairing);
	element_init_GT(eDKx2,pairing);
	element_init_GT(eDKx3,pairing);
	
	element_init_GT (temp,pairing);
	element_init_GT (temp2,pairing);
	element_init_GT (temp3,pairing);
	element_init_GT (temp4,pairing);

	element_init_GT(denominator,pairing);
	//plaintext
	element_init_GT(plaintext,pairing);
	//start to calculate
	weilPairing(&eGGgSK,gS,K,pairing);
	weilPairing(&eCL,cipher_r[2],L,pairing);
	weilPairing(&eCL2,cipher_r[3],L,pairing);
	weilPairing(&eCL3,cipher_r[4],L,pairing);
	weilPairing(&eDKx,d_r[2],Kx[2],pairing);
	weilPairing(&eDKx2,d_r[3],Kx[3],pairing);
	weilPairing(&eDKx3,d_r[4],Kx[4],pairing);
	
	element_set0(temp);
	element_set0(temp2);
	element_set0(temp3);
	element_set0(temp4);
	element_set0(denominator);
	element_mul(temp,eCL,eDKx);
	element_pow_zn(temp,temp,omega[0]);
	element_mul(temp2,eCL2,eDKx2);
	element_pow_zn(temp2,temp2,omega[1]);
	element_mul(temp3,eCL3,eDKx3);
	element_pow_zn(temp3,temp3,omega[2]);
	element_mul(temp4,temp,temp2);
	element_mul(denominator,temp4,temp3);
//	element_printf("test1 = %B\ntest2 = %B\n,test3 = %B\n",temp,temp2,temp3);
	element_mul(temp4,temp,temp2);
	element_mul(denominator,temp4,temp3);
//	element_pow_zn(denominator,temp,omega[0]);
//	element_printf("denominator3 = %B\n",denominator);
	element_div(eGGAlphaS,eGGgSK,denominator);
	
	//element_printf("eGGalphaS2 = %B\n",eGGAlphaS);
	element_div(plaintext,C,eGGAlphaS);
	element_printf("M2 = %B\n",plaintext);


}
