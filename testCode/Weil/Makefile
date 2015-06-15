all: wAbe
wAbe: wAbe.o weilPairing.o wAbeSetup.o keyGen.o LSSS.o elementIO.o encrypt.o wDecrypt.o
	gcc -o wAbe wAbe.o weilPairing.o wAbeSetup.o keyGen.o LSSS.o elementIO.o encrypt.o wDecrypt.o -L. -lpbc -lgmp
wAbe.o: wAbe.c
	gcc -c wAbe.c
weilPairing.o: weilPairing.c weilPairing.h
	gcc -c weilPairing.c
wAbeSetup.o: wAbeSetup.c wAbeSetup.h weilPairing.h
	gcc -c wAbeSetup.c
keyGen.o: keyGen.c keyGen.h
	gcc -c keyGen.c
LSSS.o: LSSS.c LSSS.h
	gcc -c LSSS.c
elementIO.o: elementIO.c elementIO.h
	gcc -c elementIO.c
encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c
wDecrypt.o: wDecrypt.c wDecrypt.h
	gcc -c wDecrypt.c
