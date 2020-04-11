#include "lista.h"

nodoListaScores* inicLista()
{
    return NULL;
}

nodoListaScores* crearNodo(stScores nodo)
{
    nodoListaScores* aux = (nodoListaScores*)malloc(sizeof(nodoListaScores));
    aux->score= nodo;
    aux->sig = NULL;
    return aux;
}

nodoListaScores* agregarPpio(nodoListaScores* lista, nodoListaScores* nuevoNodo)
{
    nuevoNodo->sig = lista;
    lista = nuevoNodo;

    return lista;
}

nodoListaScores* buscarUltimo(nodoListaScores* lista)
{
    nodoListaScores* seg = lista;
    if(seg != NULL)
        while(seg->sig != NULL)
        {
            seg = seg->sig;
        }
    return seg;
}

nodoListaScores* buscarNodo(nodoListaScores* lista, int idUsuario)
{
    nodoListaScores* seg;
    seg = lista;

    while ((seg != NULL) && (seg->score.idUsuario!=idUsuario))
    {
        seg=seg->sig;
    }

    return seg;
}

nodoListaScores* agregarFinal(nodoListaScores* lista, nodoListaScores* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
        lista->score.idScore=0;               ///No se rompe (?)
    }
    else
    {
        nodoListaScores* ultimo = buscarUltimo(lista);
        ultimo->sig = nuevoNodo;
    }
    return lista;
}

nodoListaScores* borrarNodoBuscado(nodoListaScores* lista, int idScore)
{
    nodoListaScores* seg;
    nodoListaScores* ante;
    if((lista != NULL) && (lista->score.idScore==idScore))
    {
        nodoListaScores* aux = lista;
        lista = lista->sig;
        free(aux);
    }
    else
    {
        seg = lista;
        while((seg != NULL) && (seg->score.idScore!=idScore))
        {
            ante = seg;
            seg = seg->sig;
        }

        if(seg!=NULL)
        {
            ante->sig = seg->sig;
            free(seg);
        }
    }
    return lista;
}

nodoListaScores* agregarEnOrden(nodoListaScores* lista, nodoListaScores* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {

        if(nuevoNodo->score.puntos < lista->score.puntos)
        {
            lista = agregarPpio(lista, nuevoNodo);
        }
        else
        {
            nodoListaScores* ante = lista;
            nodoListaScores* seg = lista;
            while(seg != NULL && nuevoNodo->score.puntos > seg->score.puntos)
            {
                ante = seg;
                seg = seg->sig;
            }

            ante->sig = nuevoNodo;
            nuevoNodo->sig = seg;
        }
    }
    return lista;
}

nodoListaScores* borrarTodaLaLista(nodoListaScores* lista)
{
    nodoListaScores* proximo;
    nodoListaScores* seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->sig;
        free(seg);
        seg = proximo;
    }
    return seg;
}

nodoListaScores* borrarPrimerNodo(nodoListaScores* lista)
{
    nodoListaScores* aux=lista;
    lista=lista->sig;
    free(aux);
    return lista;
}

nodoListaScores* borrarUltimoNodo(nodoListaScores* lista)
{
    nodoListaScores* aux=lista;
    nodoListaScores* ante;
    while(aux->sig!=NULL)
    {
        ante=aux;
        aux=aux->sig;
    }
    free(aux);
    ante->sig=NULL;
    return lista;
}


void mostrarUnNodo(nodoListaScores* aux)
{
    mostrarUnScore(aux->score);
}

void mostrarUnScore(stScores nodo)
{
    printf("\n ID Score.........: %d ",nodo.idScore);
    printf("\n ID Usuario.......: %d ",nodo.idUsuario);
    printf("\n Puntos...........: %d ",nodo.puntos);//(nodo.puntos>=0)? nodo.puntos:0);
    printf("\n Fecha del Score..: %s \n",nodo.fecha);
    puts("...............................");
}

void recorrerYmostrar(nodoListaScores* lista)
{
    nodoListaScores* aux=lista;
    while(aux)
    {
        mostrarUnNodo(aux);
        puts("\n");
        aux=aux->sig;
    }
}
/// Cuenta la cantidad de Scores de una lista de manera recursiv
int cuentaScores(nodoListaScores* lista)
{
    return ((lista!=NULL)&&(lista->score.idScore>=0))?1+cuentaScores(lista->sig):0;
}

//////////
///fecha///
void fGetNow(char date[])
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(date,128,"%d-%b-%Y %H:%M:%S",tlocal);
}
//////////
////
///cargando//
void cargando()
{
    printf("\nCargando:");
    for(int g=0; g<20; g++)
    {
        printf(".");
        Sleep(100);;
    }
}

void limpia ()
{
    system("pause");
    system("cls");

}


stScores extraeUltimoNodo(nodoListaScores* lista)
{
    nodoListaScores* seg = lista;
    stScores aux;
    if(seg != NULL)
        while(seg->sig != NULL && seg->score.idScore!=0)
        {
            seg = seg->sig;
        }
    strcpy(aux.fecha,seg->score.fecha);
    aux.idScore=seg->score.idScore;
    aux.idUsuario=seg->score.idUsuario;
    aux.puntos=seg->score.puntos;
    return aux;
}




int buscarMenor(stScores a[], int validos, int posInicial)
{
    int posMenor = posInicial;
    int i;

    for(i = posInicial + 1; i < validos; i++)
    {
        if(a[posMenor].puntos > a[i].puntos)
        {
            posMenor = i;
        }
    }
    return posMenor;
}

void ordenacionSeleccion(stScores a[], int validos)
{
    int i;
    for(i = 0; i < validos - 1; i++)
    {
        int posMenor = buscarMenor(a, validos, i);
        stScores aux = a[posMenor];
        a[posMenor] = a[i];
        a[i] = aux;
    }
}

void invertirScores(stScores *a, stScores *b)
{
    stScores temp = *a;
    *a = *b;
    *b = temp;
}

void invertirArreglo(stScores a[], int validos)
{
    int i = 0;
    int j = validos - 1;
    while(i<j)
    {
        invertirScores(&a[i], &a[j]);
        i++;
        j--;
    }
}
