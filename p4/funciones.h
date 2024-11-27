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
void OrdenarPorMonticulos(int *v[], int n);
void aleatorio(int v[], int n);
void descendente(int v[], int n);
void ascendente(int v[], int n);
bool ordenado(int v[], int n);
void montDescendente();
void montAscendente();
void montAleatorio();
#endif
