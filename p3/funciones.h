#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#define LONGITUD_CLAVE 30
#define LONGITUD_SINONIMOS 300
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

typedef struct
{
    int ocupada;
    char clave[LONGITUD_CLAVE];
    char sinonimos[LONGITUD_SINONIMOS];
} item;

typedef int pos;
typedef item *tabla_cerrada;

void inicializar_cerrada(tabla_cerrada *diccionario, int tam);

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
                   int *colisiones, unsigned int (*dispersion)(char *, int),
                   unsigned int (*resol_colisiones)(int pos_ini, int num_intento));

int insertar_cerrada(char *clave, char *sinonimos,
                     tabla_cerrada *diccionario, int tam,
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(pos pos_ini, int num_intento));

void mostrar_cerrada(tabla_cerrada diccionario, int tam);

unsigned int dispersionA(char *clave, int tamTabla);
unsigned int dispersionB(char *clave, int tamTabla);
unsigned int ndispersion(char *clave, int tamTabla);

unsigned int exploracion_lineal(pos pos_ini, int incremento);
unsigned int exploracion_cuadratica(pos pos_ini, int incremento);
unsigned int exploracion_doble(pos pos_ini, int incremento);
unsigned int exploracion_doble_test(int pos_ini, int num_intento);

void mostrarCabecera();
void imprimirSalida(int n, bool esMenor, double t, double x, double y, double z);
int leer_sinonimos(item datos[]);

void mostrarCabecera();
void imprimirSalida(int n, bool esMenor, double t, double x, double y, double z);
 double datos(unsigned int (*dispersion)(char *, int),
            unsigned int (*resol_colisiones)(int pos_ini, int num_intento), bool *esMenor,
         tabla_cerrada diccionario, item data[], int tam, int n);
void inicializar_semilla();
double microsegundos();
int obtener_K(int t, bool *esMenor);
void dispA_lineal(item data[], int ins);
void dispA_cuadr(item data[], int ins);
void dispA_doble(item data[], int ins);
void dispB_lineal(item data[], int ins);
void dispB_cuadr(item data[], int ins);
void dispB_doble(item data[], int ins);
#endif
