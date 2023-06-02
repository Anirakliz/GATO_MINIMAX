#include <iostream>
#include <vector>

using namespace std;

// Función para imprimir el tablero
void imprimirTablero(const vector<char>& tablero) {
    cout << "-------------" << endl;
    for (int i = 0; i < 9; i += 3) {
        cout << "| " << tablero[i] << " | " << tablero[i + 1] << " | " << tablero[i + 2] << " |" << endl;
        cout << "-------------" << endl;
    }
}

// Función para verificar si alguien ha ganado el juego
bool verificarGanador(const vector<char>& tablero, char jugador) {
    // Combinaciones ganadoras
    vector<vector<int>> combinacionesGanadoras = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Filas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columnas
        {0, 4, 8}, {2, 4, 6}             // Diagonales
    };

    for (const auto& combinacion : combinacionesGanadoras) {
        if (tablero[combinacion[0]] == jugador && tablero[combinacion[1]] == jugador && tablero[combinacion[2]] == jugador) {
            return true; // Si encontramos una combinación ganadora, devolvemos verdadero
        }
    }
    return false; // Si no hay combinaciones ganadoras, devolvemos falso
}

// Función para verificar si el juego ha terminado
bool juegoTerminado(const vector<char>& tablero) {
    // Si hay un ganador, el juego ha terminado
    if (verificarGanador(tablero, 'X') || verificarGanador(tablero, 'O')) {
        return true;
    }

    // Si no hay espacios vacíos, el juego ha terminado en empate
    for (char c : tablero) {
        if (c == ' ') {
            return false;
        }
    }

    return true;
}

// Función que implementa el algoritmo Minimax para determinar la mejor jugada
int minimax(vector<char>& tablero, int profundidad, bool esMaximizador) {
    if (verificarGanador(tablero, 'X')) {
        return -1; // Si gana 'X', devolvemos -1
    }

    if (verificarGanador(tablero, 'O')) {
        return 1; // Si gana 'O', devolvemos 1
    }

    if (juegoTerminado(tablero)) {
        return 0; // Si hay empate, devolvemos 0
    }

    if (esMaximizador) {
        int mejorPuntaje = -1000;

        for (int i = 0; i < 9; ++i) {
            if (tablero[i] == ' ') {
                tablero[i] = 'O';
                mejorPuntaje = max(mejorPuntaje, minimax(tablero, profundidad + 1, !esMaximizador));
                tablero[i] = ' ';
            }
        }

        return mejorPuntaje;
    } else {
        int mejorPuntaje = 1000;

        for (int i = 0; i < 9; ++i) {
            if (tablero[i] == ' ') {
                tablero[i] = 'X';
                mejorPuntaje = min(mejorPuntaje, minimax(tablero, profundidad + 1, !esMaximizador));
                tablero[i] = ' ';
            }
        }

        return mejorPuntaje;
    }
}

// Función para determinar la mejor jugada utilizando el algoritmo Minimax
int obtenerMejorJugada(vector<char>& tablero) {
    int mejorPuntaje = -1000;
    int mejorJugada = -1;

    for (int i = 0; i < 9; ++i) {
        if (tablero[i] == ' ') {
            tablero[i] = 'O';
            int puntaje = minimax(tablero, 0, false);
            tablero[i] = ' ';

            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejorJugada = i;
            }
        }
    }

    return mejorJugada;
}

// Función principal del juego
void jugarGato() {
    vector<char> tablero(9, ' ');
    int jugadorActual = 0;

    while (!juegoTerminado(tablero)) {
        imprimirTablero(tablero);

        if (jugadorActual % 2 == 0) {
            cout << "Turno del jugador X. Elija una casilla (0-8): ";
            int casilla;
            cin >> casilla;

            if (tablero[casilla] == ' ') {
                tablero[casilla] = 'X';
                jugadorActual++;
            } else {
                cout << "Casilla inválida. Inténtelo de nuevo." << endl;
            }
        } else {
            cout << "Turno del jugador O..." << endl;
            int mejorJugada = obtenerMejorJugada(tablero);

            if (mejorJugada != -1) {
                tablero[mejorJugada] = 'O';
                jugadorActual++;
            } else {
                cout << "¡No se puede determinar una jugada válida!" << endl;
                break;
            }
        }
    }

    imprimirTablero(tablero);

    if (verificarGanador(tablero, 'X')) {
        cout << "¡El jugador X ha ganado!" << endl;
    } else if (verificarGanador(tablero, 'O')) {
        cout << "¡El jugador O ha ganado!" << endl;
    } else {
        cout << "¡Empate!" << endl;
    }
}

// Función principal
int main() {
    jugarGato();
    return 0;
}
