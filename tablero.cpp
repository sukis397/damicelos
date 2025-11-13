#include "tablero.h"
#include <iostream>
#include <cmath>
using namespace std;

void inicializarTablero(char tablero[TAM][TAM]) {
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            tablero[i][j] = '.';


    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < TAM; ++j)
            if ((i + j) % 2 == 1)
                tablero[i][j] = 'N';

    
    for (int i = TAM - 4; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j)
            if ((i + j) % 2 == 1)
                tablero[i][j] = 'B';
}

void mostrarTablero(const char tablero[TAM][TAM], int negras, int blancas) {
    cout << "\n     ";
    for (int j = 0; j < TAM; ++j)
        cout << static_cast<char>('A' + j) << " ";
    cout << "     [Negras: " << negras << " | Blancas: " << blancas << "]\n";

    for (int i = 0; i < TAM; ++i) {
        cout << "  " << i << "  ";
        for (int j = 0; j < TAM; ++j)
            cout << tablero[i][j] << " ";
        cout << "\n";
    }
}

void contarPiezas(const char tablero[TAM][TAM], int& negras, int& blancas) {
    negras = blancas = 0;
    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j) {
            if (tablero[i][j] == 'N' || tablero[i][j] == 'Q')
                negras++;
            else if (tablero[i][j] == 'B' || tablero[i][j] == 'W')
                blancas++;
        }
}

char verificarVictoria(const char tablero[TAM][TAM]) {
    int negras = 0, blancas = 0;
    contarPiezas(tablero, negras, blancas);

    if (negras == 0) return 'B';
    if (blancas == 0) return 'N';


    bool nPuede = false, bPuede = false;

    for (int i = 0; i < TAM; ++i)
        for (int j = 0; j < TAM; ++j) {
            char p = tablero[i][j];
            if (p == '.') continue;

            if (p == 'N' || p == 'Q') nPuede = true;
            if (p == 'B' || p == 'W') bPuede = true;
        }

    if (!nPuede) return 'B';
    if (!bPuede) return 'N';
    return '.';
}

bool hayCapturaDisponible(const char tablero[TAM][TAM], int x, int y) {
    char pieza = tablero[x][y];
    if (pieza == '.') return false;

    int dx[4] = { 1, 1, -1, -1 };
    int dy[4] = { 1, -1, 1, -1 };
    char enemigoN = 'B', enemigoQ = 'W';
    char enemigoB = 'N', enemigoW = 'Q';

    for (int k = 0; k < 4; ++k) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        int nx2 = x + 2 * dx[k];
        int ny2 = y + 2 * dy[k];
        if (nx2 >= 0 && nx2 < TAM && ny2 >= 0 && ny2 < TAM) {
            char medio = tablero[nx][ny];
            if (pieza == 'N' || pieza == 'Q') {
                if ((medio == enemigoN || medio == enemigoQ) && tablero[nx2][ny2] == '.')
                    return true;
            }
            else if (pieza == 'B' || pieza == 'W') {
                if ((medio == enemigoB || medio == enemigoW) && tablero[nx2][ny2] == '.')
                    return true;
            }
        }
    }
    return false;
}

bool moverPieza(char tablero[TAM][TAM], int x1, int y1, int x2, int y2) {
    char pieza = tablero[x1][y1];
    if (pieza == '.') return false;

    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs(dx) != abs(dy) || tablero[x2][y2] != '.')
        return false;

    char enemigo1 = 'B', enemigo2 = 'W';
    if (pieza == 'B' || pieza == 'W') {
        enemigo1 = 'N';
        enemigo2 = 'Q';
    }

   
    if (abs(dx) == 1) {
        if (pieza == 'N' && dx == 1) { 
            tablero[x2][y2] = pieza;
            tablero[x1][y1] = '.';
        }
        else if (pieza == 'B' && dx == -1) { 
            tablero[x2][y2] = pieza;
            tablero[x1][y1] = '.';
        }
        else return false;
    }

    
    else if (abs(dx) == 2) {
        int mx = x1 + dx / 2;
        int my = y1 + dy / 2;
        if (tablero[mx][my] == enemigo1 || tablero[mx][my] == enemigo2) {
            tablero[mx][my] = '.';
            tablero[x2][y2] = pieza;
            tablero[x1][y1] = '.';

            while (hayCapturaDisponible(tablero, x2, y2)) {
                mostrarTablero(tablero, 0, 0);
                cout << "Captura adicional desde " << x2 << static_cast<char>('A' + y2)
                    << " -> ingrese siguiente destino: ";
                string entrada;
                cin >> entrada;
                if (entrada.size() < 2) break;
                int nx = entrada[0] - '0';
                int ny = toupper(entrada[1]) - 'A';
                if (nx < 0 || nx >= TAM || ny < 0 || ny >= TAM) break;

                int dx2 = nx - x2, dy2 = ny - y2;
                if (abs(dx2) == 2 && abs(dy2) == 2) {
                    int mx2 = (x2 + nx) / 2;
                    int my2 = (y2 + ny) / 2;
                    if (tablero[mx2][my2] == enemigo1 || tablero[mx2][my2] == enemigo2) {
                        tablero[mx2][my2] = '.';
                        tablero[nx][ny] = pieza;
                        tablero[x2][y2] = '.';
                        x2 = nx;
                        y2 = ny;
                    }
                    else break;
                }
                else break;
            }
        }
        else return false;
    }
    else return false;

 
    if (pieza == 'N' && x2 == TAM - 1)
        tablero[x2][y2] = 'Q'; 
    else if (pieza == 'B' && x2 == 0)
        tablero[x2][y2] = 'W'; 

    return true;
}
