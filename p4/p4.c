#include "funciones.h"
#define N 10

void ordenarTest(void (*llenar)(int[], int));

int main()
{
    int i;
    inicializar_semilla();
    printf("Vector ascendente:\n");
    ordenarTest(ascendente);
    printf("Vector aleatorio:\n");
    ordenarTest(aleatorio);
    printf("Vector descendente:\n");
    ordenarTest(descendente);

    printf("\nORDENACION POR MONTICULOS ASCENDENTE\n");
    for (i = 0; i < 3; i++)
    {
        montAscendente();
    }
    printf("\nORDENACION POR MONTICULOS ALEATORIO\n");
    for (i = 0; i < 3; i++)
    {
        montAleatorio();
    }
    printf("\nORDENACION POR MONTICULOS DESCENDENTE\n");
    for (i = 0; i < 3; i++)
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
