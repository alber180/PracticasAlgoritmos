#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int leer_sinonimos(item datos[])
{
    char c;
    int i, j;
    FILE *archivo;
    if ((archivo = fopen("sinonimos.txt", "r")) == NULL)
    {
        printf("Error al abrir 'sinonimos.txt'\n");
        return (EXIT_FAILURE);
    }
    for (i = 0; fscanf(archivo, "%s", datos[i].clave) != EOF; i++)
    {
        if ((c = fgetc(archivo)) != '\t')
        {
            printf("Error al leer el tabulador\n");
            return (EXIT_FAILURE);
        }
        for (j = 0; (c = fgetc(archivo)) != '\n'; j++)
        {
            if (j < LONGITUD_SINONIMOS - 1)
                datos[i].sinonimos[j] = c;
        }
        datos[i].sinonimos[MIN(j, LONGITUD_SINONIMOS - 1)] = '\0';
    }
    if (fclose(archivo) != 0)
    {
        printf("Error al cerrar el fichero\n");
        return (EXIT_FAILURE);
    }
    return (i);
}