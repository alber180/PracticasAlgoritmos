all: p3 test

p3: p3.c funciones.c funciones.h
	gcc -g -o p3.out -Wall p3.c funciones.c funciones.h -lm
	
clear_p3:
	rm *.out
	
	
test: test.c funciones.c funciones.h
	gcc -g -o test.out -Wall funciones.c funciones.h test.c -lm
	
clear_test:
	rm *.out
