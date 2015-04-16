#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
#include <stdio.h>
#include <stdlib.h>	

void mspInit(MSP *msp,int rows,int cols){
	/*int i,j = 0; 
	msp -> matrix = (mpz_t **)malloc(rows * sizeof(mpz_t *));
	for(i = 0; i < rows; i++){
      (msp -> matrix)[i] = (mpz_t *)malloc(cols*sizeof(mpz_t));
	   for(j = 0;j < cols;j++){
		mpz_init_set_si(msp->matrix[i][j],0);
	   }
	}
	*/
	msp -> matrix = malloc(rows * sizeof(int*));
	int i = 0;
	for(i; i < rows; i++){
		(msp -> matrix)[i] = calloc(cols, sizeof(int));
	}
	msp -> label = calloc(rows,sizeof(char *));
	msp -> rows = rows;
	msp -> cols = cols;
	return ;
}//initialize the msp
void mspClear(MSP *msp){
	int i = 0;
	for(i = 0;i < msp->rows;i++){
		free((msp->matrix)[i]);
	}
	free(msp -> matrix);
	free(msp -> label);
	return;
}//clear the msp
void mspSetup(MSP *msp){
	mspInit(msp,5,3);
	msp -> label[0] = "A";
	msp -> label[1] = "B";
	msp -> label[2] = "C";
	msp -> label[3] = "D";
	msp -> label[4] = "E";
	
	//label the row of matrix
	/*
	mpz_set_si(msp -> matrix[0][0],1);
	mpz_set_si(msp -> matrix[0][1],0);
	mpz_set_si(msp -> matrix[0][2],0);
	mpz_set_si(msp -> matrix[0][3],0);
	//attribute A
	mpz_set_si(msp -> matrix[1][0],1);
	mpz_set_si(msp -> matrix[1][1],1);
	mpz_set_si(msp -> matrix[1][2],0);
	mpz_set_si(msp -> matrix[1][3],0);
	//attribute B
	mpz_set_si(msp -> matrix[2][0],1);
	mpz_set_si(msp -> matrix[2][1],1);
	mpz_set_si(msp -> matrix[2][2],0);
	mpz_set_si(msp -> matrix[2][3],0);
	//attribute C
	mpz_set_si(msp -> matrix[3][0],1);
	mpz_set_si(msp -> matrix[3][1],-1);
	mpz_set_si(msp -> matrix[3][2],-1);
	mpz_set_si(msp -> matrix[3][3],1);
	//attribute D
	mpz_set_si(msp -> matrix[4][0],0);
	mpz_set_si(msp -> matrix[4][1],0);
	mpz_set_si(msp -> matrix[4][2],1);
	mpz_set_si(msp -> matrix[4][3],-1);	
	//attribute E
	*/
	msp -> matrix[0][0] = 1;
	msp -> matrix[0][1] = 0;
	msp -> matrix[0][2] = 0;
	//attribute A
	msp -> matrix[1][0] = 1;
	msp -> matrix[1][1] = 1;
	msp -> matrix[1][2] = 0;
	//attribute B
	msp -> matrix[2][0] = 1;
	msp -> matrix[2][1] = 1;
	msp -> matrix[2][2] = 0;
	//attribute C
	msp -> matrix[3][0] = 0;
	msp -> matrix[3][1] = -1;
	msp -> matrix[3][2] = 1;
	//attribute D
	msp -> matrix[4][0] = 0;
	msp -> matrix[4][1] = 0;
	msp -> matrix[4][2] = -1;	
	//attribute E
	return;
}


