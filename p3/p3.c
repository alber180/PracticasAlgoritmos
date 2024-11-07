#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
int main()
{
    item data[19062];
    int ins;
    inicializar_semilla();
    ins = leer_sinonimos(data); /*
     printf("DISPERSION A - EXPLORACION LINEAL\n");
     for (int i = 0; i < 5; i++)
     {
         dispA_lineal(data, ins);
     }
      printf("DISPERSION A - EXPLORACION CUADRATICA\n");
      for (int i = 0; i < 5; i++)
      {
          dispA_cuadr(data, ins);
      }
      printf("DISPERSION A - EXPLORACION DOBLE\n");
      for (int i = 0; i < 5; i++)
      {
          dispA_doble(data, ins);
      }
      printf("DISPERSION B - EXPLORACION LINEAL\n");
      for (int i = 0; i < 5; i++)
      {
          dispB_lineal(data, ins);
      }
      printf("DISPERSION B - EXPLORACION CUADRATICA\n");
      for (int i = 0; i < 5; i++)
      {
          dispB_cuadr(data, ins);
      }
    printf("DISPERSION B - EXPLORACION DOBLE\n");
    for (int i = 0; i < 5; i++)
    {
        dispB_doble(data, ins);
    }*/
    return 0;
}