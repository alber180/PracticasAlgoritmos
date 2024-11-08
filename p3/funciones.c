#include "funciones.h"

unsigned int dispersionA(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor += clave[i];
    return valor % tamTabla;
}

unsigned int dispersionB(char *clave, int tamTabla)
{
    int i, n = MIN(8, strlen(clave));
    unsigned int valor = clave[0];
    for (i = 1; i < n; i++)
        valor = (valor << 5) + clave[i]; /* el desplazamiento de 5 bits equivale a */
    return valor % tamTabla;             /* multipicar por 32 */
}

unsigned int ndispersion(char *clave, int tamTabla)
{
    if (strcmp(clave, "ANA") == 0)
        return 7;
    if (strcmp(clave, "JOSE") == 0)
        return 7;
    if (strcmp(clave, "OLGA") == 0)
        return 7;
    return 6;
}

unsigned int exploracion_lineal(pos pos_ini, int incremento)
{
    return pos_ini + incremento;
}

unsigned int exploracion_cuadratica(pos pos_ini, int incremento)
{
    return pos_ini + incremento * incremento;
}

unsigned int exploracion_doble(int pos_ini, int num_intento)
{
    return (pos_ini + (10007 - num_intento) % 10007);
}

unsigned int exploracion_doble_test(int pos_ini, int num_intento)
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
                   int *colisiones, unsigned int (*dispersion)(char *, int),
                   unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
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
                     unsigned int (*dispersion)(char *, int),
                     unsigned int (*resol_colisiones)(pos pos_ini, int num_intento))
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

double microsegundos()
{
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla()
{
    srand(time(NULL));
}
/*
double datos(unsigned int (*dispersion)(char *, int),
             unsigned int (*resol_colisiones)(int pos_ini, int num_intento), bool *esMenor,
             tabla_cerrada diccionario, item data[], int tam, int n, int k)
{
    int col = 0, n_al, i, j;
    double ta, tb, t1, t2, t;
    *esMenor = false;
    ta = microsegundos();
    for (i = 0; i < n; i++)
    {
        n_al = rand() % 19062;
        col = 0;
        buscar_cerrada(data[n_al].clave, diccionario, tam, &col, dispersion, resol_colisiones);
    }
    tb = microsegundos();
    t1 = tb - ta;
    ta = microsegundos();
    for (i = 0; i < n; i++)
    {
        n_al = rand() % 19062;
        col = 0;
    }
    tb = microsegundos();
    t2 = tb - ta;
    t = t1 - t2;

    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            for (j = 0; j < n; j++)
            {
                n_al = rand() % 19062;
                col = 0;
                buscar_cerrada(data[n_al].clave, diccionario, tam, &col, dispersion, resol_colisiones);
            }
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            for (j = 0; j < n; j++)
            {
                n_al = rand() % 19062;
                col = 0;
            }
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / k;
    }38197
    return t;
}
*/

double medirTiempos(unsigned int (*dispersion)(char *, int), int total_palabras, item datos[], tabla_cerrada d_tabla, int n, bool *esMenor, unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
    *esMenor = false;
    double t1 = 0, t2 = 0, t3 = 0, tf = 0, ta = 0, tb = 0, t = 0;
    int col_buscar = 0, x = 0, y = 0, i = 0, k = 10000;
    t1 = microsegundos();
    while (y < n)
    {
        x = rand() % total_palabras;
        col_buscar = 0;
        buscar_cerrada(datos[x].clave, d_tabla, 38197, &col_buscar, dispersion, resol_colisiones);
        y++;
    }
    t2 = microsegundos();
    tf = (t2 - t1);
    y = 0;
    ta = microsegundos();
    for (y = 0; y < n; y++)
    {
        x = rand() % 38197;
        col_buscar = 0;
    }
    tb = microsegundos();
    t3 = (tb - ta);
    t = (tf - t3);
    y = 0;
    if (t < 500)
    {
        *esMenor = true;
        t1 = microsegundos();
        for (i = 0; i < k; i++)
        {
            y = 0;
            while (y < n)
            {
                x = rand() % 38197;
                col_buscar = 0;
                buscar_cerrada(datos[x].clave, d_tabla, 19062, &col_buscar, dispersion, resol_colisiones);
                y++;
            }
        }
        t2 = microsegundos();
        tf = (t2 - t1);
        ta = microsegundos();
        for (i = 0; i < (k * n); i++)
        {
            col_buscar = 0;
            x = rand() % 38197;
        }

        tb = microsegundos();
        t3 = (tb - ta);
        t = (tf - t3) / k;
    }
    y = 0;
    col_buscar = 0;
    return t;
}

void imprimirSalida(int n, bool esMenor, double t, double x, double y, double z)
{
    if (esMenor)
        printf("%12d %15.3f*%15.6f%15.6f%15.6f\n", n, t, x, y, z);
    else
        printf("%12d %15.3f %15.6f%15.6f%15.6f\n", n, t, x, y, z);
}

void mostrarCabecera()
{
    printf("\n%12s %15s %15s %14s %14s\n", "n", "t(n)", "t(n)/f(n)",
           "t(n)/g(n)", "t(n)/h(n)");
}

void dispA_lineal(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionA, exploracion_lineal);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionA, tam, data, diccionario, n, &esMenor, exploracion_lineal);
        // t = datos(dispersionA, exploracion_lineal, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}

void dispA_cuadr(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionA, exploracion_cuadratica);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionA, tam, data, diccionario, n, &esMenor, exploracion_cuadratica);
        // t = datos(dispersionA, exploracion_cuadratica, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}

void dispA_doble(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionA, exploracion_doble);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionA, tam, data, diccionario, n, &esMenor, exploracion_doble);
        // t = datos(dispersionA, exploracion_doble, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}

void dispB_lineal(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionB, exploracion_lineal);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionB, tam, data, diccionario, n, &esMenor, exploracion_lineal);
        // t = datos(dispersionB, exploracion_lineal, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}

void dispB_cuadr(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionB, exploracion_cuadratica);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionB, tam, data, diccionario, n, &esMenor, exploracion_cuadratica);
        // t = datos(dispersionB, exploracion_cuadratica, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}

void dispB_doble(item data[], int ins)
{
    tabla_cerrada diccionario;
    bool esMenor;
    double x, y, z, t;
    int n, i, tam = 38197, k = 10000, cols = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario, tam, dispersionB, exploracion_doble);
    }
    printf("\n***Insertando %d elementos...Numero total de colisiones: %d\n", ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = medirTiempos(dispersionB, tam, data, diccionario, n, &esMenor, exploracion_doble);
        // t = datos(dispersionB, exploracion_doble, &esMenor, diccionario, data, tam, n, k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, esMenor, t, x, y, z);
    }
    free(diccionario);
}