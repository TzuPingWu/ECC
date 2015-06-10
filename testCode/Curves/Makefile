all: curve
curve: curve.o
	gcc -o curve curve.o -L. -lpbc -lgmp
curve.o: curve.c
	gcc -c curve.c 
