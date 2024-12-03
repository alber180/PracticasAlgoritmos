#include "funciones.h"
#define N 10
#define M 5

void ordenarTest(void (*llenar)(int[], int));
void funcionesTest();
int main()
{
    int i;
    inicializar_semilla();
    funcionesTest();
    printf("\nTest de ordenacion por monticulos:\nVector ascendente:\n");
    ordenarTest(ascendente);
    printf("\nVector aleatorio:\n");
    ordenarTest(aleatorio);
    printf("\nVector descendente:\n");
    ordenarTest(descendente);
    printf("\ninsertarMonticulo:\n");
    medirInsertarMonticulo();
    printf("\ncrearMonticulo:\n");
    medirCrearMonticulo();
    printf("\nOrdenacion por monticulos de vector ascendente\n");
    montAscendente();
    printf("\nOrdenacion por monticulos de vector aleatorio\n");
    montAleatorio();
    printf("\nOrdenacion por monticulos de vector descendente\n");
    montDescendente();
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
    /* Llenamos un vector con N-1 elementos aleatorios porque mas adelante
    probaremos insertar un nuevo elemento */
    printf("\nTest de funciones de monticulo:\nVector inicial:\n");
    mostrarVector(v, N - 1);
    crearMonticulo(v, m, N - 1);
    printf("\nVector insertado en el monticulo:\n");
    mostrarVector(m->vector, N - 1);
    insertarMonticulo(m, M);
    printf("\nInsertamos el numero %d:\n", M);
    mostrarVector(m->vector, N);
    printf("\nConsultamos el menor: %d\n", consultarMenor(m));
    quitarMenor(m);
    printf("\nAhora quitamos el menor:\n");
    mostrarVector(m->vector, N - 1);
    free(m);
    free(v);
}