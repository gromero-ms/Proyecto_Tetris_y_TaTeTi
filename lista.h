#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>


typedef struct
{
    int idScore;
    int idUsuario;
    int puntos;
    char fecha[160];
} stScores;

typedef struct
{
    stScores score;
    struct nodoListaScore* sig;
} nodoListaScores;

///--------------------------Funciones--Nodo--Lista--------------------------------------------///
nodoListaScores* inicLista();
nodoListaScores* crearNodo(stScores nodo);
nodoListaScores* agregarPpio(nodoListaScores* lista, nodoListaScores* nuevoNodo);
nodoListaScores* buscarUltimo(nodoListaScores* lista);
nodoListaScores* buscarNodo(nodoListaScores* lista, int idUsuario);
nodoListaScores* agregarFinal(nodoListaScores* lista, nodoListaScores* nuevoNodo);
nodoListaScores* borrarNodoBuscado(nodoListaScores* lista, int idScore);
nodoListaScores* agregarEnOrden(nodoListaScores* lista, nodoListaScores* nuevoNodo);
nodoListaScores* borrarTodaLaLista(nodoListaScores* lista);
nodoListaScores* borrarPrimerNodo(nodoListaScores* lista);
nodoListaScores* borrarUltimoNodo(nodoListaScores* lista);
stScores extraeUltimoNodo(nodoListaScores* lista);
void mostrarUnNodo(nodoListaScores* aux);
void mostrarUnScore(stScores nodo);
void recorrerYmostrar(nodoListaScores* lista);
int cuentaScores(nodoListaScores* lista);


///-------------------------------------------TOP--TEN-----------------------------------------///
int buscarMenor(stScores a[], int validos, int posInicial);
void ordenacionSeleccion(stScores a[], int validos);
void invertirScores(stScores *a, stScores *b);
void invertirArreglo(stScores a[], int validos);

void fGetNow(char date[]);
void cargando();
void limpia ();
#endif // LISTA_H_INCLUDED
