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
    return (m->ultimo = -1);
}

void iniMonticulo(pmonticulo *m)
{
    *m = malloc(sizeof(struct monticulo));
    if (*m == NULL)
    {
        perror("No hay espacio suficiente\n");
    }
    (*m)->ultimo = -1;
}

void insertarMonticulo(pmonticulo m, int x)
{
    if (m->ultimo == TAM)
    {
        perror("Monticulo lleno");
    }
    else
    {
        m->ultimo = m->ultimo + 1;
        m->vector[m->ultimo] = x;
        flotar(m, m->ultimo);
    }
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

    do
    {
        hijoIzq = 2 * i + 1;
        hijoDer = 2 * i + 2;
        j = i;
        if (hijoDer <= m->ultimo && m->vector[hijoDer] < m->vector[i])
        {
            i = hijoDer;
        }
        if (hijoIzq <= m->ultimo && m->vector[hijoIzq] < m->vector[i])
        {
            i = hijoIzq;
        }
        intercambiar(&(m->vector[i]), &(m->vector[j]));
    } while (j != i);
}

void flotar(pmonticulo m, int i)
{
    int p, h;
    h = i;
    p = (h - 1) / 2;
    while (i > 1 && m->vector[p] < m->vector[h])
    {
        intercambiar(&(m->vector[p]), &(m->vector[h]));
        h = p;
        p /= 2;
    }
}

void quitarMenor(pmonticulo m)
{
    if (isEmptyHeap(m))
    {
        perror("Monticulo vacio");
    }
    else
    {
        m->vector[0] = m->vector[m->ultimo];
        m->ultimo = m->ultimo - 1;
        if (m->ultimo >= 0)
        {
            hundir(m, 0);
        }
    }
}

int consultarMenor(const pmonticulo m)
{
    return m->vector[0];
}

void crearMonticulo(pmonticulo m, int v[], int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        m->vector[i] = v[i];
    }
    m->ultimo = n;
    for (j = (m->ultimo / 2); j > 0; j--)
    {
        hundir(m, j);
    }
}

void mostrar(pmonticulo m)
{
    int i;
    printf("[");
    for (i = 0; i < m->ultimo; i++)
    {
        printf("%d, ", m->vector[i]);
    }
    printf("]\n");
}

void mostrarmont(pmonticulo m)
{
    int nivel = 0;                           // Nivel actual
    int elementos = 1;                       // Número de elementos en el nivel actual
    int i = 0;                               // Índice del vector del montículo
    int maxNivel = (int)log2(m->ultimo) + 1; // Total de niveles en el montículo

    while (i < m->ultimo) // Cambiado de 'i <= m->ultimo' a 'i < m->ultimo'
    {
        // Calcular espacios iniciales para centrar los elementos del nivel actual
        int totalEspacios = (1 << (maxNivel - nivel)) - 1;

        // Espaciado inicial antes de imprimir los elementos del nivel actual
        for (int espacio = 0; espacio < totalEspacios; espacio++)
        {
            printf("   ");
        }

        // Imprimir los elementos del nivel actual
        for (int j = 0; j < elementos && i < m->ultimo; j++, i++) // Cambiado 'i <= m->ultimo' a 'i < m->ultimo'
        {
            printf("%3d", m->vector[i]);

            // Espaciado entre elementos en el mismo nivel
            if (j < elementos - 1 && i < m->ultimo)
            {
                for (int espacio = 0; espacio < (1 << (maxNivel - nivel + 1)) - 1; espacio++)
                {
                    printf("   ");
                }
            }
        }

        // Salto de línea después de imprimir todos los elementos del nivel actual
        printf("\n\n");

        // Pasar al siguiente nivel
        nivel++;
        elementos *= 2; // Cada nivel tiene el doble de elementos que el anterior

        // La condición 'if (i > m->ultimo)' ya no es necesaria debido a la condición del bucle 'while'
    }
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