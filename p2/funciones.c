/*
Luis Alfonso Rodriguez Rodriguez---luis.rodriguezr@udc.es
Alberto Paz Perez---a.pazp@udc.es
Sergio Rego Criado---sergio.rego.criado@udc.es
*/

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

void ord_ins(int v[], int n)
{
    int i, x, j;
    for (i = 1; i < n; i++)
    {
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > x)
        {
            v[j + 1] = v[j];
            --j;
        }
        v[j + 1] = x;
    }
}

void intercambiar(int *v, int *u)
{
    int aux;
    aux = *v;
    *v = *u;
    *u = aux;
}

void ord_rap_aux(int v[], int iz, int dr)
{
    int i, j, x, pivote;
    if (iz < dr)
    {
        x = iz + rand() % (dr - iz + 1);
        pivote = v[x];
        intercambiar(&v[iz], &v[x]);
        i = iz + 1;
        j = dr;
        while (i <= j)
        {
            while (i <= dr && v[i] < pivote)
            {
                i++;
            }
            while (v[j] > pivote)
            {
                j--;
            }
            if (i <= j)
            {
                intercambiar(&v[i], &v[j]);
                i++;
                j--;
            }
        }
        intercambiar(&v[iz], &v[j]);
        ord_rap_aux(v, iz, j - 1);
        ord_rap_aux(v, j + 1, dr);
    }
}

void ord_rap(int v[], int n)
{
    ord_rap_aux(v, 0, n - 1);
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
    int i;
    for (i = 1; i < n; i++)
    {
        if (v[i - 1] > v[i])
            return false;
    }
    return true;
}