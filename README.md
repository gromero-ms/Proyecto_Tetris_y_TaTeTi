# Proyecto Tetris y Ta Te Ti en C - Error 404 - UTN
## Tetris y Ta Te Ti en C - Error 404 - UTN
Con el propósito fundamental de integrar todo lo aprendido durante la cursa de la materia laboratorio 1, nos propusimos a desarrollar el clásico videojuego de puzzle Tetris.
Originalmente diseñado y programado por Alekséi Pázhitnov en la Unión Soviética. Fue lanzado el 6 de junio de 1984,  mientras trabajaba para el Centro de Computación Dorodnitsyn de la Academia de Ciencias de la Unión Soviética en Moscú.
Año 2019 y nosotros, dos estudiantes de programación en nuestro primer año, tratamos de emularlo, sin utilizar librerías graficas como graphic.h o ncurses , solo las propias de C, sin saber todo lo que nos depararía sumergirnos en el desarrollo de tan icónico juego.
 
###### Desarrollo

Todo comenzó con las primeras clases de Programación 1 donde en el mes de mayo vimos el tema de matrices, automáticamente el primer ejemplo que se vino  a nuestras mentes fue la ficha de Tetris el ***tetrominó***. Un Tetrominó es una forma geométrica compuesta de cuatro cuadrados iguales. Partiendo de esa premisa es que basamos el desarrollo del juego en función a diversas matrices que interactúan entre ellas. 

###### Piezas:

Las mismas se encuentran representadas dentro de una matriz de 4 x 4, completa con 0 y 1 en donde queremos dibujar la figura. Se necesita una matriz de estas dimensiones para cada una de las rotaciones, por lo tanto, tenemos como máximo 4 rotaciones por ficha. Esto nos deja con una matriz tridimensional de 4 x 4 x 4 :

## **char piezaELE [4]     [4]   [4]; 
##                 Rotacion Fila Columna**

**La primera estructura** contiene la información de la Pieza:
``` c
typedef struct
{
    int color;           		//próximamente tendrán color**	        
    int limite;             //Maxima extencion horizontal y vertical
    char pieza[4][4][4];    //Matriz 3-D 
} Pieza;	
```
Se carga por parámetro cada una de las pieza, en total 7 (siete)	:

***Pieza L             -        Pieza Z       -         Pieza S       -     Pieza T
Pieza T invertida     - Pieza Cuadrado  -     Pieza I***

###### Tablero:
 En el tablero también contamos con una matriz, en este caso de dos dimensiones la cual mostrara en pantalla la interfaz del juego, TABLERO DE TETRIS. En este caso la matriz utilizada es de 24 x 12:

**char tablero[24][12];**

Ya que los valores de las filas y las columnas se mantienen constante durante todo el juego, vimos convenientes definirlas como constantes:
``` c
#define FILAT 24 
#define COLT 12
```

###### Tablero Buffer: 
Al trabajar con un lenguaje como el C necesitamos generar la menos cantidad de limpiezas de pantalla system(“cls”) y re impresiones para evitar el parpadeo al momento de imprimir algo en consola. Por lo tanto, creamos una matriz adicional de tipo Char para almacenar las piezas, que al momento de llegar a la última fila (el final del tablero) queden quietas y pasan del tablero principal al Tablero Buffer
**char tableroBuffer[FILAT][COLT]**;

###### Juego: 
Una vez definidas las piezas y los tableros se procede a desarrollar el juego. Se crea una función la cual mediante la función srand() selecciona de manera random una Pieza y la carga en la pieza que pasara a ser Pieza enJuego. Esta pieza pasara a ser la que se imprima dentro de las matrices tablero. 
Toda esta interacción entre el usuario y la consola se realiza con una función que toma la tecla (carácter) que presiona el usuario y modifica una de las las variables dentro de la función que imprime la pieza en el tablero principal.
``` c
void pasaFichaToTablero (int rotacion,int i,int j, char tablero [FILAT][COLT] , Pieza enJuego);
int rotación;        ///recibe la rotación de la ficha que esta en juego.
int i;              ///la primera fila actual donde se encuentra
int j;              ///la primera columna actual donde se encuentra 
char tablero [][]; //el tablero principal
Pieza enJuego;     ///la pieza en juego
```

De esta manera se logra copiar lo contenido en la matriz Pieza a la matriz tablero en la posición específica, la cual es modificada gracias al carácter que presiona el usuario. Aumentando o disminuyendo el valor de i (mov Abajo), j (mov lateral) y la rotación.
Una vez que el valor de “i” llega a tener el mismo valor que la cantidad de filas totales menos el limite de la pieza, se realiza la función de pasaFichaToTablero pero en este caso el tablero que recibe es la del tablero buffer para lograr almacenar las fichas en ese lugar.
De esta manera el juego avanza hasta que se cumpla el objetivo del TETRIS, **lograr llenar una fila por completo:**
Para poder analizar esta situación creamos una función la cual va leyendo todo el tablero, y verificando si en cada una de las columnas de la misma ficha se encuentran valores iguales a 1 ( no olvidemos que las matrices marcaban el dibujo con un 1 detrás). Cuando la función encuentra un 1 aumenta en uno el contador suma, luego de recorrer todas las columnas analiza, si el valor contenido en suma es mayor o igual a numero de COLT (12) y de ser así marca esa fila como completa. Anidado se encuentra otro for el cual cambia los valores de la fila completa por los valores que están en el Tablero principal (los cuales son 0 ceros) y los pega sobre la fila seleccionada. Por ultimo y no así menos, se desplaza todo el contenido de la matriz Tablero Buffer una posición hacia abajo y se aumenta el puntaje del jugador!:


###### Función de verificar fila completa:
``` c
void verificFilaCompleta (char tableroBFF [FILAT][COLT],char tablero[FILAT][COLT])
 {
    int i,j,suma;
    for(j=0; j<FILAT; j++)
    {
        suma=0;
        for (i=0; i<COLT; i++)
        {
           if(tableroBFF[j][i]!=0) suma++;
        }
        if (suma==COLT)
        {
            int k,l;
            for(k=j; k>=1; k--)
                for(l=0;l<COLT;l++)
                    tableroBFF[k][l]=tablero[k][l];
                    for(l=0;l<COLT;l++)
                    tableroBFF[k][l]=tableroBFF[k-1][l];
        }
    }
}
```
El juego continuo hasta que el jugador presiona la tecla “m” para salir. Se muestra el Score y la tabla de posiciones la cual esta almacenada en un archivo junto con el archivo de jugadores. 

###### TA TE TI ( 3 en RAYA)


###### Desarrollo
Al interiorizarnos más en la programación y con nuevos conceptos tales como el de recursión
a nuestra disposición, una vez más lo primero que tuvimos que definir fue nuestra estructura
base que en este caso fue nuestro tablero y como interactuar con él.


###### Tablero:
Si bien la representación de un tablero de 3 en raya es una matriz simple de 3 X 3, esto
presento un problema a la hora de representarlo visualmente, por lo que finalmente su
representación paso a ser una matriz de 5 X 5 en la cual las filas y columnas 2 y 4 solo se
usaron para la impresión de las delimitaciones y los 9 espacios restantes como área de juego
por lo que todas las funciones de análisis y recorrido de un tablero se adaptaron para ignorar
las áreas no jugables.
La primera estructura contiene la información del Tablero:

``` c
typedef struct
{
    char layout[5][5];  //El tablero en si
    int id;             //Código identificador del tablero
    int nivel;          //Cantidad de jugadas en el tablero
    int siguientes[9];  //Jugadas posibles para ese tablero
} table;
```
Una vez más, ya que los valores de las filas y las columnas se
mantienen constante durante todo el juego, vimos convenientes
definirlas como constantes:
**#define FILT 5
#define COLT 5**

*Estas no entran en conflicto con las globales del tetris ya que cada
juego se maneja en su propia librería y estas no están conectadas
entre sí.


###### Jugada:
En el tablero contamos con una matriz, sobre la cual se realizaran las
diferentes jugadas, las cuales contendrán las coordenadas sobre las
cuales se aplicara dicha jugada.
``` c
typedef struct
{
    int player;         //Que jugador realiza la jugada
    int i;              //Coordenada I del tablero
    int j;              //Coordenada J del tablero
    int valor;          //Valor de la jugada(no se implemento)
} jugada;
```

###### Juego:

Una vez definido el tablero y las jugadas, una de las primeras tareas
fue crear una función que transformara los input en las jugadas para
que estas pudieran ser plasmadas en el tablero.
Esta interacción entre el usuario y la consola se realiza con una
función que toma la tecla (numero) que presiona el usuario y lo
transforma en una jugada equivalente.

**jugada traducirJugada(int numero);**

De esta manera se logra ingresar al tablero una coordenada acorde a
lo que ingresa el usuario, la que a su vez es evaluada en otra
instancia para saber si esta es válida o se debe escoger otra jugada
(un espacio ya ocupado por otra ficha).
Una vez la jugada a sido realizada, es el turno del algoritmo de
realizar su propia jugada, para esto utiliza la función:

**jugada la2Jugada(table unTablero);**

Esta función a su vez hace uso de la función mejorMove la cual le
retornara un dato de tipo jugada que tras haber evaluado las
probabilidades de victoria/derrota en cada posible espacio libre,
devolviendo la que mejor valor contiene y a su vez evaluando si esta
jugada puede ser una victoria, en caso de victoria de la máquina,
esta será la escogida, en cambio si no puede asegurar una victoria

inmediata se asegurara de no obtener una derrota siguiente a su
jugada. En caso de que no haya ni victoria ni derrotas inmediatas el
algoritmo procederá a escoger una jugada que le dé la máxima
cantidad de victorias y a su vez la mínima cantidad de derrotas con
las funciones:

**int retornaMIN(table unTablero);
int retornaMAX(table unTablero);
int buscaMenorJugada(jugada arreglo[8], int validos);
int buscaMayorJugada(jugada arreglo[8], int validos);
int evaluaVictoria(table unTablero);**


###### Función de la jugada:
``` c
jugada la2jugada(table unTablero)
{
    jugada unaJugada;
    jugada otraJugada;
    int victoria=0;
    int derrota=0;
    unaJugada=mejorMove(unTablero);
    unTablero.layout[unaJugada.i] [unaJugada.j]=’2’;
    victoria=evaluaVictoria(unTablero);
    if(victoria!=-1)
    {
        otraJugada=peorMove(unTablero);
        unTablero.layout[otraJugada.i] [otraJugada.j]=’1’;
        derrota=evaluaVictoria(unTablero);
        if(derrota==1)
            unaJugada=otraJugada;
        else if(derrota!=1 &amp; &amp; derrota!=0)
            otraJugada=laJugada(unTablero);
    }

    return unaJugada;
}
```
De esta manera el juego continua hasta que se declara la victoria de
un de los jugadores o se llena el tablero en un empate.

Si bien el juego, a nuestro criterio necesita más desarrollo, que vamos a realizar a medida que transcurra el segundo cuatrimestre y logremos adquirir mayores herramientas, Podemos decir que aprendimos mucho de esta experiencia, tanto académicamente como interpersonalmente, nos pudimos dar cuenta lo que es afrontar un proyecto de manera colaborativa, a exponer nuestras ideas y escuchar la del otro, a involucrarnos y comprometernos con el proyecto. Construimos conocimientos que tal vez en la cursada no se logran afianzar.  
