#include "funciones.h"

/* Funcion para realizar las pruebas, llamada con ndispersion y los 3 metodos
   de resolucion de colisiones */
void mostrarTest(int tam, tabla_cerrada diccionario,
                 unsigned int (*dispersion)(char *, int),
                 unsigned int (*resol_colisiones)(int pos_ini, int num_intento),
                 char *nombres[])
{
    int i, colisiones = 0;
    pos p;

    for (i = 0; i < 6; i++)
    {
        colisiones += insertar_cerrada(nombres[i], "", &diccionario,
                                       tam, dispersion, resol_colisiones);
    }
    mostrar_cerrada(diccionario, tam);
    printf("Numero total de colisiones al insertar los elementos: %d\n",
           colisiones);

    for (i = 0; i < 7; i++)
    {
        colisiones = 0;
        p = buscar_cerrada(nombres[i], diccionario, tam, &colisiones,
                           dispersion, resol_colisiones);
        if (p != -1 && diccionario[p].ocupada != 0)
        {
            printf("Al buscar: %s, encuentro: %s, colisiones: %d\n", nombres[i],
                   diccionario[p].clave, colisiones);
        }
        else
        {
            printf("No encuentro: %s, colisiones: %d\n",
                   nombres[i], colisiones);
        }
    }
}

int main()
{
    int tam = 11;
    tabla_cerrada diccionario;
    char *nombres[7] = {"ANA", "LUIS", "JOSE", "OLGA", "ROSA", "IVAN",
                        "CARLOS"};

    printf("\n*****TABLA CERRADA LINEAL*****\n");
    inicializar_cerrada(&diccionario, tam);
    mostrarTest(tam, diccionario, ndispersion, exploracion_lineal, nombres);
    free(diccionario);

    printf("\n*****TABLA CERRADA CUADRATICA*****\n");
    inicializar_cerrada(&diccionario, tam);
    mostrarTest(tam, diccionario, ndispersion, exploracion_cuadratica, nombres);
    free(diccionario);

    printf("\n*****TABLA CERRADA DOBLE*****\n");
    inicializar_cerrada(&diccionario, tam);
    mostrarTest(tam, diccionario, ndispersion, exploracion_doble_test, nombres);
    free(diccionario);
    return 0;
}