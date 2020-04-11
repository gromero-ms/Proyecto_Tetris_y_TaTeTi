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
```
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
```
#define FILAT 24 
#define COLT 12
```

###### Tablero Buffer: 
Al trabajar con un lenguaje como el C necesitamos generar la menos cantidad de limpiezas de pantalla system(“cls”) y re impresiones para evitar el parpadeo al momento de imprimir algo en consola. Por lo tanto, creamos una matriz adicional de tipo Char para almacenar las piezas, que al momento de llegar a la última fila (el final del tablero) queden quietas y pasan del tablero principal al Tablero Buffer
**char tableroBuffer[FILAT][COLT]**;

###### Juego: 
Una vez definidas las piezas y los tableros se procede a desarrollar el juego. Se crea una función la cual mediante la función srand() selecciona de manera random una Pieza y la carga en la pieza que pasara a ser Pieza enJuego. Esta pieza pasara a ser la que se imprima dentro de las matrices tablero. 
Toda esta interacción entre el usuario y la consola se realiza con una función que toma la tecla (carácter) que presiona el usuario y modifica una de las las variables dentro de la función que imprime la pieza en el tablero principal.
```
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
```
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

###### Conclusiones

Si bien el juego, a nuestro criterio necesita más desarrollo, que vamos a realizar a medida que transcurra el segundo cuatrimestre y logremos adquirir mayores herramientas, Podemos decir que aprendimos mucho de esta experiencia, tanto académicamente como interpersonalmente, nos pudimos dar cuenta lo que es afrontar un proyecto de manera colaborativa, a exponer nuestras ideas y escuchar la del otro, a involucrarnos y comprometernos con el proyecto. Construimos conocimientos que tal vez en la cursada no se logran afianzar.  
