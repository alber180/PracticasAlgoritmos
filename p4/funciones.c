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

void mostrarVector(int v[], int n)
{
    int i;
    printf("[%d", v[0]);
    for (i = 1; i < n; i++)
    {
        printf(", %d", v[i]);
    }
    printf("]\n\n");
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

void preguntaOrdenado(bool ord)
{
    if (ord)
        printf("Ordenado\n");
    else
        printf("No ordenado\n");
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

void quitarMenor(pmonticulo m)
{
    if (m->ultimo == -1)
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

void crearMonticulo(int v[], pmonticulo m, int n)
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

void ordenarPorMonticulos(int v[], pmonticulo m, int n)
{
    int i;
    crearMonticulo(v, m, n);
    for (i = 1; i <= n; i++)
    {
        v[i - 1] = consultarMenor(m);
        quitarMenor(m);
    }
}

void imprimirSalida(int n, bool esMenor, double t, double x, double y, double z)
{
    if (esMenor)
        printf("%12d %13.3f*%15.6f%15.6f%15.6f\n", n, t, x, y, z);
    else
        printf("%12d %13.3f %15.6f%15.6f%15.6f\n", n, t, x, y, z);
}

void mostrarCabecera()
{
    printf("\n%12s %13s %15s %14s %14s\n", "n", "t(n)", "t(n)/f(n)",
           "t(n)/g(n)", "t(n)/h(n)");
}

double t_insertarMonticulo(void (*llenar)(int[], int), bool *esMenor,
                           int v[], int n, int k)
{
    int i, j;
    double ta, tb, t1, t2, t;
    pmonticulo m;
    *esMenor = false;
    iniMonticulo(&m);
    llenar(v, n);
    ta = microsegundos();
    for (i = 0; i < n; i++)
    {
        insertarMonticulo(m, v[i]);
    }
    tb = microsegundos();
    m->ultimo = -1;
    t = tb - ta;
    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
            for (j = 0; j < n; j++)
                insertarMonticulo(m, v[j]);
            m->ultimo = -1;
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
            m->ultimo = -1;
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / k;
    }
    free(m);
    return t;
}

double datos(void (*llenar)(int[], int),
             void (*operacionMonticulo)(int[], pmonticulo, int),
             bool *esMenor, int v[], int n, int k)
{
    int i, vector[n];
    double ta, tb, t1, t2, t;
    pmonticulo m;
    *esMenor = false;
    iniMonticulo(&m);
    llenar(vector, n);
    ta = microsegundos();
    operacionMonticulo(vector, m, n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(vector, n);
            operacionMonticulo(vector, m, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(vector, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / k;
    }
    free(m);
    return t;
}

void medirCrearMonticulo()
{
    int n, *valeo, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        valeo = (int *)malloc(n * sizeof(int));
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(aleatorio, crearMonticulo, &esMenor, valeo, n, k);
            x = t / pow(n, 0.8);
            y = t / n;
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}

void medirInsertarMonticulo()
{
    int n, *valeo, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        valeo = (int *)malloc(n * sizeof(int));
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = t_insertarMonticulo(aleatorio, &esMenor, valeo, n, k);
            x = t / pow(n, 0.8);
            y = t / (n * log(n));
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}

void montDescendente()
{
    int n;
    int *vdesc, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();

    for (n = 500; n <= 256000; n *= 2)
    {
        vdesc = (int *)malloc(n * sizeof(int));
        if (vdesc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(descendente, ordenarPorMonticulos, &esMenor, vdesc, n, k);
            x = t / n;
            y = t / (n * log(n));
            z = t / pow(n, 1.2);
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
    for (n = 500; n <= 256000; n *= 2)
    {
        vasc = (int *)malloc(n * sizeof(int));
        if (vasc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(ascendente, ordenarPorMonticulos, &esMenor, vasc, n, k);
            x = t / n;
            y = t / (n * log(n));
            z = t / pow(n, 1.5);
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

    for (n = 500; n <= 256000; n *= 2)
    {
        valeo = (int *)malloc(n * sizeof(int));
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(aleatorio, ordenarPorMonticulos, &esMenor, valeo, n, k);
            x = t / n;
            y = t / (n * log(n));
            z = t / pow(n, 1.5);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}
