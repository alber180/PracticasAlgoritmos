#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
int main()
{
    pmonticulo m;
    inicializar_semilla();
    iniMonticulo(&m);
    int v[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 10; i++)
    {
        m->vector[i] = v[i];
    }
    m->ultimo = 10;
    mostrarmont(m);
    mostrar(m);
    free(m);
    return 0;
}