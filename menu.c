#include "menu.h"

void imprimirCabecera(char cabecera[])
{
    int i;
    printf("%c", 201);
    for(i=0; i<37; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    printf("%c%20s%18c\n", 186,cabecera,186);
    printf("%c", 200);
    for(i=0; i<37; i++)
    {
        printf("%c",205);
    }
    printf("%c", 188);
}

void imprimirOpcionesSubMenuAdm()
{
    imprimirCabecera("MENU ADMINISTRADOR");
    printf("\n1. Eliminar Jugador\n");
    printf("2. Modificar Jugador\n");
    printf("3. Mas\n");
    printf("0. Salir \n");
}

void imprimirOpcionesMenu1()
{
    printf("1. Login\n\n");
    printf("2. Registrarse\n\n");
    printf("0. Salir\n");
}

void imprimirOpcionesSubMenuUser()
{
    imprimirCabecera("BIENVENIDO !");
    printf("\n1. Elegir Juego\n");
    printf("2. Ver Mis Scores\n");
    printf("3. Top 10 Scores\n");
    printf("4. Modificar Datos\n");
    printf("0. Cerrar Sesion\n");
}

void imprimirOpcionesSubMenuJuegos()
{
    imprimirCabecera("JUEGOS!");
    printf("\n1. Tetris\n");
    printf("2. TA TE TI\n");
    printf("0. Salir\n");
}

int ingresarOpcion()
{
    int opcion;
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%i", &opcion);
    return opcion;
}

void iniciarMenu()
{

    system("cls");
    imprimirCabecera("TP FINAL ERROR 404");
    printf("\n\n");
    imprimirOpcionesMenu1();
}
