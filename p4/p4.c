#include "funciones.h"
#define N 10

void ordenarTest(void (*llenar)(int[], int));
void funcionesTest();

int main()
{
    int i;
    inicializar_semilla();
    funcionesTest();

    printf("Vector ascendente:\n");
    ordenarTest(ascendente);
    printf("Vector aleatorio:\n");
    ordenarTest(aleatorio);
    printf("Vector descendente:\n");
    ordenarTest(descendente);
    printf("\nInsertar Monticulo:\n");
    
    for (i = 0; i < 5; i++)
    {
        medirInsertarMonticulo();
    }
    printf("\nCrear Monticulo:\n");
    for (i = 0; i < 5; i++)
    {
        medirCrearMonticulo();
    }
    
    printf("\nORDENACION POR MONTICULOS ASCENDENTE\n");
    for (i = 0; i < 5; i++)
    {
        montAscendente();
    }
    printf("\nORDENACION POR MONTICULOS ALEATORIO\n");
    for (i = 0; i < 5; i++)
    {
        montAleatorio();
    }
    printf("\nORDENACION POR MONTICULOS DESCENDENTE\n");
    for (i = 0; i < 5; i++)
    {
        montDescendente();
    }

    return 0;
}

void ordenarTest(void (*llenar)(int[], int))
{
    int *v;
    pmonticulo m;
    iniMonticulo(&m);
    v = (int *)malloc(N * sizeof(int));
    llenar(v, N);
    mostrarVector(v, N);
    preguntaOrdenado(ordenado(v, N));
    ordenarPorMonticulos(v, m, N);
    mostrarVector(v, N);
    preguntaOrdenado(ordenado(v, N));
    free(m);
    free(v);
}

void funcionesTest()
{
    int *v;
    pmonticulo m;
    iniMonticulo(&m);
    v = (int *)malloc(N * sizeof(int));
    aleatorio(v, N - 1);
    printf("Vector inicial:\n");
    mostrarVector(v, N - 1);
    crearMonticulo(v, m, N - 1);
    printf("Vector insertado en el monticulo:\n");
    mostrarVector(m->vector, N - 1);
    insertarMonticulo(m, 5);
    printf("Insertamos el numero 5, por ejemplo:\n");
    mostrarVector(m->vector, N);
    printf("Consultamos el menor: %d\n", consultarMenor(m));
    quitarMenor(m);
    printf("Ahora quitamos el menor:\n");
    mostrarVector(m->vector, N - 1);
    free(m);
    free(v);
}