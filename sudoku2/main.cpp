#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int tamAlias = 5;
const int tamNombre = 20;
const int tamHistorial = 3;
const int cantJugadores = 10;


struct Jugador{
    char alias[tamAlias];
    char nombre[tamNombre];
    char apellido[tamNombre];
    int edad;
    int puntos;
    bool activo;
    int historial[tamHistorial];

};

// DECLARACION DE FUNCIONES //

///Lee lo ingresado en consola hasta el tamaño deseado, luego sigue leyendo para limpiar el buffer;
void leer_linea(char arr[], int tam);

///Crea un nuevo jugador
void registro_jugador(Jugador jugadores[]);

///Recibe array de jugadores y un alias y chequea si ya existe ese alias
bool alias_existente(Jugador jugadores[], char alias[]);

///Recibe array jugadores e imprime sus datos
void listado_jugadores(Jugador jugadores[]);

///Modifica un jugador
void modificar_jugador(Jugador jugadores[]);

///Imprime los datos de registro de un jugador especifico
void imprimir_datos(Jugador jugadores[]);

///Elimina un jugador a partir de su alias
void eliminar_jugador(Jugador jugadores[]);


int main()
{

    Jugador jugadores[cantJugadores];
    char leo[2];

    //Recorre el arreglo de jugadores y setea que estan inactivos
    for(int i=0 ; i<10 ; i++){
        jugadores[i].activo = false;
    }

    do{
        printf("\nMENU: \n(R)egistrar \n(L)istado \n(J)ugar \n(D)atos \n(M)odificar \n(E)liminar \n(S)alir \n");
        leer_linea(leo, 2);

        if(strcmp(leo,"R")==0 or strcmp(leo, "r")==0)
            registro_jugador(jugadores);
        else if(strcmp(leo,"L")==0 or strcmp(leo, "l")==0)
            listado_jugadores(jugadores);
        else if(strcmp(leo,"J")==0 or strcmp(leo, "j")==0)
            printf("J");
        else if(strcmp(leo,"D")==0 or strcmp(leo, "d")==0)
            imprimir_datos(jugadores);
        else if(strcmp(leo,"M")==0 or strcmp(leo, "m")==0)
            modificar_jugador(jugadores);
        else if(strcmp(leo,"E")==0 or strcmp(leo, "e")==0)
            eliminar_jugador(jugadores);
        else if(strcmp(leo,"S")!=0 and strcmp(leo, "s")!=0)
            printf("Esta opcion no es valida");

    }while(strcmp(leo,"S")!=0 and strcmp(leo, "s")!=0);

    return 0;
}



// DEFINICION DE FUNCIONES //

///Lee lo ingresado en consola hasta el tamaño deseado, luego sigue leyendo para limpiar el buffer;
void leer_linea(char arr[],int tam){
    int pos=-1;
    do{
        if(pos<tam-1)
            pos++;
        arr[pos]=getchar();
    }while(arr[pos]!='\n');
    arr[pos]='\0';
}


///Crea un nuevo jugador
void registro_jugador(Jugador jugadores[]){

    int pos = 0;
    bool disponible = false, aliasDisponible;
    char alias[tamAlias];

    //Recorre el array de jugadores buscando el primer lugar disponible
    do{
        if(jugadores[pos].activo == false) {
            disponible = true;
        }
        pos++;
    }while(disponible == false and pos<cantJugadores);

    //Pide los datos y los almacena en el array jugadores
    if(disponible){
        printf("Ingresa los datos del jugador");
        do{
            printf("\nAlias: ");
            leer_linea(alias, tamAlias);
            aliasDisponible = alias_existente(jugadores, alias);
            if(aliasDisponible) {
                printf("No podes usar este alias");
            }else{
                strcpy(jugadores[pos-1].alias, alias);
            }
        }while(aliasDisponible);
        printf("Nombre: ");
        leer_linea(jugadores[pos-1].nombre, tamNombre);
        printf("Apellido: ");
        leer_linea(jugadores[pos-1].apellido, tamNombre);
        printf("Edad: ");
        scanf("%d", &jugadores[pos-1].edad);
        getchar();
        printf("Puntos: ");
        scanf("%d", &jugadores[pos-1].puntos);
        getchar();
        //jugadores[pos-1].puntos = 0;
        jugadores[pos-1].activo = true;

    } else {
        printf("No hay espacio para registrar jugadores");
    }

}


///Recibe array de jugadores y un alias y chequea si ya existe ese alias
bool alias_existente(Jugador jugadores[], char alias[]){

    bool existeAlias = false;
    int pos = 0;

    do{
        if(strcmp(alias, jugadores[pos].alias)==0){
            existeAlias = true;
        }
        pos++;
    }while(existeAlias == false and pos<cantJugadores);

    return existeAlias;
}


///Recibe array jugadores e imprime sus datos
void listado_jugadores(Jugador jugadores[]){

    int pos, pos2, valorMayor = 0, posValorMayor, mayorAnterior;
    bool existenJugadores = false;
    Jugador jugadoresOrdenados[cantJugadores];

    //Recorre el arreglo de jugadores ordenados y setea que estan inactivos
    for(int i=0 ; i<10 ; i++){
        jugadoresOrdenados[i].activo = false;
    }


    //Itera sobre array jugadoresOrdenados
    for(pos=0 ; pos<cantJugadores ; pos++){
        //Itera sobre array jugadores
        for(pos2=0 ; pos2<cantJugadores ; pos2++){
            if(jugadores[pos2].activo){
                if(pos==0){
                    if(jugadores[pos2].puntos > valorMayor){
                        valorMayor = jugadores[pos2].puntos;
                        posValorMayor = pos2;
                    }
                } else {
                    if(jugadores[pos2].puntos > valorMayor && jugadores[pos2].puntos < mayorAnterior){
                        valorMayor = jugadores[pos2].puntos;
                        posValorMayor = pos2;
                    }
                }
                existenJugadores = true;
            }
        }
        mayorAnterior = valorMayor;
        valorMayor = 0;
        jugadoresOrdenados[pos]=jugadores[posValorMayor];
    }

    if(!existenJugadores){
        printf("\nNo existen jugadores para imprimir");
    } else {
        for(int i=0 ; i<cantJugadores ; i++){
            if(jugadoresOrdenados[i].activo){
                printf("\nAlias: %s", jugadoresOrdenados[i].alias);
                printf("\nPuntos: %d", jugadoresOrdenados[i].puntos);
            }
        }
    }

}


///Recibe array de jugadores y un alias y devuelve en que posicion esta ese jugador, o -1 si no existe
int encuentra_jugador(Jugador jugadores[], char alias[]){

    int posicion = -1, pos = 0;
    bool aliasExistente;

    do{
        if(strcmp(alias, jugadores[pos].alias)==0){
            aliasExistente = true;
            posicion = pos;
        }
        pos++;
    }while(aliasExistente == false and pos<cantJugadores);

    return posicion;
}


///Modifica un jugador
void modificar_jugador(Jugador jugadores[]){

    char alias[tamAlias], leo[2];
    int posJugador;

    printf("Ingresa el usuario: ");
    leer_linea(alias, tamAlias);
    posJugador = encuentra_jugador(jugadores, alias);

    if(posJugador != -1){
        printf("Que deseas modificar?");

        do{
            printf("\n(N)ombre \n(A)pellido \n(E)dad \n(V)olver al menu\n");
            leer_linea(leo, 2);

            if(strcmp(leo,"n")==0 or strcmp(leo, "N")==0){
                printf("Nombre: ");
                leer_linea(jugadores[posJugador].nombre, tamNombre);
            } else if(strcmp(leo,"a")==0 or strcmp(leo, "A")==0){
                printf("Apellido: ");
                leer_linea(jugadores[posJugador].apellido, tamNombre);
            } else if(strcmp(leo,"e")==0 or strcmp(leo, "E")==0){
                printf("Edad: \n");
                scanf("%d", &jugadores[posJugador].edad);
                getchar();
            } else if(strcmp(leo,"v")!=0 and strcmp(leo, "V")!=0){
                printf("Esta opcion no es valida");
            }

        }while(strcmp(leo,"V")!=0 and strcmp(leo, "v")!=0);

    }else{
        printf("Este jugador no existe\n");
    }

}


///Imprime los datos de registro de un jugador especifico
void imprimir_datos(Jugador jugadores[]){

    char alias[tamAlias];
    int posJugador;

    printf("Ingresa el usuario: ");
    leer_linea(alias, tamAlias);
    posJugador = encuentra_jugador(jugadores, alias);

    if(posJugador != -1) {

        printf("\nAlias: %s", jugadores[posJugador].alias);
        printf("\nNombre: %s", jugadores[posJugador].nombre);
        printf("\nApellido: %s", jugadores[posJugador].apellido);
        printf("\nEdad %d", jugadores[posJugador].edad);
        printf("\nPuntaje total: %d \n", jugadores[posJugador].puntos);

    } else {
        printf("Este jugador no existe\n");
    }

}


///Elimina un jugador a partir de su alias
void eliminar_jugador(Jugador jugadores[]){

    char alias[tamAlias];
    int posJugador;

    printf("Ingresa el usuario: ");
    leer_linea(alias, tamAlias);
    posJugador = encuentra_jugador(jugadores, alias);

    if(posJugador != -1) {

        jugadores[posJugador].activo = false;

    } else {
        printf("Este jugador no existe\n");
    }

}











