integrantes:
Luis Carlos GArzon GAitan
Esteban David Montero Hurtado
implementaciones:
Contador de Fichas en Tiempo Real
Sistema de Reglas Integrado en el Menú


Contador de Fichas en Tiempo Real
¿Para qué se implementó?
Para que los jugadores puedan ver en todo momento cuántas fichas le quedan a cada uno, como una forma de saber quién va ganando sin tener que contar manualmente.

¿Por qué se consideró necesario?
Es útil porque en las damas, tener más fichas generalmente significa que vas ganando. Con este contador, puedes ver de un vistazo tu ventaja o desventaja durante la partida.
¿Cómo se llevó a cabo su implementación?
Se creó en tablero.cpp con estas funciones:

contarPiezas(): Cuenta automáticamente las fichas 'N' (negras) y 'B' (blancas) en el tablero

mostrarTablero(): Muestra el contador junto al tablero: [Negras: X | Blancas: Y]

Cada vez que se mueve una ficha, el contador se actualiza solo


Sistema de Reglas Integrado en el Menú
¿Para qué se implementó?
Para que los jugadores que no conocen bien las damas internacionales puedan ver las reglas básicas directamente desde el juego, sin tener que buscarlas en internet.

¿Por qué se consideró necesario?
Mucha gente quiere jugar pero no conoce todas las reglas. Con este sistema, cualquiera puede aprender a jugar rápido y empezar una partida inmediatamente.

¿Cómo se llevó a cabo su implementación?
Se implementó en el código principal con una función que muestra las reglas:

cpp
void mostrarReglas() {
    cout << "\n=== REGLAS DE DAMAS INTERNACIONALES ===";
    cout << "\n• Tablero 10x10, 20 fichas por jugador";
    cout << "\n• Negras (N) mueven primero hacia abajo";
    cout << "\n• Blancas (B) mueven hacia arriba";
    cout << "\n• Capturas son obligatorias";
    cout << "\n• Las damas (Q/W) mueven en diagonal cualquier distancia";
    cout << "\n• Fichas normales coronan en última fila";
    cout << "\n• Gana quien capture todas las fichas del oponente\n";
}
Esta función se llama cuando el usuario selecciona la opción de ver reglas en el menú principal.
