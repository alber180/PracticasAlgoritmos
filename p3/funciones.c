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

int ndispersion(char *clave, int tamTabla)
{
    if (strcmp(clave, "ANA") == 0)
        return 7;
    if (strcmp(clave, "JOSE") == 0)
        return 7;
    if (strcmp(clave, "OLGA") == 0)
        return 7;
    return 6;
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

pos exploracion_doble_test(int pos_ini, int num_intento)
{
    int h1 = (5 - (pos_ini) % 5);
    return pos_ini + (num_intento * h1) % 11;
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
    pos i;
    int colisiones = 0;
    i = buscar_cerrada(clave, *diccionario, tam, &colisiones, dispersion,
                       resol_colisiones);
    if (i != -1 && (*diccionario)[i].ocupada == 0)
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