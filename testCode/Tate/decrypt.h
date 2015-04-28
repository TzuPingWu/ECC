#ifndef _DECRYPT_H
#define _DECRYPT_H
#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
void decrypt(pairing_t pairing,MSP *msp,element_t message);//the main function of decryption
void findOmega(MSP *msp,element_t *omega);//find the omega according to the msp->matrix
void swap(int *A,int *B);
#endif