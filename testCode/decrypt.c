#include "/usr/local/include/pbc/pbc.h"
#include "decrypt.h"
#include "elementIO.h"
#include "LSSS.h"
#include <stdio.h>
#include <stdlib.h>

void decrypt(pairing_t pairing,MSP *msp){
	
	//file pointer to read the ciphertext
	FILE *fC = fopen("cipher/C.cipher","r");
	FILE *fC_0 = fopen("cipher/C_0.cipher","r");
	FILE *fC_rows = fopen("cipher/C_rows.cipher","r");
	FILE *fD_rows = fopen("cipher/D_rows.cipher","r");
	
	int i = 0;//the index for the following for-loop
	int rows = msp->rows;//the rows of msp
	element_t C;//C = M*e(g,g)^(aplha*s)
	element_t gS;//gS = g^s
	element_t cipher_r[rows];
	element_t d_r[rows];
	element_init_G2(C,pairing);
	element_init_G2(gS,pairing);
	element_fread(fC,"%s %s\n",&C,10);
	element_fread(fC_0,"%s %s\n",&gS,10);
	for(i = 0; i < rows; i++){
		element_init_G2(cipher_r[i],pairing);
		element_init_G2(d_r[i],pairing);
		element_fread(fC_rows,"%s %s\n",&cipher_r[i],10);
		element_fread(fD_rows,"%s %s\n",&d_r[i],10);
	}
	

}
