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

void inicializar_semilla();
void aleatorio(int v[], int n);
void ascendente(int v[], int n);
void descendente(int v[], int n);
void montDescendente();
void montAscendente();
void montAleatorio();
bool ordenado(int v[], int n);
void preguntaOrdenado(bool ord);
void mostrarVector(int v[], int n);
void ordenarPorMonticulos(int v[], pmonticulo m, int n);
void iniMonticulo(pmonticulo *m);
#endif
