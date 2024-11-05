#include "funciones.h"
#include "funciones.c"
int main()
{
    item data[19062];
    int ins;
    inicializar_semilla();
    ins = leer_sinonimos(data);
    for (int i = 0; i < 5; i++)
    {
        dispB_cuadr(data, ins);
    }
    return 0;
}
