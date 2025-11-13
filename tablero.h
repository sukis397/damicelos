#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>

const int TAM = 10;
void inicializarTablero(char tablero[TAM][TAM]);


void mostrarTablero(const char tablero[TAM][TAM], int negras, int blancas);


bool moverPieza(char tablero[TAM][TAM], int x1, int y1, int x2, int y2);


bool hayCapturaDisponible(const char tablero[TAM][TAM], int x, int y);


void contarPiezas(const char tablero[TAM][TAM], int& negras, int& blancas);


char verificarVictoria(const char tablero[TAM][TAM]);

#endif
