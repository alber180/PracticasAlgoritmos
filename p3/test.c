#include "funciones.c"
#include "funciones.h"

int main()
{
    int tam = 100;
    int colisiones;
    tabla_cerrada diccionario;

    inicializar_cerrada(&diccionario, tam);
    mostrar_cerrada(diccionario, tam);
    colisiones = insertar_cerrada("AB", "Rodriguez, Rodriguez", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Auis' : %d\n", colisiones);
    mostrar_cerrada(diccionario, tam);
    colisiones = insertar_cerrada("AB", "Paz, Perez", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Alberto' : %d\n", colisiones);
    mostrar_cerrada(diccionario, tam);
    colisiones = insertar_cerrada("AB", "Rego, Criado", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    colisiones = insertar_cerrada("AB", "Rego, mateo", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    colisiones = insertar_cerrada("AB", "Rego, mateo1", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    colisiones = insertar_cerrada("AB", "Rego, mateo2", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    colisiones = insertar_cerrada("AB", "Rego, mateo3", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    colisiones = insertar_cerrada("AB", "Rego, mateo4", &diccionario, tam, dispersionB, exploracion_doble);
    printf("Colisiones 'Sergio' : %d\n", colisiones);
    mostrar_cerrada(diccionario, tam);

    free(diccionario);
}