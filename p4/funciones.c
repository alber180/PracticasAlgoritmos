#include "funciones.h"

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

void imprimirSalida(int n, int k, double t, double x, double y,
                    double z)
{
    printf("%12d %7d %13.3f %15.6f%15.6f%15.6f\n", n, k, t, x, y, z);
}

void mostrarCabecera()
{
    printf("\n%12s %7s %13s %15s %14s %14s\n", "n", "k", "t(n)", "t(n)/f(n)",
           "t(n)/g(n)", "t(n)/h(n)");
}

bool isEmptyHeap(const pmonticulo m)
{
    return m->ultimo = -1;
}

void iniMonticulo(pmonticulo m)
{
    m = malloc(sizeof(struct monticulo));
    if (m == NULL)
    {
        perror("No hay espacio suficiente\n");
    }
    m->ultimo = -1;
}

void insertarMonticulo(pmonticulo m, int x)
{
    m->ultimo++;
}

void intercambiar(int *v, int *u)
{
    int aux;
    aux = *v;
    *v = *u;
    *u = aux;
}

void hundir(pmonticulo m, int i)
{
    int j, hijoIzq, hijoDer;
    for (j = 0; j < i; j++)
    {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        j = i;
        if (hijoDer <= TAM && m->vector[hijoDer] > m->vector[i])
        {
            i = hijoDer;
        }
        if (hijoIzq <= TAM && m->vector[hijoIzq] > m->vector[i])
        {
            i = hijoIzq;
        }
        intercambiar(m->vector[i], m->vector[j]);
    }
}

void quitarMenor(pmonticulo m)
{
    if (!isEmptyHeap(m))
    {
    }
}

int consultarMenor(const pmonticulo m)
{
    if (!isEmptyHeap(m))
    {
        return m->vector[0];
    }
}
void crearMonticulo(pmonticulo m, int v[], int n)
{
}

/*
// Segun el tiempo, ejecutamos las mediciones 'k' veces para mayor precision
int obtener_K(int t)
{
    int k = 0;

    if (t < 500)
    {
        k = 10000;
    }
    else if (t < 4000)
    {
        k = 1000;
    }
    else if (t < 12000)
    {
        k = 100;
    }
    else if (t < 120000)
    {
        k = 10;
    }
    else
    {
        k = 1;
    }
    return k;
}

// Medimos los tiempos "k" veces
double tiempos_K_veces(unsigned int (*dispersion)(char *, int),
                       unsigned int (*resol_colisiones)(int pos_ini,
                                                        int num_intento),
                       tabla_cerrada diccionario, item data[],
                       int tam, int n, int k)
{
    int col = 0, n_al, i, j;
    double ta, tb, t1, t2, t;
    ta = microsegundos();

    for (i = 0; i < k; i++)
    {
        for (j = 0; j < n; j++)
        {
            n_al = rand() % 19062;
            col = 0;
            buscar_cerrada(data[n_al].clave, diccionario, tam, &col, dispersion,
                           resol_colisiones);
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
    return t;
}

// Medicion de tiempos
double tiempos(unsigned int (*dispersion)(char *, int),
               unsigned int (*resol_colisiones)(int pos_ini, int num_intento),
               tabla_cerrada diccionario, item data[], int tam,
               int n, int *k)
{
    int col = 0, n_al, i;
    double ta, tb, t1, t2, t;
    ta = microsegundos();
    for (i = 0; i < n; i++)
    {
        n_al = rand() % 19062;
        col = 0;
        buscar_cerrada(data[n_al].clave, diccionario, tam, &col, dispersion,
                       resol_colisiones);
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
    *k = obtener_K(t);

    if (*k > 1)
    {
        t = tiempos_K_veces(dispersion, resol_colisiones,
                            diccionario, data, tam, n, *k);
    }
    return t;
}

void datos(item data[], int ins, unsigned int (*dispersion)(char *, int),
           unsigned int (*resol_colisiones)(int pos_ini, int num_intento))
{
    tabla_cerrada diccionario;
    double x, y, z, t;
    int n, i, tam = 38197, cols = 0, k = 0;
    inicializar_cerrada(&diccionario, tam);
    for (i = 0; i < ins; i++)
    {
        cols += insertar_cerrada(data[i].clave, data[i].sinonimos, &diccionario,
                                 tam, dispersion, resol_colisiones);
    }
    printf("\nInsertando %d elementos... Numero total de colisiones: %d\n"
           "Buscando n elementos...\n",
           ins, cols);
    mostrarCabecera();
    for (n = 125; n <= 16000; n *= 2)
    {
        t = tiempos(dispersion, resol_colisiones, diccionario,
                    data, tam, n, &k);
        x = t / pow(n, 0.8);
        y = t / n;
        z = t / (n * log(n));
        imprimirSalida(n, k, t, x, y, z);
    }
    free(diccionario);
}*/