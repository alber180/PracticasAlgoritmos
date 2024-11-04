#include "funciones.h"

int main()
{
    int tam = 11;
    tabla_cerrada diccionario;
    inicializar_cerrada(&diccionario, tam);
    printf("%d", leer_sinonimos(diccionario));
    free(diccionario);
    return 0;
}