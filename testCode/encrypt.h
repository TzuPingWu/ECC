#ifndef _ENCRYPT_H
#define _ENCRYPT_H
#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
void encrypt(element_t message,pairing_t pairing,MSP *msp,int attrNo);//the function to encrypt the message
void matrixMul(element_t *lambda,element_t *temp,element_t *y,MSP *msp);//the multiplication of matrix
void findOmega(element_t *omega,element_t *lambda,element_t s,pairing_t pairing,int rows);//omega * lambda = s
#endif