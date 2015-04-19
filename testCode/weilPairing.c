#include <stdio.h>
#include <stdlib.h>
#include "/usr/local/include/pbc/pbc.h"
#include "weilPairing.h"

void weilPairing(element_t *out,element_t in1,element_t in2,pairing_t pairing){
	element_t temp1,temp2;
	element_init_GT(temp1,pairing);
	element_init_GT(temp2,pairing);
	pairing_apply(temp1,in1,in2,pairing);
	pairing_apply(temp2,in2,in1,pairing);
	element_div(*out,temp1,temp2);
	return;
}
