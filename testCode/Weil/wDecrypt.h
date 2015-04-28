#ifndef _W_DECRYPT_H
#define _W_DECRYPT_H
#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
void wDecrypt(pairing_t pairing,MSP *msp,element_t message);//the main function of decryption
void wFindOmega(MSP *msp,element_t *omega);//find the omega according to the msp->matrix
void wSwap(int *A,int *B);
#endif