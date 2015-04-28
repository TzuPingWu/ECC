#include "/usr/local/include/pbc/pbc.h"

#ifndef _W_ABE_SETUP
#define _W_ABE_SETUP

void generatePrime(mpz_t *p,int sBit);
//generate prime number
void setupPairing(pairing_t *pairing);
//setup the pairing
void wSetup(int attrNo,pairing_t *pairing);
//the first setup of cp-abe protocol -- setup
#endif
