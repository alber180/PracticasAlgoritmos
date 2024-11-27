all: p4 test

p4: p4.c funciones.c funciones.h
	gcc -g -o p4.out -Wall p4.c funciones.c funciones.h -lm
	
clear_p4:
	rm *.out
	
	
test: test.c funciones.c funciones.h
	gcc -o test.out -Wall funciones.c funciones.h test.c -lm
	
clear_test:
	rm *.out
