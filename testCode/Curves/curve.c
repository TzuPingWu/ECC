#include"/usr/local/include/pbc/pbc.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void generateOrdinary(pairing_t *pairing,int bits){
  pbc_param_t param;
  pbc_param_init_f_gen(param, bits);
  pairing_init_pbc_param(*pairing,param);
  pbc_param_clear(param);
}
void generateSupersingular(pairing_t *pairing,int rbits,int qbits){
	pbc_param_t param;
	pbc_param_init_a_gen(param,rbits,qbits);//using type a curve
	pairing_init_pbc_param(*pairing,param);
	pbc_param_clear(param);
	return;
}

int main(int argc, char **argv) {

 if(argc < 3){
 	fprintf(stderr,"Wrong input arguments!");		
	fprintf(stderr,"Please input <./curve><supersinuglar><rbits><qbits> or <./curve><ordinary><bits>\n");
 }else{
	//initialization
	pairing_t pairing;
	element_t g,h,temp1;
	int rbits, qbits;
	if(!strcmp(argv[1],"supersingular")&&argc==4){//to generate supersingualr curve
		rbits = atoi(argv[2]);
		qbits = atoi(argv[3]);
		generateSupersingular(&pairing,rbits,qbits);
		printf("generate supersingular curve...");
	}else if(!strcmp(argv[1],"ordinary")&&argc==3){//to generate ordinary curve
		rbits = atoi(argv[2]);
		generateOrdinary(&pairing,256);
		printf("generate ordinary curve...");
	}else{
		fprintf(stderr,"Wrong input arguments!");		
		fprintf(stderr,"Please input  <./curve><supersinuglar><rbits><qbits> or <./curve><ordinary><bits>\n");
		return 0;
	}
	if(pairing_is_symmetric(pairing)){
		printf("pairing is symmetric\n");
	}else{
		printf("pairing is NOT symmetric\n");
	}
	clock_t start,end;//start:the start of pairing, end:the end of pairing
	float difftime=0.0;
	element_init_G1(g, pairing);
	element_init_G2(h, pairing);
	element_init_GT(temp1, pairing);
	element_random(g);
	element_random(h);	
	start = clock();
	element_pairing(temp1, g, h);
	end = clock();
	difftime = (float)(end-start)/CLOCKS_PER_SEC;
	printf("The time of using pairing is %f\n",difftime);
 }//end of main-else

  return 0;
}
