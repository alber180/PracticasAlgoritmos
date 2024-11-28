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
    return (m->ultimo == -1);
}

void iniMonticulo(pmonticulo *m)
{
    *m = malloc(sizeof(struct monticulo));
    if (*m == NULL)
    {
        perror("No hay espacio suficiente\n");
        return;
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
    while (h > 0 && m->vector[p] > m->vector[h])
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
        fprintf(stderr, "Monticulo vacio\n");
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
    if (n > TAM)
    {
        perror("El array es demasiado grande para el montículo");
        return;
    }
    for (i = 0; i < n; i++)
    {
        m->vector[i] = v[i];
    }
    m->ultimo = n - 1;
    for (j = (m->ultimo / 2); j >= 0; j--)
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

bool ordenado(int v[], int n)
{
    int i;
    for (i = 1; i < n; i++)
    {
        if (v[i - 1] > v[i])
            return false;
    }
    return true;
}

void OrdenarPorMonticulos(int *v[], int n)
{
    int i;
    pmonticulo m;
    iniMonticulo(&m);
    crearMonticulo(m, *v, n);
    for (i = 1; i <= n; i++)
    {
        (*v)[i - 1] = consultarMenor(m);
        quitarMenor(m);
    }
}

void aleatorio(int v[], int n)
{ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = n - 1 - i;
}

double datos(void (*llenar)(int[], int), bool *esMenor,
             int v[], int n, int k)
{
    int i;
    double ta, tb, t1, t2, t;
    *esMenor = false;
    llenar(v, n);
    ta = microsegundos();
    OrdenarPorMonticulos(&v, n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
            // Igual hay que restar el crear monticulo en el for de abajo junto con llenar
            OrdenarPorMonticulos(&v, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; i++)
            llenar(v, n);
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / k;
    }
    return t;
}

void montDescendente()
{
    int n;
    int *vdesc, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();

    for (n = 500; n <= 32000; n *= 2)
    {
        vdesc = (int *)malloc(n * sizeof(int));
        if (vdesc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(descendente, &esMenor, vdesc, n, k);
            x = t / pow(n, 1.8);
            y = t / pow(n, 2.0);
            z = t / pow(n, 2.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vdesc);
        }
    }
}

void montAscendente()
{
    int n;
    int *vasc, k;
    bool esMenor;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();

    for (n = 500; n <= 32000; n *= 2)
    {
        vasc = (int *)malloc(n * sizeof(int));
        if (vasc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(ascendente, &esMenor, vasc, n, k);
            x = t / pow(n, 0.8);
            y = t / n;
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vasc);
        }
    }
}

void montAleatorio()
{
    int n, *valeo, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();

    for (n = 500; n <= 32000; n *= 2)
    {
        valeo = (int *)malloc(n * sizeof(int));
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(aleatorio, &esMenor, valeo, n, k);
            x = t / pow(n, 1.9);
            y = t / pow(n, 2);
            z = t / pow(n, 2.1);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}
