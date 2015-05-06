#include "/usr/local/include/pbc/pbc.h"
#include "LSSS.h"
#include "weilPairing.h"
#ifndef _W_ABE_SETUP
#define _W_ABE_SETUP

void generatePrime(mpz_t *p,int sBit);
//generate prime number
void setupPairing(pairing_t *pairing);
void setupOrdinaryPairing(pairing_t *pairing);
//setup the pairing
void wSetup(char *string,int attrNo,pairing_t *pairing, MSP *msp);
//the first setup of cp-abe protocol -- setup
#endif
