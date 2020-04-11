#include "users.h"
#include "menu.h"

stUsuario inicUsuario()
{
    stUsuario nuevo;
    nuevo.anioNacimiento=0;
    nuevo.apeNom[0]='\0';
    nuevo.eliminado=1;
    nuevo.idUsuario=0;
    nuevo.nombreUsuario[0]='\0';
    nuevo.pais[0]='\0';
    nuevo.pass[0]='\0';

    return nuevo;
}



void escribirArchivoStart()
{
    stUsuario aux;
    FILE *buffArchivo=fopen(archiUsers,"wb");
    if(!buffArchivo)
        printf("\nE R R O R en la apertura del archivo\n");
    else
    {
        for(int i=0; i<MAXUSR; i++)
        {
            aux=cargarUsuariosAutomatico(aux);
            fwrite(&aux,sizeof(stUsuario),1,buffArchivo);
        }
        if(fclose(buffArchivo)==-1)
            printf("\nE R R O R\n");
    }
    creaAdmin();
}

void generaNombre(char nombre[])
{
    char nombres[][20] = {"Alan","Jacinto","Perror","Martinez","Alicia","Jesus","Mirta","Andrea","Josefina","Monica","Andres","Juan","Nicolas","Antonia","Juana","Noe","Antonio","Juano","Noelia","Azul","Julia","Paula","Bartolome","Julian","Pomponio","Belen","Juliana"};

    strcpy(nombre,nombres[rand()%27]);
}

void generaApellido(char apellido[])
{
    char apellidos[][40] = {"Martinez","Lopez","Sanchez","Gonzalez","Gomez","Fernandez","Moreno","Sanjurjo","Jimenez","Perez","Rodriguez","Navarro","Ruiz","Diaz","Serrano","Hernandez","Munioz","Saez","Romero","Rubio","Alfaro","Molina","Spinetta", "Cortez", "Gonzalez", "Andujar", "San Juan", "Bautista", "Anchorena", "Paso",
                            "Gaboto","Vega","Vargas","Lloret","Linares","Suarez","Sierra","Amenabar","Blanco","White","Black"
                           };

    strcpy(apellido,apellidos[rand()%40]);
}

void uneApellidoYNombre(char apellidoNombre[])
{
    apellidoNombre[0]='\0';
    char nombre[20];
    char apellido[20];
    generaNombre(nombre);
    generaApellido(apellido);
    strcat(apellidoNombre,apellido);
    strcat(apellidoNombre,", ");
    strcat(apellidoNombre,nombre);
}

void generaPais (char pais[])
{
    char paises[][20] = {"India","Rumania","Rusia","Colombia","China","Qatar","Turquia","Yugoslavia","Mexico","Japon","Chile","Nigeria","Irlanda","Taiwan","Tucuman","Argentina","Sudafrica","Bulgaria","Argentina","Sudafrica"};

    strcpy(pais,paises[rand()%20]);
}

void estadoDeUsuario(int eliminado)
{
    printf(" Estado: |%s|",(eliminado==1)? "ELIMINADO":"ACTIVO");
}

void muestraUnRegistro (stUsuario usr)
{
    printf("\n ID USUARIO........: %d", usr.idUsuario);
    printf("\n Apellido y Nombre.: %s",usr.apeNom);
    printf("\n A%co de Nacimiento.: %d",164,usr.anioNacimiento);
    printf("\n Pais..............: %s\n",usr.pais);
    printf("\n Nombre de Usuario.: %s",usr.nombreUsuario);
    printf("\n Password..........: %s \n",usr.pass);
    estadoDeUsuario(usr.eliminado);
    puts("\n-----------------------------------------------------");
}

void mostrarRegistros(char archivo[])
{
    stUsuario dato;
    FILE* bufferArchi= fopen(archivo,"rb");
    if(!bufferArchi)
        printf("E R R O R  en apertura de archivo\n");
    else
    {
        while(fread(&dato,sizeof(stUsuario),1,bufferArchi)>0)
        {
            muestraUnRegistro(dato);
        }
    }
}

void generaNombreDeUsuario(char usuario[],stUsuario aux)
{
    int i;
    for(i=0; aux.apeNom[i]!=','; i++)
    {
        usuario[i]=aux.apeNom[i];
    }
    usuario[0]=tolower(usuario[0]);
    usuario[i]='\0';


}
void generaPass(char pass[],stUsuario aux)
{
    //char* buffer = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    char buffer[20];
    sprintf(buffer, "%d", aux.anioNacimiento);                ///esta funcion sirve para pasar int a string
    strcpy(pass,aux.nombreUsuario);
    /*for(int i = 0; buffer[i]; i++)
    {
        buffer[i] = tolower(buffer[i]);
    }*/
    strcat(pass,buffer);
}

stUsuario cargarUsuariosAutomatico (stUsuario aux)
{
    aux.anioNacimiento=1979+rand()%(2001-1979);
    uneApellidoYNombre(aux.apeNom);
    aux.idUsuario=rand()%999;
    generaPais(aux.pais);
    generaNombreDeUsuario(aux.nombreUsuario,aux);
    aux.eliminado=0;
    generaPass(aux.pass,aux);

    return aux;
}

int cuentaRegistros(char archivo[],int sizEstructura)
{
    int cant=0;
    FILE* bufferArchi=fopen(archivo,"rb");
    if(!bufferArchi)
        printf("E R R O R  en ");
    else
    {
        fseek(bufferArchi,0,SEEK_END);
        cant=ftell(bufferArchi);
        cant=cant/sizeof(stUsuario);
    }
    return cant;
}

int agregarCelda(stCelda enJuego[],stUsuario usuario,int validos)
{
    enJuego[validos].usr=usuario;
    enJuego[validos].tablaScores=inicLista();
    //enJuego[validos].tablaScores->score.idScore=0;
    validos++;
    return validos;
}

int alta (stCelda enJuego[], stUsuario nuevo, stScores score, int validos)
{
    nodoListaScores* aux = crearNodo(score);
    int pos = buscaPosIdUsuario(enJuego,nuevo.idUsuario,validos);
    if(pos==-1)
    {
        validos=agregarCelda(enJuego,nuevo,validos);

        pos=validos-1;
    }
    /*if(!enJuego[pos].tablaScores){
            enJuego[pos].tablaScores->score.idScore=0;          ///SE ROMPE TODO (?
            }*/
    enJuego[pos].tablaScores=agregarEnOrden(enJuego[pos].tablaScores, aux);
    return validos;
}

int buscaPosIdUsuario(stCelda enJuego[],int idUsuario, int validos)
{
    int rta=-1;
    int i=0;
    while((i<validos)&&(rta==-1))
    {
        if(enJuego[i].usr.idUsuario==idUsuario)
        {
            rta=i;
        }
        i++;
    }
    return rta;
}

int archivoToEnJuego(stCelda enJuego[], int validos)
{
    FILE* bufferArchi=fopen(archiUsers, "rb");
    if(bufferArchi)
    {
        stUsuario datos;
        stUsuario nuevoUser;
        stScores scoreDeNuevo;
        while((fread(&datos,sizeof(stUsuario),1,bufferArchi)>0))
        {
            nuevoUser.idUsuario=datos.idUsuario;
            strcpy(nuevoUser.apeNom,datos.apeNom);
            scoreDeNuevo.idUsuario = datos.idUsuario;
            strcpy(nuevoUser.nombreUsuario,datos.nombreUsuario);
            strcpy(nuevoUser.pais,datos.pais);
            nuevoUser.anioNacimiento=datos.anioNacimiento;
            strcpy(nuevoUser.pass,datos.pass);
            fGetNow(scoreDeNuevo.fecha);
            validos = alta(enJuego,nuevoUser,scoreDeNuevo,validos);
        }
        fclose(bufferArchi);
    }
    return validos;
}

void tendraScore(nodoListaScores* Score)
{
    (Score->score.idScore>=0)? recorrerYmostrar(Score):printf("\tUsuario sin puntaje previo...\n");
}

void mostrarUnaCelda(stCelda unaCelda)
{
    printf("\n================ID %d================\n",unaCelda.usr.idUsuario);
    printf("\nNombre de usuario: %s", unaCelda.usr.nombreUsuario);
    printf("\nPartidas Jugadas:\t|%d|",cuentaScores(unaCelda.tablaScores));
    puts("\n\n========Listado de Scores:==========");
    //(enJuego[i].tablaScores->score.idScore>0)? recorrerYmostrar(enJuego[i].tablaScores):printf("\tUsuario sin puntaje previo...\n");
    tendraScore(unaCelda.tablaScores);
}

void mostrarUnaCeldaResumida(stCelda unaCelda)
{
    printf("\n================ID %d================\n",unaCelda.usr.idUsuario);
    printf("\nNombre de usuario: %s", unaCelda.usr.nombreUsuario);
    printf("\nPartidas Jugadas:\t|%d|",cuentaScores(unaCelda.tablaScores));
    puts("\n======================================");

    //tendraScore(unaCelda.tablaScores);
}

void mostrarEnJuego(stCelda enJuego[], int validos)
{
    printf("\nMostrando Usuarios Activos: \n");
    int i=0;
    while(i<validos)
    {
        if(enJuego[i].usr.eliminado!=0)
        {
            mostrarUnaCeldaResumida(enJuego[i]);
        }
        i++;
    }
}

void escribirArchivoScores(stCelda enJuego[], int validos)
{
    stScores aux;
    int idUser;
    int idScore=0;
    int maxScores;

    FILE *buffArchivo=fopen(archiScores,"wb");
    if(!buffArchivo)
        printf("\nE R R O R en la apertura del archivo\n");
    else
    {
        for(int i=0; i<validos; i++)
        {
            idUser=enJuego[i].usr.idUsuario;
            maxScores=rand()%MAXSCR;

            for(int j=0; j<maxScores; j++)
            {
                aux=generaScoresRandom(idUser,idScore);
                idScore++;
                fwrite(&aux,sizeof(stScores),1,buffArchivo);
            }
            idScore=0;
        }
        if(fclose(buffArchivo)==-1)
            printf("\nE R R O R\n");
    }


}

stScores generaScoresRandom(int idUsuario,int idScore)
{

    stScores aux;

    aux.idUsuario=idUsuario;
    aux.idScore=idScore+1;
    aux.puntos=1+(rand()%200);
    strcpy(aux.fecha,"Sin_Fecha");

    return aux;
}

stScores generaScores(int idUsuario,int puntos)
{

    stScores aux;
    char fecha[120];
    aux.idUsuario=idUsuario;
    aux.idScore=1+(rand()%999);
    aux.puntos=puntos;
    //strcpy(aux.fecha,"Sin_Fecha");
    fGetNow(fecha);
    strcpy(aux.fecha,fecha);

    return aux;
}

void mostrarRegistrosScores(char archivo[])
{
    stScores dato;
    FILE* bufferArchi= fopen(archivo,"rb");
    if(!bufferArchi)
        printf("E R R O R  en apertura de archivo\n");
    else
    {
        while(fread(&dato,sizeof(stScores),1,bufferArchi)>0)
        {
            muestraUnRegistroScores(dato);
        }
    }
}

void muestraUnRegistroScores (stScores score)
{

    printf("\n ID SCORE........: %d", score.idScore);
    printf("\n SCORE...........: %d",score.puntos);
    printf("\n Fecha Score.....: %s",score.fecha);
    puts("\n-----------------------------------------------------");
}

void archiScoreToCeldas(stCelda enJuego[],int validos)
{
    FILE* bufferArchi=fopen(archiScores, "rb");

    if(bufferArchi)
    {
        stScores datos;

        nodoListaScores* nuevoScore=inicLista();
        int pos;
        while((fread(&datos,sizeof(stScores),1,bufferArchi)>0))
        {

            pos=buscaPosIdUsuario(enJuego,datos.idUsuario,validos);
            nuevoScore=crearNodo(datos);
            enJuego[pos].tablaScores=agregarEnOrden(enJuego[pos].tablaScores,nuevoScore);
        }
        fclose(bufferArchi);
    }
    else
        perror("\nE R R O R: ");
}


void encriptaPass(char pass[])
{
    int i=0;
    int valor;
    char num[9];
    while(pass[i]!=13)
    {
        pass[i]=getch();
        if(pass[i]>32 && i<20)
        {
            if (pass[i] >= 48 && pass[i] <= 57)
            {
                valor = valor * 10 + pass[i] - '0';
                sprintf(num, "%d", valor);
                strcat(pass,num);
            }
            putchar('*');
            i++;
        }
        else if(pass[i]==8 && i>0)
        {
            putchar(8);
            putchar(' ');
            putchar(8);
            i--;
        }

    }

    pass[i]='\0';
}

int verificaUsuario(stCelda enJuego[],char nomUsuario[],int validos)
{
    int flag=-1;
    int i=0;
    char buffer[30];
    while(i<validos && flag==-1)
    {
        strcpy(buffer,enJuego[i].usr.nombreUsuario);
        if(strcmp(buffer,nomUsuario)==0)
            flag=i;
        i++;
    }
    return flag;
}

int verificaPass(stCelda enJuego[],char pass[],int validos)
{
    int flag=-1;
    int i=0;
    char buffer[30];
    while(i<validos && flag==-1)
    {
        strcpy(buffer,enJuego[i].usr.pass);
        if(strcmp(buffer,pass)==0)
            flag=i;
        i++;
    }
    return flag;
}

int comparaUsrPass(stCelda enJuego[],char pass[],char nomUsuario[],int validos)
{
    int flag=-1;
    int usr,clave;
    usr=verificaUsuario(enJuego,nomUsuario,validos);
    clave=verificaPass(enJuego,pass,validos);
    if(usr==clave)
        flag=usr;

    return flag;
}


stCelda login(stCelda enJuego[],int validos)
{
    stCelda usuarioEnJuego;
    int posUsuario=-1;
    int controlLogueo=0;
    int controlPass=0;
    char logueoPass[40];
    char logueoUser[40];
verifiUsuario:
    controlLogueo=0;

    printf("\nIngrese Usuario:\n");
    fflush(stdin);
    gets(logueoUser);
    controlLogueo=verificaUsuario(enJuego,logueoUser,validos);    ///controla que el user exista
    if(controlLogueo==-1)
    {
        printf("\nNombre de Usuario Incorrecto\n");

        goto verifiUsuario;
    }
    else
    {
verifiPass:
        controlPass=0;

        printf("\nIngrese Contrase%ca:\n",164);
        encriptaPass(logueoPass);
        fflush(stdin);
        //scanf("%s",logueoPass);
        controlPass=verificaPass(enJuego,logueoPass,validos);  ///controla que la pass exista
        if(controlPass==-1)
        {
            printf("\nContrase%ca Incorrecta",164);

            goto verifiPass;
        }
    }
    posUsuario=comparaUsrPass(enJuego,logueoPass,logueoUser,validos);

    if(posUsuario==-1)      ///user y pass del mismo jugador
    {
        printf("\nUsuario o contrase%ca Incorrectos",164);
        goto verifiUsuario;
    }
    cargando( );
    printf("\nLogueo con Exito\n");
    usuarioEnJuego=enJuego[posUsuario];

    return usuarioEnJuego;
}

int altaDeUsuario(stCelda enJuego[],int validos)  ///lista de jugadores
{
    stUsuario nuevoUsr=inicUsuario();
    int controlCopiaUser=0;
    char userGet[12];           ///toma el user para copiarlo en el struc


validoUsuario:
    printf("\nIngrese un nombre de Usuario(10 caracteres como maximo)\n");
    fflush(stdin);
    scanf("%s",userGet);
    controlCopiaUser=verificaUsuario(enJuego,userGet,validos);
    if(controlCopiaUser!=-1)
    {
        printf("\nNombre de Usuario en uso, Ingrese uno nuevo\n");
        goto validoUsuario;
    }
    if(strlen(userGet)>10)
    {
        printf("\nNombre de Usuario demasiado largo\n");
        goto validoUsuario;
    }

    strcpy(nuevoUsr.nombreUsuario,userGet);/////

    ///llegado aca hay un ingreso de usuario valido

    nuevoUsr=modificaPass(nuevoUsr);  ///funcion modularizada para ingreso de pass


    nuevoUsr.idUsuario=rand()%999;
    stScores score;

    for(int i=0; i<5; i++)
    {
        score=generaScoresRandom(nuevoUsr.idUsuario,i);
    }

    validos=alta(enJuego,nuevoUsr,score,validos);
///Inicia los scores en 0 para evitar conflicto con la impresion

    return validos;
}

void creaAdmin()
{
    stUsuario aux;
    FILE *buffArchivo=fopen(archiUsers,"ab");
    if(!buffArchivo)
        perror("\nE R R O R:");
    else
    {
        aux.anioNacimiento=1810;
        strcpy(aux.apeNom,"Perror, 404");
        aux.idUsuario=404;
        strcpy(aux.nombreUsuario,"admin404");
        strcpy(aux.pais,"Land Not Found");
        strcpy(aux.pass,"error404");
        fwrite(&aux,sizeof(stUsuario),1,buffArchivo);
    }
    if(fclose(buffArchivo)==-1)
        printf("\nE R R O R\n");
}

///-----------------------------------------------------------------------------------------------------------///

void eliminaCelda(stCelda enJuego[],int validos)
{

    char desicion;              ///eliminar o no eliminar : esa es la cuestion



noAlAdmin:
    mostrarEnJuego(enJuego,validos);
    int aux=-1;

    printf("\n Ingrese el ID del usuario a eliminar:\t");
    scanf("%d",&aux);
    if(aux==404)
    {
        puts("\nImposible Borrar al Admin\n");
        Sleep(1500);
        goto noAlAdmin;
    }

    aux=buscaPosIdUsuario(enJuego,aux,validos);   ///se busca la posicion del usuario a eliminar
    if (aux==-1)
    {
        puts("\nID no encontrado o Invalido\n");
        Sleep(1500);
        goto noAlAdmin;
    }
    system("cls");
    puts("\nATENCION ESTA SEGURO DE ELIMINAR A:\n");
    muestraUnRegistro(enJuego[aux].usr);
    printf("\n\n\t\tS / N \t");
    fflush(stdin);
    if(tolower(desicion=getch()=='s'))
    {
        enJuego[aux].usr.eliminado=0;                   ///eliminado = 0 (esta eliminado)
        puts("\n\n\t\tUSUARIO ELIMINADO");
    }
    else
        puts("\n\n\t\tMagnanimo.");

    Sleep(1000);
    puts("\n\n");
}

void modificarJugador(stCelda enJuego[],int validos)
{
    imprimirCabecera("MODIFICAR JUGADOR");

    char desicion='s';              ///eliminar o no eliminar : esa es la cuestion

noAlAdmin:

    mostrarEnJuego(enJuego,validos);
    int aux=-1;

    printf("\n Ingrese el ID del usuario a Modificar:\t");
    scanf("%d",&aux);
    if(aux==404)
    {
        puts("\nImposible Modificar al Admin\n");
        Sleep(1500);
        goto noAlAdmin;
    }
    ///asigna ID elegido al dummy
    aux=buscaPosIdUsuario(enJuego,aux,validos);   ///se busca la posicion del usuario a modificar
    if (aux==-1)
    {
        puts("\nID no encontrado o Invalido\n");
        Sleep(1500);
        goto noAlAdmin;
    }
    system("cls");
    do
    {

        enJuego[aux].usr=menuModificar(enJuego[aux].usr);
        printf("\n\n%cDesea modificar algun otro parametro?\tS/N",168);
        fflush(stdin);
        tolower(desicion=getch());
    }
    while(desicion=='s');

    Sleep(500);
    system("cls");
}

stUsuario modificaPass (stUsuario jugador)
{
    char passGet[10];
    char passConfirm[10];
validoPass:
    printf("\nIngrese la contrase%ca (max 10 caracteres)\n",164);
    fflush(stdin);
    encriptaPass(passGet);
    if(strlen(passGet)>10)
    {
        printf("\nLargo de la Contrase%ca Incorrecto",164);
        goto validoPass;
    }
    ///una vez saltado el problema del largo de la pass se va a la confirmacion
    else
    {
        printf("\nConfirme la contrase%ca\n",164);
        fflush(stdin);
        encriptaPass(passConfirm);
        if (strcmp(passGet,passConfirm)!=0)       ///confirmacion de igualdad entre pass y confirm
        {
            printf("\nContrase%ca Incorrecta,\n",164);
            goto validoPass;
        }
    }

    strcpy(jugador.pass,passGet);
    return jugador;
}

stUsuario menuModificar(stUsuario jugador)
{
    stUsuario aux;

    int op;
    do
    {
        system("cls");
        muestraUnRegistro(jugador);
        puts("\n");
        imprimirCabecera("MODIFICAR JUGADOR");
        printf("\n%cQue dato desea modificar?:\n\n",168);
        printf("1. A%co de nacimiento\n",164);
        printf("2. Pais\n");
        printf("3. Contrase%ca\n",164);
        printf("0. Salir\n");
        scanf("%d",&op);
        switch(op)
        {
        case 0:
            system("cls");
            break;
        case 1:
            printf("\nNuevo A%co:\t",164);
            scanf("%d",&jugador.anioNacimiento);
            system("cls");
            break;
        case 2:
            printf("\nNuevo Pais:\t");
            fflush(stdin);
            gets(aux.pais);
            strcpy(jugador.pais,aux.pais);
            system("cls");
            break;
        case 3:
            printf("\nNueva contrase%ca:\t",164);
            jugador=modificaPass(jugador);
            system("cls");
            break;
        default:
            printf("Opcion incorrecta\n");
        }
    }
    while(op != 0);

    return jugador;
}


void mostrarTopTen(stScores topTen[],stCelda enJuego[],int validos)
{
    int i;
    stUsuario dummy;
    puts("\n\tLOS 10 MEJORES JUGADORES\n");
    puts("\n\tPUESTO\tSCORE\tNOMBRE\n");
    for(i=0; i<10; i++)
    {

        dummy=enJuego[buscaPosIdUsuario(enJuego,topTen[i].idUsuario,validos)].usr;
        printf("\t%d\t%d\t%s\n",i+1,topTen[i].puntos,dummy.apeNom);
    }
    puts("\n");
}

void topDiez(stCelda enJuego[],int validos)
{

    int maxScores=0;
    maxScores=cuentaTodosScores(enJuego,validos);
    stScores todosScores[maxScores];                    ///Array de tamaño de todos los scores

    levantaTodosScores(enJuego,validos,todosScores);
    ordenacionSeleccion(todosScores,maxScores);
    invertirArreglo(todosScores,maxScores);

    mostrarTopTen(todosScores,enJuego,maxScores);
}

int cuentaTodosScores(stCelda enJuego[], int validos)
{
    int suma=0;
    for(int i=0; i<validos; i++)
    {
        suma=suma+cuentaScores(enJuego[i].tablaScores);
    }

    return suma;
}

void levantaTodosScores(stCelda enJuego[], int validos, stScores todosScores[])
{

    int j=0;
    nodoListaScores* aux;
    aux=inicLista();

    for(int i=0; i<validos; i++)
    {
        aux=enJuego[i].tablaScores;
        while(aux)
        {
            todosScores[j]=aux->score;
            aux=aux->sig;
            j++;
        }
    }
}

void persisteScores(stCelda enJuego[],int validos)
{
    FILE* bufferArchi=(archiScores,"wb");
    stScores dato;
    if(!bufferArchi)
        perror("\nERROR:");

    else
    {
        nodoListaScores* aux;
        aux=inicLista();

        for(int i=0; i<validos; i++)
        {
            aux=enJuego[i].tablaScores;
            while(aux)
            {
                dato=aux->score;
                fwrite(&dato,sizeof(stScores),1,bufferArchi);
                aux=aux->sig;
            }
        }
    }
    if(fclose(bufferArchi)==-1)
        perror("ERROR");
}
