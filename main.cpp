#include <iostream>
#include <cctype>
#include "tablero.h"
using namespace std;

int letraAIndice(char c) {
    c = toupper(c);
    if (c < 'A' || c > 'J') return -1;
    return c - 'A';
}

void mostrarReglas() {
    cout << "\n=== REGLAS DE DAMAS INTERNACIONALES ===\n";
    cout << "1. Tablero 10x10, fichas en casillas oscuras\n";
    cout << "2. Negras (N) empiezan, Blancas (B)\n";
    cout << "3. Movimiento: diagonal hacia adelante (1 casilla)\n";
    cout << "4. Captura: saltar sobre ficha enemiga (2 casillas)\n";
    cout << "5. Capturas múltiples son OBLIGATORIAS\n";
    cout << "6. Coronación: llegar al extremo opuesto -> Dama (Q/W)\n";
    cout << "7. Damas se mueven y capturan en todas direcciones\n";
    cout << "8. Gana quien capture todas las fichas o deje sin movimientos\n";
    cout << "9. Formato movimiento: fila columna (ej: 5A 4B)\n";
    cout << "==========================================\n\n";
}

int main() {
    char tablero[TAM][TAM];
    inicializarTablero(tablero);

    char turno = 'N';
    int negras = 0, blancas = 0;

    cout << "=== Damas Internacionales ===\n";
    cout << "Formato de movimiento: fila Columna (ej: 5A 4B)\n";
    cout << "Usa 'X' para salir o 'R' para ver reglas\n\n";

    while (true) {
        contarPiezas(tablero, negras, blancas);
        mostrarTablero(tablero, negras, blancas);

        char ganador = verificarVictoria(tablero);
        if (ganador != '.') {
            cout << (ganador == 'N' ? "Ganan las Negras.\n" : "Ganan las Blancas.\n");
            break;
        }

        cout << "\nTurno de: " << (turno == 'N' ? "Negras (N)" : "Blancas (B)") << "\n";
        string origen, destino;
        cout << "Movimiento (ej: 5A 4B) o 'R' para reglas: ";
        cin >> origen;

      
        if (toupper(origen[0]) == 'X') break;

   
        if (toupper(origen[0]) == 'R') {
            mostrarReglas();
            continue;  
        }

        cin >> destino;

        if (origen.size() < 2 || destino.size() < 2) {
            cout << "Entrada inválida.\n";
            continue;
        }

        int x1 = origen[0] - '0';
        int y1 = letraAIndice(origen[1]);
        int x2 = destino[0] - '0';
        int y2 = letraAIndice(destino[1]);

        if (x1 < 0 || x1 >= TAM || y1 < 0 || y1 >= TAM ||
            x2 < 0 || x2 >= TAM || y2 < 0 || y2 >= TAM) {
            cout << "Coordenadas fuera del tablero.\n";
            continue;
        }

        char pieza = tablero[x1][y1];
        if (pieza == '.') {
            cout << "No hay pieza en la casilla origen.\n";
            continue;
        }

        if ((turno == 'N' && (pieza != 'N' && pieza != 'Q')) ||
            (turno == 'B' && (pieza != 'B' && pieza != 'W'))) {
            cout << "No puedes mover piezas del otro jugador.\n";
            continue;
        }

        bool ok = moverPieza(tablero, x1, y1, x2, y2);
        if (!ok) {
            cout << "Movimiento inválido.\n";
            continue;
        }

        turno = (turno == 'N') ? 'B' : 'N';
        cout << "\n";
    }

    cout << "Juego terminado.\n";
    return 0;
}
