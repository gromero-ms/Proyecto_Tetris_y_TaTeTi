#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include <math.h>

#define COLR 5
#define FILR 5



typedef struct
{
    char layout[FILR][COLR];
    int id;
    int nivel;
    int siguientes[9];
} table;

typedef struct
{
    int player;
    int i;
    int j;
    int valor;
} jugada;

typedef struct
{
    table dato;
    struct nodoArbol* arbol_1;
    struct nodoArbol* arbol_2;
    struct nodoArbol* arbol_3;
    struct nodoArbol* arbol_4;
    struct nodoArbol* arbol_5;
    struct nodoArbol* arbol_6;
    struct nodoArbol* arbol_7;
    struct nodoArbol* arbol_8;
    struct nodoArbol* arbol_9;

} nodoArbol;

typedef struct
{
    int opcion;
    char identificador[10];
    nodoArbol* arbol;
} celda;


///--------------------------3--En--Raya--------------------------------------------------------------///

void muestraTablero(table unTablero,int puntos);   ///Muestra el tablero con su NIVEL y CODIGO
int nivelTablero(table unTablero);      ///Evalua el nivel del tablero (cantidad de jugadas hechas)
int codigoTablero(table unTablero);     ///Calcula el codigo de el tablero en cuestion
int potencia(int num, int pot);         ///Funcion de potencia
table siguientesJugadas(table unTablero); ///Funcion que llena el array de siguientes

jugada traducirJugada(int numero);      ///recibe un int del 1 al 9 para traducir en una coord para jugar

int evaluaVictoria(table unTablero);    ///evalua cantidad de victorias en base a las jugadas hechas

int retornaMIN(table unTablero);        ///Retorna el MIN de victorias posibles (min es el max del opuesto)
int retornaMAX(table unTablero);        ///Retorna el MAX de victorias posibles

void pasaLaytoTable(char lay[COLR][FILR],char unTable[COLR][FILR]); ///Pasa el tablero preseteado al de juego

int buscaMenorJugada(jugada arreglo[8],int validos);  ///Busca la jugada con menor chance de victoria enemiga
int buscaMayorJugada(jugada arreglo[8],int validos);  ///Busca la jugada con mayor chance de victoria propia

jugada mejorMove(table unTablero);      ///Busca la mejor jugada posible para IA
jugada peorMove(table unTablero);       ///Busca la mejor jugada posible para el oponente en base a la mejor anterior
jugada laJugada(table unTablero);       ///Utiliza las Funciones anteriores para calcular y devolver la mejor jugada para IA
jugada la2Jugada(table unTablero);      ///Hace lo mismo para la segunda IA

int skinetWins();

///----------------------------Arbol----------------------------------------------------------------------///

nodoArbol* plantarArbol();
nodoArbol* crearNodoArbol(table dato);
nodoArbol* buscarArbol(nodoArbol* arbol, table dato);
nodoArbol* insertarArbol(nodoArbol* arbol, table dato);

void muestraArbol(nodoArbol* arbol);

int contarNodosArbol(nodoArbol* arbol);
int contarNodosHoja(nodoArbol* arbol);

///-------------------------Arr-De--Arbol--------------------------------------------------///

void inicArrDeArb(celda arrDeArb[]);
void agregarAArbol(celda arrDeArbol[],int posicion, table nuevoTable);
int juegoTaTeTi(char elJugador[]);

