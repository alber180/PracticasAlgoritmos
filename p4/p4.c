#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
int main()
{
    int i;
    inicializar_semilla();
    for (i = 0; i < 3; i++)
    {
        montAleatorio();
    }

    return 0;
}