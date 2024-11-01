all: p2 test

p2: prac2.c funciones.c funciones.h
	gcc -o prac2.out -Wall prac2.c funciones.c funciones.h -lm
	
clear_p2:
	rm *.out
	
	
test: test.c funciones.c funciones.h
	gcc -o test.out -Wall funciones.c funciones.h test.c -lm
	
clear_test:
	rm *.out
