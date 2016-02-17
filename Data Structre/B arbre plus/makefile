main :  test_Barbre.o barbre.o barbre_bis.o
	gcc -Wall -g -I. test_Barbre.o barbre.o barbre_bis.o -o main 
main.o : main.c barbre.h
	gcc -Wall -g -c -I. -L. test_Barbre.c -o  test_Barbre.o
barbre.o : barbre.c barbre.h
	gcc -Wall -g -c -I. -L. barbre.c -o barbre.o 	
barbre_bis.o : barbre_bis.h barbre_bis.c
	gcc -Wall -g -c -I. -L. barbre_bis.c -o barbre_bis.o
