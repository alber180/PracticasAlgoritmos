#include "funciones.h"

int main()
{
    int tam = 38197, ins, i, cols = 0;
    tabla_cerrada diccionario;
    inicializar_cerrada(&diccionario, tam);
    ins = leer_sinonimos(diccionario);
    printf("***Insertando %d elementos...", ins);
    for (i = 0; i < tam; i++)
    {
        cols += insertar_cerrada(diccionario[i].clave, diccionario[i].sinonimos, &diccionario, tam, dispersionB, exploracion_lineal);
    }
    printf("Numero total de colisiones: %d\n", cols);
    free(diccionario);
    return 0;
}