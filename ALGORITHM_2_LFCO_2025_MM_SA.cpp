#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

// Estructura para almacenar la configuracion del PDA
struct Configuracion {
    int paso;              
    int indice;            // Posicion en la cadena
    string entradaRestante;// Parte de la cadena que falta por procesar
    string contenidoPila;  // Representacion de la pila
    string mensaje;        // Mensaje explicando la accion (apilar/desapilar/error)
};

// Convierte la pila en un string, con la base a la izquierda.
string pilaAString(stack<char> pila) {
    string resultado;
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

/**
 * Simula el PDA que reconoce la gramatica S -> aSb | epsilon.
 * Retorna true si la cadena se acepta (pila vacia).
 * Ademas, llena el vector 'configuraciones' con la info de cada paso.
 */
bool simulacionPDA(const string &entrada, vector<Configuracion> &configuraciones) {
    stack<char> pilaPDA;
    int paso = 0;

    Configuracion inicial;
    inicial.paso = paso;
    inicial.indice = 0;
    inicial.entradaRestante = entrada;
    inicial.contenidoPila = pilaAString(pilaPDA);
    inicial.mensaje = "Paso inicial (pila vacia)";
    configuraciones.push_back(inicial);

    // Procesar simbolo a simbolo
    for (int i = 0; i < (int)entrada.size(); i++) {
        char caracter = entrada[i];
        paso++;

        // Nueva configuracion
        Configuracion conf;
        conf.paso = paso;
        conf.indice = i + 1;  // Hemos procesado i+1 simbolos
        conf.entradaRestante = entrada.substr(i + 1);
        
        // Accion segun 'a' o 'b'
        if (caracter == 'a') {
            // Apilar
            pilaPDA.push('A');
            conf.mensaje = "Procesando simbolo '" + string(1, caracter) + "', Accion: Apilar 'A'";
        } 
        else if (caracter == 'b') {
            // Desapilar
            if (pilaPDA.empty()) {
                conf.mensaje = "Procesando simbolo '" + string(1, caracter) + "', Error: Pila vacia. RECHAZADA";
                conf.contenidoPila = pilaAString(pilaPDA);
                configuraciones.push_back(conf);
                return false;
            }
            pilaPDA.pop();
            conf.mensaje = "Procesando simbolo '" + string(1, caracter) + "', Accion: Desapilar 'A'";
        } 
        else {
            // Simbolo no reconocido
            conf.mensaje = "Procesando simbolo '" + string(1, caracter) + "', Error: Simbolo no reconocido. RECHAZADA";
            conf.contenidoPila = pilaAString(pilaPDA);
            configuraciones.push_back(conf);
            return false;
        }

        conf.contenidoPila = pilaAString(pilaPDA);
        configuraciones.push_back(conf);
    }
    
    // Aceptacion si la pila queda vacia
    if (pilaPDA.empty()) {
        return true;
    } else {
        return false;
    }
}

void imprimirConfiguraciones(const vector<Configuracion> &configuraciones) {
    for (auto &conf : configuraciones) {
        cout << "Paso " << conf.paso 
             << " | Entrada restante: \"" << conf.entradaRestante << "\""
             << " | Pila: [";
        // Si la pila esta vacia, la representamos con nada
        if (conf.contenidoPila.empty()) {
            cout << "";
        } else {
            cout << conf.contenidoPila;
        }
        cout << "]";
        cout << " " << conf.mensaje << "\n";
    }
}

/**
 * Lee las cadenas de "Cadenas_generadas.txt", las procesa con el PDA
 * y guarda en "Cadenas_aceptadas.txt" solo las que fueron aceptadas.
 */
void simularPDAYGuardarAceptadas() {
    cout << "====================================================================================\n";
    cout << "                  ALGORITHM_2 - Simulacion del PDA\n\n";

    ifstream archivoEntrada("Cadenas_generadas.txt");
    if (!archivoEntrada) {
        cerr << "Error al abrir 'Cadenas_generadas.txt' para lectura.\n";
        return;
    }

    ofstream archivoAceptadas("Cadenas_aceptadas.txt");
    if (!archivoAceptadas) {
        cerr << "Error al crear 'Cadenas_aceptadas.txt'.\n";
        return;
    }

    vector<string> cadenasPrueba;
    string linea;
    while (getline(archivoEntrada, linea)) {
        if (!linea.empty()) {
            cadenasPrueba.push_back(linea);
        }
    }
    archivoEntrada.close();

    // Procesar cada cadena
    for (auto &cadena : cadenasPrueba) {
        cout << "Procesando cadena: \"" << cadena << "\"\n";

        vector<Configuracion> configuraciones;
        bool aceptada = simulacionPDA(cadena, configuraciones);

        // Imprimir el resumen al final
        imprimirConfiguraciones(configuraciones);

        cout << "\nResultado final para la cadena \"" << cadena << "\": " 
             << (aceptada ? "ACEPTADA" : "RECHAZADA") << "\n";
        cout << "--------------------------------------------\n\n";

        // Si se acepta, la guardamos en Cadenas_aceptadas.txt
        if (aceptada) {
            archivoAceptadas << cadena << endl;
        }
    }

    archivoAceptadas.close();
    cout << "Fin de ALGORITHM_2.\n\n";
}