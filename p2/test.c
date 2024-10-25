/*
Luis Alfonso Rodriguez Rodriguez---luis.rodriguezr@udc.es
Alberto Paz Perez---a.pazp@udc.es
Sergio Rego Criado---sergio.rego.criado@udc.es
*/

#include "funciones.h"

/* Funciones para realizar las pruebas con ambos algoritmos */
void preguntaOrdenado(bool ord); /* Imprime por pantalla si esta ordenado */
void ordenarDescendenteTest();   /* Ordena y comprueba vectores descendentes */
void ordenarAleatorioTest();     /* Ordena y comprueba vectores aleatorios */
void ordenarAscendenteTest();    /* Ordena y comprueba vectores ascendentes */

void ordenarDescendenteTest()
{
    int *vdesc, n = 15;

    printf("\nVector descendente por ordenacion rapida:\n");
    vdesc = (int *)malloc(n * sizeof(int));
    descendente(vdesc, n);
    mostrarVector(vdesc, n);
    preguntaOrdenado(ordenado(vdesc, n));
    ord_rap(vdesc, n);
    mostrarVector(vdesc, n);
    preguntaOrdenado(ordenado(vdesc, n));

    printf("\nVector descendente por insercion:\n");
    descendente(vdesc, n);
    mostrarVector(vdesc, n);
    preguntaOrdenado(ordenado(vdesc, n));
    ord_ins(vdesc, n);
    mostrarVector(vdesc, n);
    preguntaOrdenado(ordenado(vdesc, n));

    free(vdesc);
}

void ordenarAleatorioTest()
{
    int *va, n = 15;

    printf("\nVector aleatorio por ordenacion rapida:\n");
    va = (int *)malloc(n * sizeof(int));
    aleatorio(va, n);
    mostrarVector(va, n);
    preguntaOrdenado(ordenado(va, n));
    ord_rap(va, n);
    mostrarVector(va, n);
    preguntaOrdenado(ordenado(va, n));

    printf("\nVector aleatorio por insercion:\n");
    aleatorio(va, n);
    mostrarVector(va, n);
    preguntaOrdenado(ordenado(va, n));
    ord_ins(va, n);
    mostrarVector(va, n);
    preguntaOrdenado(ordenado(va, n));

    free(va);
}

void ordenarAscendenteTest()
{
    int *vasc, n = 15;

    printf("\nVector ascendente por ordenacion rapida:\n");
    vasc = (int *)malloc(n * sizeof(int));
    ascendente(vasc, n);
    mostrarVector(vasc, n);
    preguntaOrdenado(ordenado(vasc, n));
    ord_rap(vasc, n);
    mostrarVector(vasc, n);
    preguntaOrdenado(ordenado(vasc, n));

    printf("\nVector ascendente por insercion:\n");
    ascendente(vasc, n);
    mostrarVector(vasc, n);
    preguntaOrdenado(ordenado(vasc, n));
    ord_rap(vasc, n);
    mostrarVector(vasc, n);
    preguntaOrdenado(ordenado(vasc, n));

    free(vasc);
}

int main()
{
    inicializar_semilla();
    ordenarDescendenteTest();
    ordenarAleatorioTest();
    ordenarAscendenteTest();
    return 0;
}

void preguntaOrdenado(bool ord)
{
    if (ord)
        printf("Ordenado\n");
    else
        printf("No ordenado\n");
}