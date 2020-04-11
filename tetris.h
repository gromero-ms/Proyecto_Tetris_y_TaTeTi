#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>


#define COLT 12
#define FILAT 24

typedef struct
{
    int activa;                   /// activa 1 no activa 0 en tablero
    int color;                   /// Comming Soon
    int limite;                 /// Maxima extension de una ficha horizontal y vertical
    char pieza[4][4][4];       /// Matriz 3D ROTACION-FILA-COLUMNA
} Pieza;

///----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///
void cargarPiezasenFichas(int rot,int fil,int col,char ficha[rot][fil][col],char almacen[rot][fil][col]); ///Carga las matrices Almacenes en las struc de las fichas
int rotacionPieza(Pieza piezaN, int rot);                                                                  ///Comando para rotar  una pieza impresa
///void mostrarTablero(char tablero[FILAT][COLT],char tablerobff[FILAT][COLT], char nombre[],int score);      ///nuestra el Tablero
void pasaFichaToTablero (int rotacion,int i,int j, char tablero[FILAT][COLT], Pieza enJuego);               ///Ingresa una ficha al tablero
void limpiaTablero (char tablero[FILAT][COLT]);                                                             ///Limpia el tablero del residuo del movimiento anterior.
Pieza fichaRand (Pieza ficha[7]);                                                                           ///Random para pieza a jugar
void pasaAuxToBuffer (Pieza Auxiliar,int rot,int movAbj,int movLat,char tableroBFF[FILAT][COLT]);           ///Pasa la ficha muerta al tablero back(no tiene mov solo almacena fichas muertas)
void hidecursor();                                                                                          ///Esconde la linea que espera la pulsacion de teclado (ayuda a que la pantalla refresque un poco mas rapido)
int verificFilaCompleta (char tableroBFF [FILAT][COLT],char tablero[FILAT][COLT]);                         ///Busca la fila completa
int verificaLugar (Pieza enJuego,int rot,char tableroBFF[FILAT][COLT],int movAbajo,int movLat);             ///Verifica que debajo de la ficha se encuentra otra
int verificaLateral (Pieza enJuego,int rot, char tableroBFF[FILAT][COLT],int movAbajo,int movLat);          ///Verifica colicion con otras fichas
int verificaTablero (int movLat);                                                                           ///Verifica que no se salga lateral del tablero
int verificaPerdidaTope (char tablero[FILAT][COLT]);
///---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------///
void color(int x);
char getch_noblock(int nivel);
int juegoTetris(char elJugador[],int score);
void mostrarTablero (char tablero[FILAT][COLT],char tablerobff[FILAT][COLT], char nombre[],int score);
