#include "funciones.h"

int main()
{
    int i;
    inicializar_semilla();
    for (i = 0; i < 3; i++)
    {
        montAscendente();
    }
    for (i = 0; i < 3; i++)
    {
        montAleatorio();
    }
    for (i = 0; i < 3; i++)
    {
        montDescendente();
    }

    return 0;
}