#include "raya.h"


///--------------------------3--En--Raya--------------------------------------------------------------///

void muestraTablero(table unTablero,int puntos)
{
    int i,j;
    int nivel=0;
    int id=0;
    system("cls");
    printf("Score:\t%d\n",puntos);
    for(i=0; i<COLR; i++)
    {
        printf("\n");
        for(j=0; j<FILR; j++)
        {
            if((i%2==0)&&(j%2==0))
            {
                if(unTablero.layout[i][j]=='1')              ///HUMANO
                {
                    printf("  X ",unTablero.layout[i][j]);
                    nivel++;
                }
                else if(unTablero.layout[i][j]=='2')         ///IA
                {
                    printf("  O ",unTablero.layout[i][j]);
                    nivel++;
                }
                else
                    printf("    ");
            }
            else if((i%2!=0))
                printf("---");
            else
                printf("|");

        }

    }
    unTablero.nivel=nivel;
    id=codigoTablero(unTablero);
    unTablero.id=id;
    printf("\nCODIGO:\t %d",unTablero.id);
    printf("\n\nNIVEL:\t %d",unTablero.nivel);
    printf("\nSiguientes Posibles:");
    for(int k=0; k<9; k++)
    {
        if(unTablero.siguientes[k]!=0)
            printf("  %d   ",unTablero.siguientes[k]);
    }
}

int nivelTablero(table unTablero)
{
    int nivel=0;
    int i,j;
    for(i=0; i<COLR; i=i+2)
    {
        for(j=0; j<FILR; j=j+2)
        {
            if(unTablero.layout[i][j]!=' ')
                nivel++;
        }
    }
    return nivel;
}

int potencia(int num, int pot)
{
    int i;

    for(i=0; i<pot; i++)
    {
        num=num*10;
    }
    return num;
}

jugada traducirJugada(int numero)
{
    jugada unaJugada;
    do
    {
        switch(numero)
        {
        case 1:
            unaJugada.i=4;
            unaJugada.j=0;
            break;
        case 2:
            unaJugada.i=4;
            unaJugada.j=2;
            break;
        case 3:
            unaJugada.i=4;
            unaJugada.j=4;
            break;
        case 4:
            unaJugada.i=2;
            unaJugada.j=0;
            break;
        case 5:
            unaJugada.i=2;
            unaJugada.j=2;
            break;
        case 6:
            unaJugada.i=2;
            unaJugada.j=4;
            break;
        case 7:
            unaJugada.i=0;
            unaJugada.j=0;
            break;
        case 8:
            unaJugada.i=0;
            unaJugada.j=2;
            break;
        case 9:
            unaJugada.i=0;
            unaJugada.j=4;
            break;
        default:
            printf("\n\t INGRESE UN NUMERO VALIDO (1-9)\n");
        }
    }
    while((numero<0)&&(numero>10));
    return  unaJugada;
}



int codigoTablero(table unTablero)
{
    long int codigo=0;
    long int cont=0;
    for(int i=0; i<FILR; i=i+2)
    {
        for(int j=0; j<COLR; j=j+2)
        {
            if(unTablero.layout[i][j]=='1')
                codigo=codigo+1*(potencia(1,8-cont));
            else if (unTablero.layout[i][j]=='2')
                codigo=codigo+2*(potencia(1,8-cont));
            cont=cont+1;
        }
    }
    return codigo;
}

table siguientesJugadas(table unTablero)
{
    int k=1;
    int l=0;
    for(int i=0; i<5; i=i+2)
    {
        for(int j=0; j<5; j=j+2)
        {
            if(unTablero.layout[i][j]==' ')
            {
                switch(k)
                {
                case 1:
                    unTablero.siguientes[l]=7;
                    l++;
                    break;
                case 2:
                    unTablero.siguientes[l]=8;
                    l++;
                    break;
                case 3:
                    unTablero.siguientes[l]=9;
                    l++;
                    break;
                case 4:
                    unTablero.siguientes[l]=4;
                    l++;
                    break;
                case 5:
                    unTablero.siguientes[l]=5;
                    l++;
                    break;
                case 6:
                    unTablero.siguientes[l]=6;
                    l++;
                    break;
                case 7:
                    unTablero.siguientes[l]=1;
                    l++;
                    break;
                case 8:
                    unTablero.siguientes[l]=2;
                    l++;
                    break;
                case 9:
                    unTablero.siguientes[l]=3;
                    l++;
                    break;
                default:
                    printf("\n\t ERROR \n");
                }
            }
            k++;
        }

    }
    while(l<9)
    {
        unTablero.siguientes[l]=0;
        l++;
    }
    return unTablero;
}

int evaluaVictoria(table unTablero)
{
    int victoria=0;
    int i,j;

    for(i=0; i<FILR; i=i+2)
    {
        if ((unTablero.layout[i][0] == unTablero.layout[i][2])&&(unTablero.layout[i][2]== unTablero.layout[i][4])&&(unTablero.layout[i][4]=='2'))       ///2 es la O
            victoria--;
        else if ((unTablero.layout[i][0] == unTablero.layout[i][2])&&(unTablero.layout[i][2]== unTablero.layout[i][4])&&(unTablero.layout[i][4]=='1'))    ///1 es la X
            victoria++;
    }
    for (j=0; j<COLR; j=j+2)
    {
        if ((unTablero.layout[0][j] == unTablero.layout[2][j])&&(unTablero.layout[2][j] == unTablero.layout[4][j])&&(unTablero.layout[4][j]=='2'))        ///2 es la O
            victoria--;
        else if ((unTablero.layout[0][j] == unTablero.layout[2][j])&&(unTablero.layout[2][j] == unTablero.layout[4][j])&&(unTablero.layout[4][j]=='1'))   ///1 es la X
            victoria++;
    }
    if ((unTablero.layout[0][0] == unTablero.layout[2][2])&&(unTablero.layout[2][2]==unTablero.layout[4][4])&&(unTablero.layout[4][4]=='2'))         ///2 es la O
        victoria--;
    else if ((unTablero.layout[0][0] == unTablero.layout[2][2])&&(unTablero.layout[2][2]==unTablero.layout[4][4])&&(unTablero.layout[4][4]=='1'))    ///1 es la X
        victoria++;
    if ((unTablero.layout[0][4] == unTablero.layout[2][2])&&(unTablero.layout[2][2]==unTablero.layout[4][0])&&(unTablero.layout[4][0]=='2'))         ///2 es la O
        victoria--;
    else if ((unTablero.layout[0][4] == unTablero.layout[2][2])&&(unTablero.layout[2][2]==unTablero.layout[4][0])&&(unTablero.layout[4][0]=='1'))    ///1 es la X
        victoria++;

    return victoria;
}

int retornaMIN(table unTablero)
{
    int min=0;

    min=evaluaVictoria(unTablero);
    if((min!=1)&&(min!=-1))
    {
        for(int i=0; i<FILR; i=i+2)
        {
            for(int j=0; j<COLR; j=j+2)
            {
                if (unTablero.layout[i][j]==' ')
                    unTablero.layout[i][j]='2';
            }
        }
    }
    min=evaluaVictoria(unTablero);
    return min;
}

int retornaMAX(table unTablero)
{
    int max=0;

    max=evaluaVictoria(unTablero);
    if((max!=1)&&(max!=-1))
    {
        for(int i=0; i<FILR; i=i+2)
        {
            for(int j=0; j<COLR; j=j+2)
            {
                if (unTablero.layout[i][j]==' ')
                    unTablero.layout[i][j]='1';
            }
        }
    }
    max=evaluaVictoria(unTablero);
    return max;
}

void pasaLaytoTable(char lay[COLR][FILR],char unTable[COLR][FILR])
{
    for(int i=0; i<COLR; i++)
    {
        for(int j=0; j<FILR; j++)
        {
            unTable[i][j]=lay[i][j];
        }
    }
}

int buscaMenorJugada(jugada arreglo[8],int validos)
{
    int menor=arreglo[0].valor;
    int posmenor=0;
    for(int i=0; i<validos; i++)
    {
        if(arreglo[i].valor<menor)
        {
            menor=arreglo[i].valor;
            posmenor=i;
        }
    }

    return posmenor;
}

int buscaMayorJugada(jugada arreglo[8],int validos)
{
    int mayor=arreglo[0].valor;
    int posMayor=0;
    for(int i=0; i<validos; i++)
    {
        if(arreglo[i].valor>mayor)
        {
            mayor=arreglo[i].valor;
            posMayor=i;
        }
    }

    return posMayor;
}

jugada mejorMove(table unTablero)
{
    jugada mejor;
    int mejorValor;
    int valor=0;
    int cont=0;
    jugada arreglo[8];
    for(int i=0; i<FILR; i=i+2)
    {
        for(int j=0; j<COLR; j=j+2)
        {
            if(unTablero.layout[i][j]==' ')
            {
                unTablero.layout[i][j]='2';
                valor=retornaMAX(unTablero);
                mejor.i=i;
                mejor.j=j;
                mejor.valor=valor;
                arreglo[cont]=mejor;
                cont++;
                unTablero.layout[i][j]=' ';
            }
        }
    }
    mejorValor=buscaMenorJugada(arreglo,cont);
    mejor=arreglo[mejorValor];
    return mejor;
}

jugada peorMove(table unTablero)
{
    jugada peor;
    int peorValor;
    int valor=0;
    int cont=0;
    jugada arreglo[8];
    for(int i=0; i<FILR; i=i+2)
    {
        for(int j=0; j<COLR; j=j+2)
        {
            if(unTablero.layout[i][j]==' ')
            {
                unTablero.layout[i][j]='1';
                valor=retornaMIN(unTablero);
                peor.i=i;
                peor.j=j;
                peor.valor=valor;
                arreglo[cont]=peor;
                cont++;
                unTablero.layout[i][j]=' ';
            }
        }
    }
    peorValor=buscaMayorJugada(arreglo,cont);
    peor=arreglo[peorValor];
    return peor;
}

jugada laJugada(table unTablero)
{

    jugada unaJugada;
    jugada otraJugada;
    int victoria=0;
    int derrota=0;

    unaJugada=mejorMove(unTablero);
    unTablero.layout[unaJugada.i][unaJugada.j]='2';
    victoria=evaluaVictoria(unTablero);

    if(victoria!=-1)
    {
        otraJugada=peorMove(unTablero);
        unTablero.layout[otraJugada.i][otraJugada.j]='1';
        derrota=evaluaVictoria(unTablero);
        if(derrota==1)
            unaJugada=otraJugada;
    }
    return unaJugada;
}

jugada la2Jugada(table unTablero)
{

    jugada unaJugada;
    jugada otraJugada;
    int victoria=0;
    int derrota=0;

    unaJugada=mejorMove(unTablero);
    unTablero.layout[unaJugada.i][unaJugada.j]='2';
    victoria=evaluaVictoria(unTablero);

    if(victoria!=-1)
    {
        otraJugada=peorMove(unTablero);
        unTablero.layout[otraJugada.i][otraJugada.j]='1';
        derrota=evaluaVictoria(unTablero);


        if(derrota==1)
            unaJugada=otraJugada;
        else if(derrota!=1&&derrota!=0)
            otraJugada=laJugada(unTablero);
    }
//    else if(derrota==1)
    //   unaJugada=otraJugada;
    return unaJugada;
}

int skinetWins()
{
    for(int i=0; i<10; i++)
    {
        system("color 59");
        printf("\tSKINET WINS");
        Sleep(10);
        system("color 69");
    }
    return 1;
}

///----------------------------Arbol----------------------------------------------------------------------///


nodoArbol* plantarArbol()
{
    return NULL;
}

nodoArbol* crearNodoArbol(table dato)
{
    nodoArbol* aux = (nodoArbol*)malloc(sizeof(nodoArbol));
    aux->dato = dato;
    aux->arbol_1=plantarArbol();
    aux->arbol_2=plantarArbol();
    aux->arbol_3=plantarArbol();
    aux->arbol_4=plantarArbol();
    aux->arbol_5=plantarArbol();
    aux->arbol_6=plantarArbol();
    aux->arbol_7=plantarArbol();
    aux->arbol_8=plantarArbol();
    aux->arbol_9=plantarArbol();

    return aux;
}

nodoArbol * buscarArbol(nodoArbol* arbol, table dato)
{
    nodoArbol* rta = NULL;
    int flag=0;

    if(arbol!=NULL)
    {
        if(arbol->dato.id==dato.id)
        {
            rta=arbol;
        }
        else
        {
            for(int i=0; i<9; i++)
            {
                do
                {
                    switch(i)
                    {
                    case 0:
                        rta=buscarArbol(arbol->arbol_1,dato);
                        if(rta)
                            flag=1;

                        break;
                    case 1:
                        rta=buscarArbol(arbol->arbol_2,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 2:
                        rta=buscarArbol(arbol->arbol_3,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 3:
                        rta=buscarArbol(arbol->arbol_4,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 4:
                        rta=buscarArbol(arbol->arbol_5,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 5:
                        rta=buscarArbol(arbol->arbol_6,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 6:
                        rta=buscarArbol(arbol->arbol_7,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 7:
                        rta=buscarArbol(arbol->arbol_8,dato);
                        if(rta)
                            flag=1;
                        break;
                    case 8:
                        rta=buscarArbol(arbol->arbol_9,dato);
                        if(rta)
                            flag=1;
                        break;
                    default:
                        flag=1;
                    }
                }
                while (flag==0);
            }
        }
    }
    return rta;
}

/*nodoArbol* insertarArbol(nodoArbol* arbol, table dato)
{
    int flag=0;
    if(arbol == NULL)
    {
        arbol = crearNodoArbol(dato);
    }
    else
    {
        for(int i=0; i<9; i++)
        {
            do
            {
                switch(i)
                {
                case 0:
                    if(arbol->arbol_1==NULL)
                    {
                        arbol->arbol_1=insertarArbol(arbol->arbol_1,dato);
                        flag=1;
                    }
                    break;
                case 1:
                    if(arbol->arbol_2==NULL)
                    {
                        arbol->arbol_2=insertarArbol(arbol->arbol_2,dato);
                        flag=1;
                    }
                    break;
                case 2:
                    if(arbol->arbol_3==NULL)
                    {
                        arbol->arbol_3=insertarArbol(arbol->arbol_3,dato);
                        flag=1;
                    }
                    break;
                case 3:
                    if(arbol->arbol_4==NULL)
                    {
                        arbol->arbol_4=insertarArbol(arbol->arbol_4,dato);
                        flag=1;
                    }
                    break;
                case 4:
                    if(arbol->arbol_5==NULL)
                    {
                        arbol->arbol_5=insertarArbol(arbol->arbol_5,dato);
                        flag=1;
                    }
                    break;
                case 5:
                    if(arbol->arbol_6==NULL)
                    {
                        arbol->arbol_6=insertarArbol(arbol->arbol_6,dato);
                        flag=1;
                    }
                    break;
                case 6:
                    if(arbol->arbol_7==NULL)
                    {
                        arbol->arbol_7=insertarArbol(arbol->arbol_7,dato);
                        flag=1;
                    }
                    break;
                case 7:
                    if(arbol->arbol_8==NULL)
                    {
                        arbol->arbol_8=insertarArbol(arbol->arbol_8,dato);
                        flag=1;
                    }
                    break;
                case 8:
                    if(arbol->arbol_9==NULL)
                    {
                        arbol->arbol_9=insertarArbol(arbol->arbol_9,dato);
                        flag=1;
                    }
                    break;
                default:
                    flag=1;
                }
            }
            while (flag==0);
        }



    }
    return arbol;
}

void muestraArbol(nodoArbol* arbol)
{
    if(arbol!=NULL)
    {
        printf(" %d ",arbol->dato.id);
        muestraArbol(arbol->arbol_1);
        muestraArbol(arbol->arbol_2);
        muestraArbol(arbol->arbol_3);
        muestraArbol(arbol->arbol_4);
        muestraArbol(arbol->arbol_5);
        muestraArbol(arbol->arbol_6);
        muestraArbol(arbol->arbol_7);
        muestraArbol(arbol->arbol_8);
        muestraArbol(arbol->arbol_9);
    }
}

int contarNodosArbol(nodoArbol* arbol)
{
    int cuenta=0;
    if(arbol)
    {
        cuenta=1;
        cuenta=cuenta+contarNodosArbol(arbol->arbol_1)+contarNodosArbol(arbol->arbol_2)+contarNodosArbol(arbol->arbol_3)+contarNodosArbol(arbol->arbol_4)+contarNodosArbol(arbol->arbol_5)+contarNodosArbol(arbol->arbol_6)+contarNodosArbol(arbol->arbol_7)+contarNodosArbol(arbol->arbol_8)+contarNodosArbol(arbol->arbol_9);
    }
    return cuenta;
}

int contarNodosHoja(nodoArbol* arbol)
{
    int cuenta=0;
    if(arbol)
    {
        if(arbol->arbol_1==NULL && arbol->arbol_2==NULL && arbol->arbol_3==NULL && arbol->arbol_4==NULL && arbol->arbol_5==NULL && arbol->arbol_6==NULL && arbol->arbol_7==NULL && arbol->arbol_8==NULL && arbol->arbol_9==NULL)
            cuenta=1;
        else
            cuenta=cuenta+contarNodosHoja(arbol->arbol_1)+contarNodosHoja(arbol->arbol_2)+contarNodosHoja(arbol->arbol_3)+contarNodosHoja(arbol->arbol_4)+contarNodosHoja(arbol->arbol_5)+contarNodosHoja(arbol->arbol_6)+contarNodosHoja(arbol->arbol_7)+contarNodosHoja(arbol->arbol_8)+contarNodosHoja(arbol->arbol_9);
    }
    return cuenta;
}
*/
///-------------------------Arr-De--Arbol--------------------------------------------------///

void inicArrDeArb(celda arrDeArb[])
{
    strcpy(arrDeArb[0].identificador,"Empieza_X");
    strcpy(arrDeArb[1].identificador,"Empieza_O");
    arrDeArb[0].opcion=0;
    arrDeArb[1].opcion=1;
    arrDeArb[0].arbol=plantarArbol();
    arrDeArb[1].arbol=plantarArbol();
}

int juegoTaTeTi(char elJugador[])
{
    SetConsoleTitleA("TP FINAL LAB 2 | ERROR 404 TM");

    table elTablero;
    jugada iaJugada;
    jugada ia2Jugada;
    int jugadaPlayer;
    celda arrDeArb[2];
    inicArrDeArb(arrDeArb);
    int puntos=10;
    char control='s';


    do
    {
        int turno=0;
        int the_end=0;
        char prueba[FILR][COLR]=
        {
            ///  A       A       A
            {' ',' ',' ',' ',' '},///<---ESTA
            {' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' '},///<---ESTA
            {' ',' ',' ',' ',' '},
            {' ',' ',' ',' ',' '}///<---ESTA
        };
        pasaLaytoTable(prueba,elTablero.layout);
        elTablero=siguientesJugadas(elTablero);

        muestraTablero(elTablero,puntos);
        printf("\nUSUARIO: %s",elJugador);
        printf("\n\nUtilice el KEYPAD para jugar ");


        do
        {
            if(turno%2==0)
            {
jugadaInvalida:
                puts("\n");
                fflush(stdin);
                jugadaPlayer=getch();

                ia2Jugada=traducirJugada(jugadaPlayer-48);

                if(elTablero.layout[ia2Jugada.i][ia2Jugada.j]==' ')
                {
                    elTablero.layout[ia2Jugada.i][ia2Jugada.j]='1';
                }
                else
                {
                    printf("\nJugada INVALIDA\n");
                    goto jugadaInvalida;
                }

                muestraTablero(elTablero,puntos);
            }
            else
            {
                iaJugada=la2Jugada(elTablero);
                elTablero.layout[iaJugada.i][iaJugada.j]='2';
                elTablero=siguientesJugadas(elTablero);
                muestraTablero(elTablero,puntos);
            }

            turno++;
            the_end=evaluaVictoria(elTablero);
            elTablero.nivel=nivelTablero(elTablero);
            elTablero=siguientesJugadas(elTablero);
        }
        while(elTablero.nivel<9&&the_end!=1&&the_end!=-1);

        printf("\n%s\n ",(the_end==-1)? "SKINET WINS"/*skinetWins(1)*/:(the_end==1)? "BRAVO JHON KOINOR":"EMPATASTE...");

        if(the_end>0)
            puntos++;
        else if (the_end<0)
            puntos--;


        puts("\n\nJUGAR DE NUEVO: S/N\t");
        tolower(control=getch());

    }
    while(control=='s'&&puntos>0);

    /*printf("\n\n %d\t %s",arrDeArb[0].opcion,arrDeArb[0].identificador);
    printf("\n %d\t %s",arrDeArb[1].opcion,arrDeArb[1].identificador);*/




    return puntos;
}
