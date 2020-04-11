#include "tetris.h"


void cargarPiezasenFichas(int rot,int fil,int col,char ficha[rot][fil][col],char almacen[rot][fil][col])
{
    int i=0;
    int j=0;
    int k=0;

    for(i=0; i<rot; i++)
    {
        for(j=0; j<fil; j++)
        {
            for(k=0; k<col; k++)
            {
                ficha[i][j][k]=almacen[i][j][k];
            }
        }
    }
}

int rotacionPieza(Pieza piezaN, int rot)
{
    rot++;
    if(rot==4)
        rot=0;
    return rot;
}

void cargarPiezaAJugar(Pieza fija, Pieza enJuego)
{
    int i,j,k;
    enJuego.limite=fija.limite;
    enJuego.color=fija.color;

    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            for(k=0; k<4; k++)
            {
                enJuego.pieza[i][j][k]= fija.pieza[i][j][k];
            }
        }
    }
}

void mostrarTablero (char tablero[FILAT][COLT],char tablerobff[FILAT][COLT], char nombre[],int score) ///Imprime el tablero y analiza como dibujarlo.
{
    system("cls");
    ;
    int i,j;
    for (i=0; i<FILAT-1; i++)
    {
        for(j=0; j<COLT; j++)
        {
            printf(" %c", (tablero[i][j] + tablerobff[i][j]=='1')? 'X' : 250);
        }
        printf("\n");
    }
    printf("Score: %d",score);

    printf("\nJugador: %s\t\t'M' para volver al menu",nombre);
}

void mostrarTableroBuffer (char tablero[FILAT][COLT]) ///Imprime el tablero Buffer y analiza como dibujarlo.
{
    system("cls");

    int i,j;
    for (i=0; i<FILAT-1; i++)
    {
        for(j=0; j<COLT; j++)
        {
            printf(" %c", (tablero[i][j]=='1')? 'X':250);
        }
        printf("\n");
    }
}

void pasaFichaToTablero (int rotacion,int i,int j, char tablero[FILAT][COLT], Pieza enJuego)/// PASA LA FICHA CORRECTAMENTE
{
    int posicion=0;
    int j2=j;   ///tienen que ser iguales///
    int c2=0;
    int c1=0;
    while ((i<FILAT)&&(c1<4))
    {
        while ((j2<COLT)&&(c2<4))
        {
            if (enJuego.pieza[rotacion][c1][c2]=='1')
            {
                tablero[i][j2] = enJuego.pieza[rotacion][c1][c2];
            }
            c2++;
            j2++;
        }
        i++;
        c2=0;
        j2=j;    ///tiene que ser iguales///
        c1++;
        posicion++;
    }
}

void limpiaTablero (char tablero[FILAT][COLT])  ///Limpia el tablero del residuo del movimiento anterior.
{
    int i,j;
    for(i=0; i<FILAT; i++)
    {
        for (j=0; j<COLT; j++)
        {
            tablero[i][j]=0;
        }
    }
}

Pieza fichaRand (Pieza ficha[7])
{
    srand(time(NULL));
    Pieza randFicha;
    int i=0;
    i=rand()%8;
    switch(i)
    {
    case 0:
        randFicha=ficha[0];
        break;
    case 1:
        randFicha=ficha[1];
        break;
    case 2:
        randFicha=ficha[2];
        break;
    case 3:
        randFicha=ficha[3];
        break;
    case 4:
        randFicha=ficha[4];
        break;
    case 5:
        randFicha=ficha[5];
        break;
    case 6:
        randFicha=ficha[6];
        break;
    default:
        randFicha=ficha[rand()%5];
    }
    return randFicha;
}

void pasaAuxToBuffer (Pieza Auxiliar,int rot,int movAbj,int movLat,char tableroBFF[FILAT][COLT])
{
    int j2=movLat;   ///tienen que ser iguales///
    int c2=0;
    int c1=0;

    while ((movAbj<FILAT)&&(c1<4))
    {
        while ((j2<COLT)&&(c2<4))
        {
            if (Auxiliar.pieza[rot][c1][c2]=='1')
            {
                tableroBFF[movAbj][j2] = Auxiliar.pieza[rot][c1][c2];
            }
            c2++;
            j2++;
        }
        movAbj++;
        c2=0;
        j2=movLat;    ///tiene que ser iguales///
        c1++;
    }
    mostrarTableroBuffer(tableroBFF);
}

void hidecursor() ///Esconde la linea que espera la pulsacion de teclado (ayuda a que la pantalla refresque un poco mas rapido)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int verificFilaCompleta (char tableroBFF [FILAT][COLT],char tablero[FILAT][COLT]) ///Verifica si la fila esta completa, la borra y deciende lo que esta arriba
{
    int i,j,suma;
    int contador=0;
    int score=0;

    for(j=0; j<FILAT; j++)
    {
        suma=0;
        for (i=0; i<COLT; i++)
        {
            if(tableroBFF[j][i]!=0)
                suma++;
        }
        if (suma==COLT)
        {
            int k,l;
            for(k=j; k>=1; k--)
            {
                for(l=0; l<COLT; l++)
                    tableroBFF[k][l]=tableroBFF[k-1][l];
            }
            for(l=0; l<COLT; l++)
            {
                tableroBFF[k][l]=tablero[k][l];
            }
            score=50;
        }
    }
    return score;
}

int verificaLugar (Pieza enJuego,int rot, char tableroBFF[FILAT][COLT],int movAbajo,int movLat)
{
    int i,j;
    int flag=0;
    for(i=0; i<enJuego.limite; i++)
    {
        for(j=0; j<enJuego.limite; j++)
        {
            if(enJuego.pieza[rot][i][j]=='1')
            {
                if(tableroBFF[movAbajo+1+i][movLat+j]=='1')
                {
                    pasaAuxToBuffer(enJuego,rot,movAbajo,movLat,tableroBFF);
                    flag=1;
                }
            }
        }
    }
    return flag;
}

int verificaLateral (Pieza enJuego,int rot, char tableroBFF[FILAT][COLT],int movAbajo,int movLat)
{
    int i,j;
    int flag=0;
    if(enJuego.color==7)
        movLat--;
    for(i=0; i<enJuego.limite; i++)
    {
        for(j=0; j<enJuego.limite; j++)
        {
            if(enJuego.pieza[rot][i][j]=='1')
            {
                if(tableroBFF[movAbajo+i][movLat+j]=='1')
                {
                    flag=1;
                }
                if(tableroBFF[movAbajo+i][movLat+j])
                {
                    flag=-1;
                }
            }
        }
    }
    return flag;
}
///------------------------------------------------------------------------------------------------------------------------------------------------
int verificaTablero (int movLat)
{
    int flag=0;
    int movder=movLat;
    int movizq=movLat+1;
    if(movder<=-1)
        flag=-1;
    else if(movizq>11)
        flag=1;

    return flag;
}

void color(int x)                                                               /// Cambia la combinacion de color de fondo y frente
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

char getch_noblock(int nivel)
{
    if (kbhit())
        return getch();
    else
        Sleep(nivel);
    return 's';
}

int verificaPerdidaTope (char tablero[FILAT][COLT])
{
    int flag=0;
    for(int i=0; i<COLT; i++)
    {
        if(tablero[1][i]!=0)
        {
            flag=1;
        }
    }
    return flag;
}

int juegoTetris(char elJugador[],int score)
{
    SetConsoleTitle("Tetris ERROR 404 v2.0 UTN MDP [JUN-2019]");
    hidecursor();
    char tablero[FILAT][COLT] = {0};
    char tableroBuffer[FILAT][COLT] = {0};
    int rotacion=0;
    int flag=0;
    int flagPerdida=0;
    int flagSalir=0;
    char ctrlMovimiento;
    int selecPieza=0;
    int movAbajo=0;
    int movLateral=0;
///------------------------------------------------------------------------------------------------------------------------------------------------
    Pieza fichaL,fichaLI,fichaS,fichaSI,fichaT,fichaC,fichaP;
    ///ficha L
    fichaL.activa =1;
    fichaL.limite =4;
    fichaL.color =1;
    ///ficha L Invertida
    fichaLI.activa =1;
    fichaLI.limite =4;
    fichaLI.color =2;
    ///ficha S
    fichaS.activa =1;
    fichaS.limite =4;
    fichaS.color =3;
    ///ficha S Invertida
    fichaSI.activa =1;
    fichaSI.limite =4;
    fichaSI.color =4;
    ///ficha T
    fichaT.activa=1;
    fichaT.limite=4;
    fichaT.color=5;
    ///ficha Cubo
    fichaC.activa =1;
    fichaC.limite =4;
    fichaC.color =6;
    ///ficha Palo
    fichaP.activa =1;
    fichaP.limite =4;
    fichaP.color =7;

    ///Almacenes de fichas para introducir en la estructura pieza.ficha
    char almacenELE[4][4][4]=
    {
        {
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','1','1','0'},
            {'0','0','0','0'}
        },{
            {'0','0','0','0'},
            {'1','1','1','0'},
            {'1','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        },{
            {'0','0','1','0'},
            {'1','1','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenELEI[4][4][4]=
    {
        {
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'1','1','0','0'},
            {'0','0','0','0'}
        },{
            {'1','0','0','0'},
            {'1','1','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'1','0','0','0'},
            {'1','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','1','0'},
            {'0','0','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenESE[4][4][4]=
    {
        {
            {'0','1','1','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','0','0','0'},
            {'1','1','0','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','1','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','0','0','0'},
            {'1','1','0','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenESEI[4][4][4]=
    {
        {
            {'1','1','0','0'},
            {'0','1','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','0','0'},
            {'1','1','0','0'},
            {'1','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'0','1','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','0','0'},
            {'1','1','0','0'},
            {'1','0','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenLAT[4][4][4]=
    {
        {
            {'0','1','0','0'},
            {'1','1','1','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','0','0'},
            {'0','1','1','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        },{
            {'0','0','0','0'},
            {'1','1','1','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','0','0'},
            {'1','1','0','0'},
            {'0','1','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenCUBO[4][4][4]=
    {
        {
            {'1','1','0','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'1','1','0','0'},
            {'1','1','0','0'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        }
    };
    char almacenPALO[4][4][4]=
    {
        {
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','1','0','0'}
        },{
            {'0','0','0','0'},
            {'1','1','1','1'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        },{
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','1','0','0'},
            {'0','1','0','0'}
        },{
            {'0','0','0','0'},
            {'1','1','1','1'},
            {'0','0','0','0'},
            {'0','0','0','0'}
        }
    };
    ///carga de las matrices en las estruc
    cargarPiezasenFichas(4,4,4,fichaL.pieza,almacenELE);
    cargarPiezasenFichas(4,4,4,fichaLI.pieza,almacenELEI);
    cargarPiezasenFichas(4,4,4,fichaS.pieza,almacenESE);
    cargarPiezasenFichas(4,4,4,fichaSI.pieza,almacenESEI);
    cargarPiezasenFichas(4,4,4,fichaT.pieza,almacenLAT);
    cargarPiezasenFichas(4,4,4,fichaC.pieza,almacenCUBO);
    cargarPiezasenFichas(4,4,4,fichaP.pieza,almacenPALO);
    Pieza ficHas[7]= {fichaL,fichaLI,fichaS,fichaSI,fichaT,fichaC,fichaP};
    Pieza enJuego;
    int nivel=150; /// intermedio 10-30-60-100-120-150


    mostrarTablero(tablero,tableroBuffer,elJugador,score);

    do
    {
        enJuego=fichaRand(ficHas);
        do
        {


            fflush(stdin);
            //ctrlMonvimiento=getch(); ///De esta manera no se ve el caracter que se preciona

            ctrlMovimiento=getch_noblock(nivel); ///De esta manera si no se preciona ninguna tecla la ficha baja sola
            // nivel--;
            if (ctrlMovimiento=='r') ///r cambia la rotacion de la pieza
            {
                limpiaTablero(tablero);
                rotacion=rotacionPieza(fichaT,rotacion);
                pasaFichaToTablero(rotacion,movAbajo,movLateral, tablero,enJuego);
                mostrarTablero(tablero,tableroBuffer,elJugador,score);
            }
            else if (ctrlMovimiento=='s')   ///s hace un descenso controlado (1 espacio)
            {
                limpiaTablero(tablero);
                movAbajo++;
                pasaFichaToTablero(rotacion,movAbajo,movLateral,tablero,enJuego);
                mostrarTablero(tablero,tableroBuffer,elJugador,score);
            }
            else if (ctrlMovimiento=='d')    ///d mueve la pieza hacia la derecha
            {
                limpiaTablero(tablero);
                movLateral++;
                if (verificaLateral(enJuego,rotacion,tableroBuffer,movAbajo,movLateral)==1)
                    movLateral-- ;
                if (verificaTablero(movLateral)==1)
                    movLateral--;
                pasaFichaToTablero(rotacion,movAbajo,movLateral,tablero,enJuego);
                mostrarTablero(tablero,tableroBuffer,elJugador,score);
                selecPieza++;
            }
            else if (ctrlMovimiento=='a')   ///a mueve la ficha hacia la izquierda
            {
                limpiaTablero(tablero);
                movLateral--;

                if (verificaLateral(enJuego,rotacion,tableroBuffer,movAbajo,movLateral)==-1)
                    movLateral++ ;
                if (verificaTablero(movLateral)==-1)
                    movLateral++;
                pasaFichaToTablero(rotacion,movAbajo,movLateral,tablero,enJuego);
                mostrarTablero(tablero,tableroBuffer,elJugador,score);
                selecPieza--;

            }
            else if (ctrlMovimiento=='m')   ///m termina el juego
            {
                system("cls");
                flagSalir=1;
            }
            flag=verificaLugar(enJuego,rotacion,tableroBuffer,movAbajo,movLateral);

            score+=verificFilaCompleta(tableroBuffer,tablero);
        }

        while((movAbajo<20)&&(flag!=1)&&flagSalir==0);  ///condicion para reingreso de fichas
        enJuego.activa=0;
        pasaAuxToBuffer(enJuego,rotacion,movAbajo,movLateral,tableroBuffer);
        movAbajo=0;
        flag=0;
        flagPerdida=verificaPerdidaTope(tablero);
    }
    while(flagPerdida==0&&flagSalir==0);  /// futura condicion de perdida (fichas muertas en fil 1 o 2)
    if(flagPerdida==1)
        printf("\n\n PERDISTE");
    Sleep(120);
    system("cls");
    //limpiaTablero(tablero);
    return score;
}
