#include "lista.h"


#define archiUsers "usuarios.dat"
#define archiScores "scores.dat"
#define MAXUSR 10                          ///Modifica la cantidad de usuarios que se generan en el archivo
#define MAXSCR 10                         ///Modifica la cantidad maxima de scores generados por usuario

typedef struct
{
    int idUsuario;          ///ID del usuario
    char nombreUsuario[30]; ///Nombre de usuario
    char apeNom[40];        ///Apellido y nombre del usuario
    char pass[40];          ///Contraseña
    int anioNacimiento;     ///Anio Nacimiento
    char pais[20];          ///Pais
    int eliminado;          ///Indica 1 o 0 si el cliente fue eliminado
} stUsuario;

typedef struct
{
    stUsuario usr;
    nodoListaScores* tablaScores;
} stCelda;

///----------------------------------------------Funciones--Users------------------------------------------------------------------///

stUsuario inicUsuario();                            ///inicia el user en neutro
void escribirArchivoStart();                        ///guarda en archivo usuarios de manera automatica
stUsuario cargarUsuariosAutomatico (stUsuario aux); ///crea usuario automaticamente
void creaAdmin();                                   ///crea la cuenta de Administrador
void generaNombre(char nombre[]);                   ///genera un nombre extraido de un almacen de nombres
void generaApellido(char apellido[]);               ///genera un apellido extraido de un almacen de apellidos
void uneApellidoYNombre(char apellidoNombre[]);     ///concatena apellido y nombre
void generaPais (char pais[]);                      ///genera un pais extraido de un almacen de paises
void generaNombreDeUsuario(char usuario[],stUsuario aux);   ///genera nombre de usuario
void muestraUnRegistro (stUsuario usr);             ///muestra un registro de tipo usuario
void estadoDeUsuario(int eliminado);                ///muestra el estado del usuario ELIMINADO O ACTIVO
void mostrarRegistros(char archivo[]);              ///muestra el archivo
void generaPass(char pass[],stUsuario aux);         ///genera un pass para los usuario automaticos
int cuentaRegistros(char archivo[],int sizEstructura);  ///cuenta los registros del archivo

int agregarCelda(stCelda enJuego[],stUsuario usuario,int validos);          ///agrega una nueva celda en el arreglo
int alta(stCelda enJuego[], stUsuario nuevo, stScores score, int validos);  ///agrega en la lista de scores del user
int buscaPosIdUsuario(stCelda enJuego[],int idUsuario, int validos);        ///busca la posicion del user en base al ID
int archivoToEnJuego(stCelda enJuego[], int validos);                       ///bajha el archivo de users al arreglo
void mostrarUnaCelda(stCelda unaCelda);             ///Muestra la celda completa con todos los scores(lista)
void mostrarUnaCeldaResumida(stCelda unaCelda);     ///Muestra la celda resumida sin todos los scores
void mostrarEnJuego(stCelda enJuego[], int validos);///Muestra users no dados de baja
void tendraScore(nodoListaScores* Score);           ///Averigua si el user tiene scores registrados

void escribirArchivoScores(stCelda enJuego[], int validos);    ///Guarda en archivo de Scores
stScores generaScores(int idUsuario, int puntos);              ///Genera score para almacenar en el usuario
stScores generaScoresRandom(int idUsuario,int idScore);        ///Genera scores para el archi de scores
void mostrarRegistrosScores(char archivo[]);                   ///Mostrar Registros de Scores
void muestraUnRegistroScores (stScores score);                 ///Muestra 1 score (aux de funcion anterior)
void archiScoreToCeldas(stCelda enJuego[],int validos);        ///Extrae los scores del archivo de scores y los asigna a los jugadores en Linea


void encriptaPass(char pass[]);                                                      ///Enmascara los caracteres al ingresar la clave
int verificaUsuario(stCelda enJuego[],char nomUsuario[],int validos);               ///Verifica si existe el user y su posicion(sino retorna -1)
int verificaPass(stCelda enJuego[],char pass[],int validos);                       ///Verifica si existe la pass y su posicion(sino retorna -1)
int comparaUsrPass(stCelda enJuego[],char pass[],char nomUsuario[],int validos);  ///Verifica que el pass pertenezca a dicho user
stCelda login(stCelda enJuego[],int validos);                                    ///funcion para el login del usuario a jugar
int altaDeUsuario(stCelda enJuego[],int validos);                               ///funcion para dar de alta un nuevo user


void eliminaCelda(stCelda enJuego[],int validos);                       ///Da de baja el user(no elimina el registro pero lo da de baja)
void modificarJugador(stCelda enJuego[],int validos);
stUsuario menuModificar(stUsuario jugador);                             ///Modifica un Registro de User
stUsuario modificaPass (stUsuario jugador);                             ///Modifica la pass (aux de anterior)
void topDiez(stCelda enJuego[],int validos);                            ///Genera el TOP 10 Scores
void mostrarTopTen(stScores topTen[],stCelda enJuego[],int validos);    ///Muestra el TOP 10

int cuentaTodosScores(stCelda enJuego[], int validos);                      ///cuenta cantidad de scores en el Arr de Lista
void levantaTodosScores(stCelda enJuego[], int validos, stScores todosScores[]); ///Arr de todos scores

void persisteScores(stCelda enJuego[],int validos);                     ///persiste los scores
