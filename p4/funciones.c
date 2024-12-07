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
{ // Generamos un vector de números pseudoaleatorio entre -n y +n
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

void ascendente(int v[], int n)
{
    // Generamos un vector de números de 0 a n-1
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    // Generamos un vector de números de n-1 a 0
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
    printf("]\n");
}

bool ordenado(int v[], int n)
{
    // Funcion para comprobar si un vector esta ordenado
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
    // Funcion que muestra por pantalla si el vector esta ordenado
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
    // Funcion para asignar espacio de memoria al monticulo
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
        printf("Monticulo lleno\n");
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
        printf("Monticulo vacio\n");
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
        printf("El array es demasiado grande para el montículo\n");
    }
    else
    {
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
}

void ordenarPorMonticulos(int v[], pmonticulo m, int n)
{
    int i;
    crearMonticulo(v, m, n);
    for (i = 0; i < n; i++)
    {
        v[i] = consultarMenor(m);
        quitarMenor(m);
    }
}

void imprimirSalida(int n, bool esMenor, double t, double x, double y, double z)
{
    // Funcion para mostrar cada fila de la tabla
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
                           int v[], int n, int k, pmonticulo m)
{
    int i, j;
    double ta, tb, t1, t2, t;
    *esMenor = false;
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
    return t;
}

double datos(void (*llenar)(int[], int),
             void (*operacionMonticulo)(int[], pmonticulo, int),
             bool *esMenor, int v[], int n, int k, pmonticulo m)
{
    int i;
    double ta, tb, t1, t2, t;
    *esMenor = false;
    llenar(v, n);
    ta = microsegundos();
    operacionMonticulo(v, m, n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
            operacionMonticulo(v, m, n);
        }
        tb = microsegundos();
        t1 = tb - ta;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
        }
        tb = microsegundos();
        t2 = tb - ta;
        t = (t1 - t2) / k;
    }
    return t;
}

void medirCrearMonticulo()
{
    int n, *valeo, k;
    pmonticulo m;
    bool esMenor = false;
    double x, y, z, t;
    iniMonticulo(&m);
    k = 10000;
    valeo = (int *)malloc(TAM * sizeof(int));
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(aleatorio, crearMonticulo, &esMenor, valeo, n, k, m);
            x = t / pow(n, 0.9);
            y = t / n;
            z = t / pow(n, 1.1);
            imprimirSalida(n, esMenor, t, x, y, z);
        }
    }
    free(valeo);
    free(m);
}

void medirInsertarMonticulo()
{
    int n, *vdesc, k;
    pmonticulo m;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    iniMonticulo(&m);
    vdesc = (int *)malloc(TAM * sizeof(int));
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        if (vdesc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = t_insertarMonticulo(descendente, &esMenor, vdesc, n, k, m);
            x = t / pow(n, 0.9);
            y = t / (n * log(n));
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
        }
    }
    free(vdesc);
    free(m);
}

void montDescendente()
{
    int n;
    int *vdesc, k;
    pmonticulo m;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    iniMonticulo(&m);
    vdesc = (int *)malloc(TAM * sizeof(int));
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        if (vdesc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(descendente, ordenarPorMonticulos,
                      &esMenor, vdesc, n, k, m);
            x = t / n;
            y = t / (pow(n, 0.98) * log(n));
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
        }
    }
    free(vdesc);
    free(m);
}

void montAscendente()
{
    int n;
    int *vasc, k;
    pmonticulo m;
    bool esMenor;
    double x, y, z, t;
    k = 10000;
    iniMonticulo(&m);
    vasc = (int *)malloc(TAM * sizeof(int));
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        if (vasc == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(ascendente, ordenarPorMonticulos,
                      &esMenor, vasc, n, k, m);
            x = t / n;
            y = t / (pow(n, 0.99) * log(n));
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
        }
    }
    free(vasc);
    free(m);
}

void montAleatorio()
{
    int n, *valeo, k;
    bool esMenor = false;
    pmonticulo m;
    double x, y, z, t;
    k = 10000;
    iniMonticulo(&m);
    valeo = (int *)malloc(TAM * sizeof(int));
    mostrarCabecera();
    for (n = 500; n <= 256000; n *= 2)
    {
        if (valeo == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(aleatorio, ordenarPorMonticulos,
                      &esMenor, valeo, n, k, m);
            x = t / n;
            y = t / (n * log(n));
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
        }
    }
    free(valeo);
    free(m);
}
