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
void montDescendente();
void montAscendente();
void montAleatorio();
#endif
