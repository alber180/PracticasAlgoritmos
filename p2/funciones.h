/*
Luis Alfonso Rodriguez Rodriguez---luis.rodriguezr@udc.es
Alberto Paz Perez---a.pazp@udc.es
Sergio Rego Criado---sergio.rego.criado@udc.es
*/

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

#define MAX_NUM 32000

void inicializar_semilla();
void aleatorio(int v[], int n);
void ascendente(int v[], int n);
void descendente(int v[], int n);
void ord_ins(int v[], int n);
void intercambiar(int *v, int *u);
void ord_rap_aux(int v[], int iz, int dr);
void ord_rap(int v[], int n);
double microsegundos();
void mostrarVector(int v[], int n);
bool ordenado(int v[], int n);
#endif