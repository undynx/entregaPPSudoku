#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int tamAlias = 5;
const int tamNombre = 20;
const int tamHistorial = 3;
const int cantJugadores = 10;
const int tamSudoku = 9;


struct Jugador{
    char alias[tamAlias];
    char nombre[tamNombre];
    char apellido[tamNombre];
    int edad;
    int puntos;
    bool activo;
    int historial[tamHistorial];

};

//////////////////////////////

// DECLARACION DE FUNCIONES //

///Lee lo ingresado en consola hasta el tamaño deseado, luego sigue leyendo para limpiar el buffer;
void leer_linea(char arr[], int tam);

///Crea un nuevo jugador
void registro_jugador(Jugador jugadores[], int &cantJugadoresActivos);

///Recibe array de jugadores y un alias y chequea si ya existe ese alias
bool alias_existente(Jugador jugadores[], char alias[]);

///Recibe array jugadores e imprime sus datos
void listado_jugadores(Jugador jugadores[], int cantJugadoresActivos);

///Modifica un jugador
void modificar_jugador(Jugador jugadores[]);

///Imprime los datos de registro de un jugador especifico
void imprimir_datos(Jugador jugadores[]);

///Elimina un jugador a partir de su alias
void eliminar_jugador(Jugador jugadores[], int &cantJugadoresActivos);

///Permite al jugador jugar
void jugar(Jugador jugadores[]);

///Busca un valor random del sudoku que tenga 0
void generar_ayuda(int sudoku[][tamSudoku]);

//A partir de aquí están las funciones de la primera entrega

///Inicializa el sudoku
void inicializar_sudoku(int sudoku[][tamSudoku]);

///Imprimi tablero de Sudoku
void imprimir_sudoku(int sudoku[][tamSudoku]);

///Devuelve un Numero random en base a rango dado
int random_numbers(int minNum, int maxNum);

///Mover randomicamente las Columnas
void move_random_column(int sudoku[][tamSudoku], int pos1);

///Mover randomicamente las Filas
void move_random_row(int sudoku[][tamSudoku], int pos2);

/// Mover randomicamente las matrices de 3x9
void move_random_matriz(int sudoku[][tamSudoku], int pos2);

///Mostrar la cantidad de elementos ingresada
void show_elements(int sudoku[][tamSudoku], int cant_elem);

///Generar un tablero de Sudoku valid
void generar_sudoku_valido(int sudoku[][tamSudoku], int cant_elem);

///Validar que el candidato no esta en la Fila & Columna
bool es_candidato2(int sudoku[][tamSudoku], int num, int fila, int columna);

///Validar que el candidato no esta en el Area
bool validar_area(int sudoku[][tamSudoku], int num, int fila, int columna);

///Lista de Candidatos
void crear_candidatos(int sudoku[][tamSudoku], int fila, int columna, bool candidatos[tamSudoku]);

///Devuelve true o false si el tablero es valido
bool sudoku_valido(int sudoku[][tamSudoku]);

///Devuelve true si el trablero esta resuelto en su completitud
bool sudoku_resuelto(int sudoku[][tamSudoku]);

void funcion_mentira(Jugador jugadores[]);


/////////////////////////////

int main()
{
    Jugador jugadores[cantJugadores];
    char leo[2];
    int cantJugadoresActivos = 0;

    //Recorre el arreglo de jugadores y setea que estan inactivos
    for(int i=0 ; i<10 ; i++){
        jugadores[i].activo = false;
    }

    /*jugadores[0].activo = true;
    strcpy(jugadores[0].alias, "mei");
    strcpy(jugadores[0].nombre, "Maite");
    strcpy(jugadores[0].apellido, "Martinez");
    jugadores[0].edad = 23;
    jugadores[0].puntos = 10;
    cantJugadoresActivos ++;*/


    do{
        printf("MENU: \n(R)egistrar \n(L)istado \n(J)ugar \n(D)atos \n(M)odificar \n(E)liminar \n(S)alir \n");
        leer_linea(leo, 2);

        if(strcmp(leo,"R")==0 or strcmp(leo, "r")==0)
            registro_jugador(jugadores, cantJugadoresActivos);

        else if(strcmp(leo,"L")==0 or strcmp(leo, "l")==0)
            //listado_jugadores(jugadores, cantJugadoresActivos);
            funcion_mentira(jugadores);

        else if(strcmp(leo,"J")==0 or strcmp(leo, "j")==0)
            if(cantJugadoresActivos>0){
                jugar(jugadores);
            }else{
                printf("No existen jugadores registrados para jugar\n");
            }

        else if(strcmp(leo,"D")==0 or strcmp(leo, "d")==0)
            imprimir_datos(jugadores);

        else if(strcmp(leo,"M")==0 or strcmp(leo, "m")==0)
            modificar_jugador(jugadores);

        else if(strcmp(leo,"E")==0 or strcmp(leo, "e")==0)
            eliminar_jugador(jugadores, cantJugadoresActivos);

        else if(strcmp(leo,"S")!=0 and strcmp(leo, "s")!=0)
            printf("Esta opcion no es valida");

    }while(strcmp(leo,"S")!=0 and strcmp(leo, "s")!=0);

    return 0;
}

/////////////////////////////

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
void registro_jugador(Jugador jugadores[], int &cantJugadoresActivos){

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
                printf("No podes usar este alias\n");
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
        cantJugadoresActivos++;

    } else {
        printf("No hay espacio para registrar jugadores\n");
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

///
void funcion_mentira(Jugador jugadores[]){

    for(int posJugador = 0; posJugador < 9 ; posJugador++){
        printf("\nAlias: %s", jugadores[posJugador].alias);
        printf("\nNombre: %s", jugadores[posJugador].nombre);
        printf("\nApellido: %s", jugadores[posJugador].apellido);
        printf("\nEdad %d", jugadores[posJugador].edad);
        printf("\nPuntaje total: %d \n", jugadores[posJugador].puntos);
        printf("\nEsta activo? %d \n", jugadores[posJugador].activo);
    }

}


///Recibe array jugadores e imprime sus datos
void listado_jugadores(Jugador jugadores[], int cantJugadoresActivos){

    int pos, pos2, valorMayor = 0, posValorMayor, mayorAnterior;
    bool existenJugadores = false;
    Jugador jugadoresOrdenados[cantJugadores];

    //Recorre el arreglo de jugadores ordenados y setea que estan inactivos
    for(int i=0 ; i<10 ; i++){
        jugadoresOrdenados[i].activo = false;
    }

    //Itera sobre array jugadoresOrdenados
    for(pos=0 ; pos<cantJugadoresActivos ; pos++){
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
        printf("\nNo existen jugadores para imprimir\n");
    } else {
        for(int i=0 ; i<cantJugadores ; i++){
            if(jugadoresOrdenados[i].activo){
                printf("\nAlias: %s", jugadoresOrdenados[i].alias);
                printf("\nPuntos: %d \n", jugadoresOrdenados[i].puntos);
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
            if(jugadores[pos].activo){
                aliasExistente = true;
                posicion = pos;
            }
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
                printf("Esta opcion no es valida\n");
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

    if(posJugador != -1 && jugadores[posJugador].activo == true) {

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
void eliminar_jugador(Jugador jugadores[], int &cantJugadoresActivos){

    char alias[tamAlias];
    int posJugador;

    printf("Ingresa el usuario: ");
    leer_linea(alias, tamAlias);
    posJugador = encuentra_jugador(jugadores, alias);

    if(posJugador != -1) {

        jugadores[posJugador].activo = false;
        jugadores[posJugador].puntos = 0;
        cantJugadoresActivos--;

    } else {
        printf("Este jugador no existe\n");
    }

}

///Permite al jugador jugar
void jugar(Jugador jugadores[]){

    char leo[2], aliasJugador[tamAlias];
    int puntosAsignar=0, numMostrar, posJugador = -1, sudoku[tamSudoku][tamSudoku], filaIngresar, colIngresar, numIngresar;

    //Encuentra la posicion del jugador
    do{
        printf("Ingresa un alias registrado: ");
        leer_linea(aliasJugador, tamAlias);
        printf("%s\n", aliasJugador);
        posJugador = encuentra_jugador(jugadores, aliasJugador);
        printf("%d", posJugador);
    }while(posJugador == -1);

    //Elige el nivel del juego
    do{
        printf("Que nivel deseas jugar? \n(F)acil \n(N)ormal \n(D)ificil \n");
        leer_linea(leo, 2);

        if(strcmp(leo, "F")==0 or strcmp(leo, "f")==0){
            puntosAsignar = 21;
            numMostrar = 60;
        } else if(strcmp(leo, "N")==0 or strcmp(leo, "n")==0){
            puntosAsignar = 41;
            numMostrar = 40;
        }else if(strcmp(leo, "d")==0 or strcmp(leo, "D")==0){
            puntosAsignar = 61;
            numMostrar = 80;
        } else {
            printf("Esta opcion no es valida\n");
        }
    }while(strcmp(leo, "F")!=0 and strcmp(leo, "f")!=0 and strcmp(leo, "N")!=0 and strcmp(leo, "n")!=0 and strcmp(leo, "d")!=0 and strcmp(leo, "D")!=0);

    //Genera un sudoku nuevo
    inicializar_sudoku(sudoku);
    generar_sudoku_valido(sudoku, numMostrar);
    imprimir_sudoku(sudoku);

    do{
        printf("Si queres rendirte ingresa -1, si necesitas ayuda ingresa -2\n");
        //Valida que el numero este entre 1 y 9
        do{
            printf("Elegi el numero: ");
            scanf("%d", &numIngresar);
            getchar();
        }while((numIngresar < 1 || numIngresar > 9) && numIngresar != -1 && numIngresar != -2);

        if(numIngresar == -2){
            generar_ayuda(sudoku);

        } else if(numIngresar != -1){
            //Valida que el numero este entre 1 y 9
            do{
                printf("Elegi la fila: ");
                scanf("%d", &filaIngresar);
                getchar();
            }while(filaIngresar < 1 || filaIngresar > 9);
            filaIngresar --;

            //Valida que el numero este entre 1 y 9
            do{
                printf("Elegi la columna: ");
                scanf("%d", &colIngresar);
                getchar();
            }while(colIngresar < 1 || colIngresar > 9);
            colIngresar --;

            if(es_candidato2(sudoku, numIngresar, filaIngresar, colIngresar)){
                sudoku[filaIngresar][colIngresar] = numIngresar;
                imprimir_sudoku(sudoku);
            } else {
                printf("Este numero no es valido para esta celda\n");
            }

        }else{
            printf("Te rendiste! :( \n");
        }

    }while(!sudoku_resuelto(sudoku) && sudoku_valido(sudoku) && numIngresar != -1);

    if(numIngresar != -1){
        printf("FELICIDADES! Ganaste\n\n");
        jugadores[posJugador].puntos += puntosAsignar;
    }
}


///Busca un valor random del sudoku que tenga 0
void generar_ayuda(int sudoku[][tamSudoku]){

    int fila, columna, pos;
    bool candidatos[tamSudoku];

    do{
        fila = random_numbers(0, 8);
        columna = random_numbers(0, 8);
    }while(sudoku[fila][columna] != 0);

    crear_candidatos(sudoku, fila, columna, candidatos);

    printf("Para la fila %d y columna %d, el/los candidato(s) son: \n", fila+1, columna+1);
    for (pos = 0; pos < tamSudoku; pos++){
        if(candidatos[pos] == true){
            if(pos == 8){
                printf("%d ", pos+1);
            } else {
                printf("%d // ", pos+1);
            }
        }
    }
    printf("\n");
}

/////////////////////////////
//A partir de aquí están las funciones correspondientes
//a la primer entrega (jugabilidad)

///Inicializa el sudoku
void inicializar_sudoku(int sudoku[][tamSudoku])
{
    int pos1, pos2;

    // Inicializar la matriz del Sudoku con 0
    for (pos1 = 0; pos1 < tamSudoku; pos1++)
    {
        for (pos2 = 0; pos2 < tamSudoku; pos2++)
        {
            sudoku[pos1][pos2] = 0;
        }
    }
}

///Imprimi tablero de Sudoku
void imprimir_sudoku(int sudoku[][tamSudoku])
{
    int pos1, pos2;

    printf("\n");

    for (pos2 = 0; pos2 < tamSudoku; pos2++)
    {
        printf("++++");

        if (pos2 == 2 || pos2 == 5)
        {
            printf("+");
        }
    }
    printf("+\n");

    for (pos1 = 0; pos1 < tamSudoku; pos1++)
    {
        for (pos2 = 0; pos2 < tamSudoku; pos2++)
        {
            printf("| %d ", sudoku[pos1][pos2]);

            if (pos2 == 2 || pos2 == 5)
            {
                printf("|");
            }
        }

        printf("|\n");
        if (pos1 == 2 || pos1 == 5)
        {

            for (pos2 = 0; pos2 < tamSudoku; pos2++)
            {
                printf("++++");

                if (pos2 == 2 || pos2 == 5)
                {
                    printf("+");
                }
            }
            printf("+\n");
        }
    }

    for (pos2 = 0; pos2 < tamSudoku; pos2++)
    {
        printf("++++");

        if (pos2 == 2 || pos2 == 5)
        {
            printf("+");
        }
    }
    printf("+\n\n");
}


///Devuelve un Numero random en base a rango dado
int random_numbers(int minNum, int maxNum)
{
    int randNumber;

    // Genero un numero Random en base a un rango dado
    randNumber = rand() % maxNum;

    while (randNumber < minNum)
    {
        randNumber = rand() % maxNum;
    }
    return randNumber;
}

///Mover randomicamente las Columnas
void move_random_column(int sudoku[][tamSudoku], int pos1)
{
    int pos, aux, randNumber1, randNumber2, contCambios, rangoA = 0, rangoB = 2;

    // Muevo randomicamente las columnas, lo hago random & 3 veces
    for (pos = 0; pos < 3; pos++)
    {
        contCambios = 0;
        do
        {
            randNumber1 = random_numbers(rangoA, rangoB + 1);
            randNumber2 = random_numbers(rangoA, rangoB + 1);

            do
            {
                randNumber2 = random_numbers(rangoA, rangoB + 1);
            } while (randNumber1 == randNumber2);

            for (pos1 = 0; pos1 < tamSudoku; pos1++)
            {
                aux = sudoku[pos1][randNumber1];
                sudoku[pos1][randNumber1] = sudoku[pos1][randNumber2];
                sudoku[pos1][randNumber2] = aux;
            }
            contCambios++;
        } while (contCambios < 3);

        rangoA = rangoA + 3;
        rangoB = rangoB + 3;
    }
}

///Mover randomicamente las Filas
void move_random_row(int sudoku[][tamSudoku], int pos2)
{
    int pos, aux, randNumber1, randNumber2, contCambios, rangoA = 0, rangoB = 2;

    // Muevo randomicamente las filas
    for (pos = 0; pos < 3; pos++)
    {
        contCambios = 0;
        do
        {
            randNumber1 = random_numbers(rangoA, rangoB + 1);
            randNumber2 = random_numbers(rangoA, rangoB + 1);

            do
            {
                randNumber2 = random_numbers(rangoA, rangoB + 1);
            } while (randNumber1 == randNumber2);

            for (pos2 = 0; pos2 < tamSudoku; pos2++)
            {
                aux = sudoku[randNumber1][pos2];
                sudoku[randNumber1][pos2] = sudoku[randNumber2][pos2];
                sudoku[randNumber2][pos2] = aux;
            }
            contCambios++;
        } while (contCambios < 3);

        rangoA = rangoA + 3;
        rangoB = rangoB + 3;
    }
}

/// Mover randomicamente las matrices de 3x9
void move_random_matriz(int sudoku[][tamSudoku], int pos2)
{
    int pos, randNumber1, randNumber2, pos1A, pos1B, contCambios, aux;

    // Muevo las matrices de 3x9 (es la composicion de 3 matrices de 3x3 en fila)
    for (pos = 0; pos < 3; pos++)
    {
        randNumber1 = random_numbers(0, 3);
        randNumber2 = random_numbers(0, 3);

        do
        {
            randNumber2 = random_numbers(0, 3);
        } while (randNumber1 == randNumber2);

        pos1A = randNumber1 * 3;
        pos1B = randNumber2 * 3;

        for (contCambios = 0; contCambios < 3; contCambios++)
        {
            for (pos2 = 0; pos2 < tamSudoku; pos2++)
            {
                aux = sudoku[pos1A][pos2];
                sudoku[pos1A][pos2] = sudoku[pos1B][pos2];
                sudoku[pos1B][pos2] = aux;
            }

            pos1A++;
            pos1B++;
        }
    }
}

///Mostrar la cantidad de elementos ingresada
void show_elements(int sudoku[][tamSudoku], int cant_elem)
{
    int pos1, pos2, cont;

    // Con el tablero valido creado previamente lleno el tablero de 0 para solo dejar visible la cant_elem
    cont = (tamSudoku * tamSudoku) - cant_elem;

    while (cont > 0)
    {
        pos1 = random_numbers(0, tamSudoku);
        pos2 = random_numbers(0, tamSudoku);

        if (sudoku[pos1][pos2] != ' ' && sudoku[pos1][pos2] != 0)
        {
            sudoku[pos1][pos2] = 0;
            cont--;
        }
    }
}

///Generar un tablero de Sudoku valid
void generar_sudoku_valido(int sudoku[][tamSudoku], int cant_elem)
{
    srand(time(NULL));

    int pos1, pos2, contNum = 1, increNum = 1;

    // Rellenar tablero con numero del 1 al 9
    for (pos1 = 0; pos1 < tamSudoku; pos1++) // For de la Fila
    {
        contNum = increNum;

        for (pos2 = 0; pos2 < tamSudoku; pos2++) // For de la Columna
        {

            if (contNum <= tamSudoku)
            {
                sudoku[pos1][pos2] = contNum;
                contNum++;
            }
            else
            {
                contNum = 1;
                sudoku[pos1][pos2] = contNum;
                contNum++;
            }
        }

        // Actualizamos numero de inicio de cada Fila
        increNum = contNum + 3;

        if (contNum == 10)
        {
            increNum = 4;
        }
        if (increNum > tamSudoku)
        {
            increNum = (increNum % tamSudoku) + 1;
        }
    }

    // Randomizar columnas de a Bloque
    move_random_column(sudoku, pos1);

    // Randomizar filas de a Bloque
    move_random_row(sudoku, pos2);

    // Randomizar matrices de a Bloque
    move_random_matriz(sudoku, pos2);

    show_elements(sudoku, cant_elem);
}


///Validar que el candidato no esta en la Fila & Columna
bool es_candidato2(int sudoku[][tamSudoku], int num, int fila, int columna)
{
    int pos;
    bool candFilaColumna = false, filaCand = true, columnaCand = true;

    for (pos = 0; pos < tamSudoku; pos++)
    {

        if (num == sudoku[fila][pos])
        {
            if (pos != columna)
            {
                filaCand = false;
            }
        }
    }

    for (pos = 0; pos < tamSudoku; pos++)
    {

        if (num == sudoku[pos][columna])
        {
            if (pos != fila)
            {
                columnaCand = false;
            }
        }
    }

    if (filaCand && columnaCand)
    {
        candFilaColumna = true;
    }

    // printf("Es candidato ? %d\n", candFilaColumna);

    return candFilaColumna;
}


///Validar que el candidato no esta en el Area
bool validar_area(int sudoku[][tamSudoku], int num, int fila, int columna)
{
    int row, col;
    bool candArea = true;

    // Busco el area donde esta el numero y valido que no se repita
    for (row = fila - (fila % 3); row < (fila - (fila % 3) + 3); row++)
    {
        for (col = columna - (columna % 3); col < (columna - (columna % 3) + 3); col++)
        {
            if (num == sudoku[row][col] && sudoku[row][col] != sudoku[fila][columna])
            {
                candArea = false;
            }
        }
    }

    return candArea;
}


///Lista de Candidatos
void crear_candidatos(int sudoku[][tamSudoku], int fila, int columna, bool candidatos[tamSudoku])
{
    int pos, num;
    bool candFilaColumna, candArea;

    for (pos = 0; pos < tamSudoku; pos++){
        num = pos + 1;

        // Validar que el numero no se encuentre en la Fila & Columna
        candFilaColumna = es_candidato2(sudoku, num, fila, columna);

        // Si el numero no esta en la Fila & Columna entos valido que no este en el Area
        if (candFilaColumna){
            candArea = validar_area(sudoku, num, fila, columna);
        }

        // Si el numero no esta en la Fila, Columna o Area le asigno que es candidato valido de lo contrario no es candidato
        if (candFilaColumna && candArea){
            candidatos[pos] = true;
        }else{
            candidatos[pos] = false;
        }
    }

}


///Devuelve true o false si el tablero es valido
bool sudoku_valido(int sudoku[][tamSudoku])
{
    int pos1 = 0, pos2 = 0, num;
    bool candFilaColumna, candArea, tableroValido = true;

    // Recorro la fila y columna para ver que cada numero cumple re regla de unicidad en culumna, fila & area
    do
    {
        do
        {
            num = sudoku[pos1][pos2];
            if (num != 0)
            {
                candFilaColumna = es_candidato2(sudoku, num, pos1, pos2);
                candArea = validar_area(sudoku, num, pos1, pos2);

                if (!candFilaColumna || !candArea)
                {
                    tableroValido = false;
                }
            }

            pos2++;
        } while (pos2 < tamSudoku);
        pos1++;
        pos2 = 0;

    } while (tableroValido && pos1 < tamSudoku);

    return tableroValido;
}


///Devuelve true si el trablero esta resuelto en su completitud
bool sudoku_resuelto(int sudoku[][tamSudoku])
{

    int pos1 = 0, pos2 = 0;
    bool sudokuResuelto = false, noCero = true, tableroValido;

    // Cheque que no hay ningun 0 (osea algun espacio sin rellenar)
    for (pos1 = 0; pos1 < tamSudoku; pos1++)
    {
        for (pos2 = 0; pos2 < tamSudoku; pos2++)
        {
            if (sudoku[pos1][pos2] == 0)
            {
                noCero = false;
            }
        }
    }

    // Corroboro que todos los valores cumplan la regla de unicidad
    tableroValido = sudoku_valido(sudoku);

    // Si no hay 0 y los numeros cumplen la regla de unicidad el jugador gana
    if (noCero && tableroValido)
    {
        sudokuResuelto = true;
    }

    return sudokuResuelto;
}










