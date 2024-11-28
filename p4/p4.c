#include "funciones.h"

int main()
{
    int i;
    inicializar_semilla();
    printf("ORDENACION POR MONTICULOS ASCENDENTE\n");
    for (i = 0; i < 3; i++)
    {
        montAscendente();
    }
    printf("ORDENACION POR MONTICULOS ALEATORIO\n");
    for (i = 0; i < 3; i++)
    {
        montAleatorio();
    }
    printf("ORDENACION POR MONTICULOS DESCENDENTE\n");
    for (i = 0; i < 3; i++)
    {
        montDescendente();
    }

    return 0;
}