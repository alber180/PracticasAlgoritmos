/*
Luis Alfonso Rodriguez Rodriguez---luis.rodriguezr@udc.es
Alberto Paz Perez---a.pazp@udc.es
Sergio Rego Criado---sergio.rego.criado@udc.es
*/

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

void insAscendente();   /* Insercion ascendente */
void insDescendente();  /* Insercion descendente */
void insAleatorio();    /* Insercion aleatoria */
void rapAscendente();   /* Rapida ascendente */
void rapDescendente();  /* Rapida descendente */
void rapAleatorio();    /* Rapida aleatoria */
void mostrarCabecera(); /*Funcion para mostrar la cabecera de la tabla*/

/* Funcion para imprimir los resultados */
void imprimirSalida(int n, bool esMenor, double t, double x, double y,
                    double z);

/* Funcion para medir los tiempos */
double datos(void (*llenar)(int v[], int), void (*ord)(int[], int),
             bool *esMenor, int v[], int n, int k);

int main()
{
    int i;
    /* Ejecutamos las diferentes pruebas */
    printf("\nDESCENDENTE POR INSERCION\n");
    for (i = 0; i < 5; i++)
    {
        insDescendente();
    }
    printf("\nASCENDENTE POR INSERCION\n");
    for (i = 0; i < 5; i++)
    {
        insAscendente();
    }
    printf("\nALEATORIO POR INSERCION\n");
    for (i = 0; i < 5; i++)
    {
        insAleatorio();
    }
    printf("\nDESCENDENTE POR ORDENACION RAPIDA\n");
    for (i = 0; i < 5; i++)
    {
        rapDescendente();
    }
    printf("\nASCENDENTE POR ORDENACION RAPIDA\n");
    for (i = 0; i < 5; i++)
    {
        rapAscendente();
    }
    printf("\nALEATORIO POR ORDENACION RAPIDA\n");
    for (i = 0; i < 5; i++)
    {
        rapAleatorio();
    }
    return 0;
}

void insDescendente()
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
            t = datos(descendente, ord_ins, &esMenor, vdesc, n, k);
            x = t / pow(n, 1.8);
            y = t / pow(n, 2.0);
            z = t / pow(n, 2.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vdesc);
        }
    }
}

void insAscendente()
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
            t = datos(ascendente, ord_ins, &esMenor, vasc, n, k);
            x = t / pow(n, 0.8);
            y = t / n;
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vasc);
        }
    }
}

void insAleatorio()
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
            t = datos(aleatorio, ord_ins, &esMenor, valeo, n, k);
            x = t / pow(n, 1.9);
            y = t / pow(n, 2);
            z = t / pow(n, 2.1);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}

void rapDescendente()
{
    int n, *vdesc, k;
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
            t = datos(descendente, ord_rap, &esMenor, vdesc, n, k);
            x = t / pow(n, 1.04);
            y = t / pow(n, 1.08);
            z = t / pow(n, 1.12);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vdesc);
        }
    }
}

void rapAscendente()
{
    int n, *vasce, k;
    bool esMenor = false;
    double x, y, z, t;
    k = 10000;
    mostrarCabecera();
    for (n = 500; n <= 32000; n *= 2)
    {
        vasce = (int *)malloc(n * sizeof(int));
        if (vasce == NULL)
            printf("Error: no se pudo asignar memoria\n");
        else
        {
            t = datos(ascendente, ord_rap, &esMenor, vasce, n, k);
            x = t / pow(n, 1.05);
            y = t / pow(n, 1.09);
            z = t / pow(n, 1.13);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(vasce);
        }
    }
}

void rapAleatorio()
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
            t = datos(aleatorio, ord_rap, &esMenor, valeo, n, k);
            x = t / n;
            y = t / pow(n, 1.117);
            z = t / pow(n, 1.2);
            imprimirSalida(n, esMenor, t, x, y, z);
            free(valeo);
        }
    }
}

double datos(void (*llenar)(int[], int), void (*ord)(int[], int), bool *esMenor,
             int v[], int n, int k)
{
    int i;
    double ta, tb, t1, t2, t;
    *esMenor = false;
    llenar(v, n);
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