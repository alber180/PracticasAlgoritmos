#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
                   int *colisiones, pos (*dispersion)(char *, int),
                   pos (*resol_colisiones)(pos pos_ini, int num_intento));

int insertar_cerrada(char *clave, char *sinonimos,
                     tabla_cerrada *diccionario, int tam,
                     pos (*dispersion)(char *, int),
                     pos (*resol_colisiones)(pos pos_ini, int num_intento));

void mostrar_cerrada(tabla_cerrada diccionario, int tam);

pos dispersionA(char *clave, int tamTabla);
pos dispersionB(char *clave, int tamTabla);
int ndispersion(char *clave, int tamTabla);

pos exploracion_lineal(pos pos_ini, int incremento);
pos exploracion_cuadratica(pos pos_ini, int incremento);
pos exploracion_doble(pos pos_ini, int incremento);
pos exploracion_doble_test(int pos_ini, int num_intento);
int leer_sinonimos(item datos[]);
#endif
