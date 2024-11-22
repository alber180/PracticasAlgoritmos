#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define TAM 256000
struct monticulo
{
    int ultimo;
    int vector[TAM];
};
typedef struct monticulo *pmonticulo;

void mostrarCabecera();
void imprimirSalida(int n, int k, double t, double x, double y, double z);
void inicializar_semilla();
double microsegundos();

void iniMonticulo(pmonticulo *m);
void insertarMonticulo(pmonticulo m, int x);
void quitarMenor(pmonticulo m);
int consultarMenor(const pmonticulo m);
void crearMonticulo(pmonticulo m, int v[], int n);
void hundir(pmonticulo m, int i);
void flotar(pmonticulo m, int i);
void intercambiar(int *v, int *u);
void mostrarmont(pmonticulo m);
void mostrar(pmonticulo m);

/*
double tiempos(unsigned int (*dispersion)(char *, int),
               unsigned int (*resol_colisiones)(int pos_ini, int num_intento),
               tabla_cerrada diccionario, item data[], int tam,
               int n, int *k);
double tiempos_K_veces(unsigned int (*dispersion)(char *, int),
                       unsigned int (*resol_colisiones)(int pos_ini, int num_intento),
                       tabla_cerrada diccionario, item data[],
                       int tam, int n, int k);


int obtener_K(int t);
void datos(item data[], int ins, unsigned int (*dispersion)(char *, int),
           unsigned int (*resol_colisiones)(int pos_ini, int num_intento));*/
#endif
