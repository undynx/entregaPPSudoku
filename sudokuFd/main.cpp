// Federico Bracesco    -   4.426.591-7     -   fedebracesco@gmail.com
// Sofia Rossi          -   5.285.147-7     -   sofiarossi161@gmail.com

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int size = 9;

/// Requerida - Crea tablero de Sudoku
void inicializar_sudoku(int sudoku[][size]);

/// Requerida - Imprimi tablero de Sudoku
void imprimir_sudoku(int sudoku[][size]);

/// Devuelve un Numero randon en base a rango dado
int random_numbers(int minNum, int maxNum);

/// Mover randomicamente las Columnas
void move_random_column(int sudoku[][size], int pos1);

/// Mover randomicamente las Filas
void move_random_row(int sudoku[][size], int pos2);

/// Mover randomicamente las matrices de 3x9
void move_random_matriz(int sudoku[][size], int pos2);

/// Mostrar la cantidad de elementos ingresada
void show_elements(int sudoku[][size], int cant_elem);

/// Requerida - Generar un tablero de Sudoku valid
void generar_sudoku_valido(int sudoku[][size], int cant_elem);

/// Requerida - Validar que el candidato no esta en la Fila & Columna
bool es_candidato2(int sudoku[][size], int num, int fila, int columna);

/// Validar que el candidato no esta en el Area
bool validar_area(int sudoku[][size], int num, int fila, int columna);

/// Requerida - Lista de Candidatos
void crear_candidatos(int sudoku[][size], int fila, int columna, bool candidatos[size]);

/// Requerida - Devuelve true o false si el tablero es valido
bool sudoku_valido(int sudoku[][size]);

/// Requerida - Devuelve true si el trablero esta resuelto en su completitud
bool sudoku_resuelto(int sudoku[][size]);

int main()
{
    int sudokuInGame[size][size], cantCoso;

    bool esCandFilaColumna, candidatos[size],  esValido, estaResuelto;

    inicializar_sudoku(sudokuInGame);

    printf("Cuantos coso: ");
    scanf("%d", &cantCoso);
    getchar();

    generar_sudoku_valido(sudokuInGame, cantCoso);

    imprimir_sudoku(sudokuInGame);

    esValido = sudoku_valido(sudokuInGame);
    printf("Es valido? %d\n", esValido);
    estaResuelto = sudoku_resuelto(sudokuInGame);
    printf("Esta resuelto? %d", estaResuelto);

    return 0;
}

void inicializar_sudoku(int sudoku[][size])
{
    int pos1, pos2;

    // Inicializar la matriz del Sudoku con 0
    for (pos1 = 0; pos1 < size; pos1++)
    {
        for (pos2 = 0; pos2 < size; pos2++)
        {
            sudoku[pos1][pos2] = 0;
        }
    }
}

void imprimir_sudoku(int sudoku[][size])
{
    int pos1, pos2;

    for (pos2 = 0; pos2 < size; pos2++)
    {
        printf("++++");

        if (pos2 == 2 || pos2 == 5)
        {
            printf("+");
        }
    }
    printf("+\n");

    for (pos1 = 0; pos1 < size; pos1++)
    {
        for (pos2 = 0; pos2 < size; pos2++)
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

            for (pos2 = 0; pos2 < size; pos2++)
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

    for (pos2 = 0; pos2 < size; pos2++)
    {
        printf("++++");

        if (pos2 == 2 || pos2 == 5)
        {
            printf("+");
        }
    }
    printf("+\n");
}

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

void move_random_column(int sudoku[][size], int pos1)
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

            for (pos1 = 0; pos1 < size; pos1++)
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

void move_random_row(int sudoku[][size], int pos2)
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

            for (pos2 = 0; pos2 < size; pos2++)
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

void move_random_matriz(int sudoku[][size], int pos2)
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
            for (pos2 = 0; pos2 < size; pos2++)
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

void show_elements(int sudoku[][size], int cant_elem)
{
    int pos1, pos2, cont;

    // Con el tablero valido creado previamente lleno el tablero de 0 para solo dejar visible la cant_elem
    cont = (size * size) - cant_elem;

    while (cont > 0)
    {
        pos1 = random_numbers(0, size);
        pos2 = random_numbers(0, size);

        if (sudoku[pos1][pos2] != ' ' && sudoku[pos1][pos2] != 0)
        {
            sudoku[pos1][pos2] = 0;
            cont--;
        }
    }
}

void generar_sudoku_valido(int sudoku[][size], int cant_elem)
{
    srand(time(NULL));

    int pos1, pos2, pos, contNum = 1, increNum = 1, cont = 20;

    // Rellenar tablero con numero del 1 al 9
    for (pos1 = 0; pos1 < size; pos1++) // For de la Fila
    {
        contNum = increNum;

        for (pos2 = 0; pos2 < size; pos2++) // For de la Columna
        {

            if (contNum <= size)
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
        if (increNum > size)
        {
            increNum = (increNum % size) + 1;
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

bool es_candidato2(int sudoku[][size], int num, int fila, int columna)
{
    int pos;
    bool candFilaColumna = false, filaCand = true, columnaCand = true;

    for (pos = 0; pos < size; pos++)
    {

        if (num == sudoku[fila][pos])
        {
            if (pos != columna)
            {
                filaCand = false;
            }
        }
    }

    for (pos = 0; pos < size; pos++)
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

bool validar_area(int sudoku[][size], int num, int fila, int columna)
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

void crear_candidatos(int sudoku[][size], int fila, int columna, bool candidatos[size])
{
    int pos, num;
    bool candFilaColumna, candArea;

    for (pos = 0; pos < size; pos++)
    {
        num = pos + 1;

        // Validar que el numero no se encuentre en la Fila & Columna
        candFilaColumna = es_candidato2(sudoku, num, fila, columna);

        // Si el numero no esta en la Fila & Columna entos valido que no este en el Area
        if (candFilaColumna)
        {
            candArea = validar_area(sudoku, num, fila, columna);
        }

        // Si el numero no esta en la Fila, Columna o Area le asigno que es candidato valido de lo contrario no es candidato
        if (candFilaColumna && candArea)
        {
            candidatos[pos] = true;
        }
        else
        {
            candidatos[pos] = false;
        }
    }

    for (pos = 0; pos < size; pos++)
    {
        num = pos + 1;
        printf("El numero %d, true=1 o false=0 - %d\n", num, candidatos[pos]);
    }
}

bool sudoku_valido(int sudoku[][size])
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
        } while (pos2 < size);
        pos1++;
        pos2 = 0;

    } while (tableroValido && pos1 < size);

    return tableroValido;
}

bool sudoku_resuelto(int sudoku[][size])
{

    int pos1 = 0, pos2 = 0, num;
    bool sudokuResuelto = false, noCero = true, tableroValido;

    // Cheque que no hay ningun 0 (osea algun espacio sin rellenar)
    for (pos1 = 0; pos1 < size; pos1++)
    {
        for (pos2 = 0; pos2 < size; pos2++)
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
