#include <iostream>   
#include <vector>     
#include <string>     // Para manipulacion de cadenas de caracteres
#include <cstdlib>    // Para generar numeros aleatorios (rand, srand)
#include <ctime>      // Para inicializar la semilla aleatoria 
#include <algorithm>  // Para usar find en la busqueda de elementos en vectores
#include <fstream>    // Para escribir en los archivos de texto
using namespace std;

/**
 * Genera recursivamente una cadena valida segun la gramatica:
 *   S -> aSb |epsilon
 * para un numero determinado de pares (la profundidad de la cadena (depth)).
 */
string generarCadenaValida(int profundidad) {
    if (profundidad <= 0) return ""; // Caso base: cadena vacia
    return "a" + generarCadenaValida(profundidad - 1) + "b";
}

string generarCadenaValidaAleatoria(int profundidadMaxima) {
    int profundidad = rand() % profundidadMaxima + 1;
    return generarCadenaValida(profundidad);
}
/**
 * Genera una cadena invalida utilizando el mismo alfabeto {a, b}.
 * Se genera una cadena aleatoria; si por azar resulta valida (a^n b^n),
 * se cambia una letra para romper la validez.
 */
string generarCadenaInvalida() {
    int longitud = rand() % 6+1; 
    string cadena;
    for (int i = 0; i < longitud; i++) {
        char caracter = (rand() % 2 == 0) ? 'a' : 'b';
        cadena.push_back(caracter);
    }
    // Verificar si la cadena cumple la forma a^n b^n
    int conteoA = 0, conteoB = 0;
    for (char caracter : cadena) {
        if (caracter == 'a') conteoA++; else conteoB++;
    }
    bool esValida = false;
    if (conteoA == conteoB && conteoA > 0) {
        // Revisar que sea a^n b^n
        esValida = true;
        for (int i = 0; i < conteoA; i++) {
            if (cadena[i] != 'a') { esValida = false; break; }
        }
        for (int i = conteoA; i < (int)cadena.size(); i++) {
            if (cadena[i] != 'b') { esValida = false; break; }
        }
    }
    // Si la cadena generada es valida, se altera el primer simbolo para invalidarla
    if (esValida && !cadena.empty()) {
        cadena[0] = (cadena[0] == 'a') ? 'b' : 'a';
    }
    return cadena;
}

/**
 * Funcion que genera 5 cadenas validas y 5 cadenas invalidas,
 * las muestra en consola y las escribe en "Cadenas_generadas.txt".
 */
void generarYGuardarCadenas() {
    srand(static_cast<unsigned int>(time(NULL))); // Semilla para los numeros aleatorios
    
    cout << "====================================================================================\n";
    cout << "              ALGORITHM_1 - Generacion de Cadenas\n\n";
    
    int numeroValidas = 4;
    int numeroInvalidas = 4;
    int profundidadMaxima = 12;
    
    vector<string> cadenasValidas;
    vector<string> cadenasInvalidas;
    
    // Generar cadenas validas sin duplicados
    while(cadenasValidas.size() < (size_t)numeroValidas) {
        string cadena = generarCadenaValidaAleatoria(profundidadMaxima);
        if (find(cadenasValidas.begin(), cadenasValidas.end(), cadena) == cadenasValidas.end()) {
            cadenasValidas.push_back(cadena);
        }
    }
    
    // Generar cadenas invalidas sin duplicados
    while(cadenasInvalidas.size() < (size_t)numeroInvalidas) {
        string cadena = generarCadenaInvalida();
        if (find(cadenasInvalidas.begin(), cadenasInvalidas.end(), cadena) == cadenasInvalidas.end()) {
            cadenasInvalidas.push_back(cadena);
        }
    }
    
    // Mostrar resultados en consola
    cout << "============================================\n";
    cout << "  Cadenas ACEPTADAS (S -> aSb | epsilon):\n";
    for (size_t i = 0; i < cadenasValidas.size(); i++) {
        cout << "  " << i + 1 << ". \"" << cadenasValidas[i] << "\"\n";
    }
    
    cout << "\n============================================\n";
    cout << "  Cadenas RECHAZADAS:\n";
    for (size_t i = 0; i < cadenasInvalidas.size(); i++) {
        cout << "  " << i + 1 << ". \"" << cadenasInvalidas[i] << "\"\n";
    }
    
    // Guardar las cadenas en "Cadenas_generadas.txt"
    ofstream archivoSalida("Cadenas_generadas.txt");
    if (!archivoSalida) {
        cerr << "Error al abrir 'Cadenas_generadas.txt' para escritura.\n";
        return;
    }
    // Primero las validas, luego las invalidas
    for (const auto &cadena : cadenasValidas) {
        archivoSalida << cadena << endl;
    }
    for (const auto &cadena : cadenasInvalidas) {
        archivoSalida << cadena << endl;
    }
    archivoSalida.close();
    
    cout << "\nFin de ALGORITHM_1.\n\n";
}