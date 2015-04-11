#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
#include <stdio.h>
#include <stdlib.h>

int genSecret(int prime){


}//generate the secret

void mspInit(MSP *msp,int rows,int cols){
	
	msp -> matrix = calloc(rows,sizeof(int *));
	int i = 0;
	for( i = 0; i<rows; i++){
		(msp -> matrix)[i] = calloc(cols,sizeof(int));
	}
	msp -> label = calloc(rows,sizeof(char *));
	msp -> rows = rows;
	msp -> cols = cols;
	return ;
}//initialize the msp
void mspClear(MSP *msp){
	int i = 0;
	for( i = 0;i < msp->rows; i++){
		free((msp->matrix)[i]);
	}
	free(msp -> matrix);
	free(msp -> label);
	return;
}//clear the msp
//Assume attribute is:prof,vProf,aProf,lecturer,phd,graduate,unGraduate
//the boolean formaular is (A AND B) OR (C AND (D AND E))
void mspSetup(MSP *msp){
/*	
	msp->matrix[0]={1,0,1};//A
	msp->matrix[1]={1,0,-1};//B
	msp->matrix[2]={0,1,0};//C
	msp->matrix[3]={0,0,1};//D
	msp->matrix[4]={1,-1,-1};//E
*/
}


