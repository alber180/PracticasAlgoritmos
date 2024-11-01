#include "funciones.h"

pos dispersionA(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor += clave[i];
    return valor % tamTabla;
}

pos dispersionB(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor = (valor << 5) + clave[i]; /* el desplazamiento de 5 bits equivale a */
    return valor % tamTabla;             /* multipicar por 32 */
}

pos exploracion_lineal(pos pos_ini, int incremento)
{
    return pos_ini + incremento;
}

pos exploracion_cuadratica(pos pos_ini, int incremento)
{
    return pos_ini + incremento * incremento;
}

pos exploracion_doble(int pos_ini, int num_intento)
{
    return (pos_ini + (10007 - num_intento) % 10007);
}

void inicializar_cerrada(tabla_cerrada *diccionario, int tam)
{
    *diccionario = malloc(tam * sizeof(item));
    if (*diccionario == NULL)
    {
        perror("Error al asignar memoria\n");
    }

    for (int i = 0; i < tam; i++)
    {
        (*diccionario)[i].ocupada = 0;
        (*diccionario)[i].clave[0] = '\0';
        (*diccionario)[i].sinonimos[0] = '\0';
    }
}

pos buscar_cerrada(char *clave, tabla_cerrada diccionario, int tam,
                   int *colisiones, pos (*dispersion)(char *, int),
                   pos (*resol_colisiones)(pos pos_ini, int num_intento))
{
    pos ini, i;
    ini = dispersion(clave, tam);
    i = ini;
    while (diccionario[i].ocupada && strcmp(diccionario[i].clave, clave) != 0)
    {
        (*colisiones)++;
        i = resol_colisiones(ini, *colisiones) % tam;
        if (i == ini)
            return -1;
    }
    return i;
}

int insertar_cerrada(char *clave, char *sinonimos,
                     tabla_cerrada *diccionario, int tam,
                     pos (*dispersion)(char *, int),
                     pos (*resol_colisiones)(pos pos_ini, int num_intento))
{
    pos ini, i;
    int colisiones = 0;
    ini = dispersion(clave, tam);
    for (i = ini; (*diccionario)[i].ocupada && colisiones < tam; i = resol_colisiones(ini, colisiones) % tam)
    {
        colisiones++;
    }
    if ((*diccionario)[i].ocupada == 0)
    {
        strcpy((*diccionario)[i].clave, clave);
        strcpy((*diccionario)[i].sinonimos, sinonimos);
        (*diccionario)[i].ocupada = 1;
    }
    return colisiones;
}

void mostrar_cerrada(tabla_cerrada diccionario, int tam)
{
    pos i;
    printf("{\n");
    for (i = 0; i < tam; i++)
    {
        if (diccionario[i].ocupada)
        {
            printf("%d-(%s)  %s\n", i, diccionario[i].clave, diccionario[i].sinonimos);
        }
        else
        {
            printf("%d-\n", i);
        }
    }
    printf("}\n");
}