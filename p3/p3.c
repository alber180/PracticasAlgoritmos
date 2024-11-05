#include "funciones.h"

int main()
{
    int ins, i;
    inicializar_cerrada(&diccionario, tam);
    ins = leer_sinonimos(diccionario);
    printf("***Insertando %d elementos...", ins);
    for (i = 0; i < 2 * ins; i++)
    {
        cols += insertar_cerrada(diccionario[i].clave, diccionario[i].sinonimos, &diccionario, tam, dispersionB, exploracion_cuadratica);
    }
    printf("Numero total de colisiones: %d\n", cols);
    free(diccionario);
    return 0;
}

void dispA_lineal()
{
    int n, tam = 38197, k = 10000, cols = 0;
    tabla_cerrada diccionario;
    bool esMenor = false;
    double x, y, z, t;
    mostrarCabecera();
    for (n = 125; n <= 20000; n *= 2)
    {
        inicializar_cerrada(&diccionario, tam);
        t = datos(dispersionA, exploracion_lineal, &esMenor, diccionario, n, k);
        x = t / pow(n, 1.8);
        y = t / pow(n, 2.0);
        z = t / pow(n, 2.2);
        imprimirSalida(n, esMenor, t, x, y, z);
        free(diccionario);
    }
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

void aleatorio(int v[], int n)
{ /* se generan números pseudoaleatorio entre -n y +n */
    int i, m = 2 * n + 1;
    for (i = 0; i < n; i++)
        v[i] = (rand() % m) - n;
}

double datos(pos (*dispersion)(char *, int),
             pos (*resol_colisiones)(pos pos_ini, int num_intento), bool *esMenor,
             tabla_cerrada *diccionario, int tam, int k)
{
    int i, ins;
    double ta, tb, t1, t2, t;
    *esMenor = false;

    ins = leer_sinonimos(diccionario);
    ta = microsegundos();
    ord(v, n);
    tb = microsegundos();
    t = tb - ta;
    if (t < 500)
    {
        *esMenor = true;
        ta = microsegundos();
        for (i = 0; i < k; i++)
        {
            llenar(v, n);
            ord(v, n);
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
