#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
int main()
{
    item data[19062];
    int ins;
    inicializar_semilla();
    ins = leer_sinonimos(data);

    // Insertamos y leemos los datos para hacer las mediciones:
    printf("\n***DISPERSION A - EXPLORACION LINEAL\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionA, exploracion_lineal);
    }

    printf("\n***DISPERSION A - EXPLORACION CUADRATICA\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionA, exploracion_cuadratica);
    }

    printf("\n***DISPERSION A - EXPLORACION DOBLE\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionA, exploracion_doble);
    }
    printf("\n***DISPERSION B - EXPLORACION LINEAL\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionB, exploracion_lineal);
    }

    printf("\n***DISPERSION B - EXPLORACION CUADRATICA\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionB, exploracion_cuadratica);
    }

    printf("\n***DISPERSION B - EXPLORACION DOBLE\n");
    for (int i = 0; i < 3; i++)
    {
        datos(data, ins, dispersionB, exploracion_doble);
    }
    return 0;
}