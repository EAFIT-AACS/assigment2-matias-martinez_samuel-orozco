#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Estructura para almacenar cada paso de la derivacion
struct PasoDerivacion {
    string regla;           
    string formaSentencial; 
};

// Funcion que genera la derivacion por la izquierda 
vector<PasoDerivacion> derivacionIzquierda(const string &x) {
    // Contamos el numero de 'a' en la cadena (n)
    int n = 0;
    for (char caracter : x) {
        if (caracter == 'a')
            n++;
        else
            break;
    }
    
    vector<PasoDerivacion> derivacion;
    derivacion.push_back({"(inicio)", "S"});  // Paso inicial: S
    
    // Aplicar la regla (i) n veces: S -> aSb 
    for (int i = 0; i < n; i++) {
        string anterior = derivacion.back().formaSentencial;
        size_t posicion = anterior.find('S');
        if (posicion != string::npos) {
            string siguiente = anterior.substr(0, posicion) + "aSb" + anterior.substr(posicion + 1);
            derivacion.push_back({"(i) S->aSb ", siguiente});
        }
    }
    
    // Aplicar la regla (ii): S -> epsilon 
    string anterior = derivacion.back().formaSentencial;
    size_t posicion = anterior.find('S');
    if (posicion != string::npos) {
        // Eliminamos la S, generando la cadena final a^n b^n
        string siguiente = anterior.substr(0, posicion) + anterior.substr(posicion + 1);
        derivacion.push_back({"(ii) S->epsilon ", siguiente});
    }
    
    return derivacion;
}

// Estructura para almacenar la configuracion del PDA en cada paso
struct ConfigPDA {
    string contenidoPila;   
    string entradaRestante; 
};

// Funcion para convertir el contenido de la pila en un string
string pilaPDAaString(stack<char> pila) {
    string resultado;
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}

// Funcion que simula la computacion del PDA 
// Por cada 'a' apila 'A' y por cada 'b' desapila 'A'.
// Registra cada configuracion en un vector.
vector<ConfigPDA> computacionAceptacionPDA(const string &x) {
    vector<ConfigPDA> historial;
    stack<char> pilaPDA;
    string entrada = x;
    
    // Guardar la configuracion inicial
    ConfigPDA inicial;
    inicial.contenidoPila = pilaPDAaString(pilaPDA);
    inicial.entradaRestante = entrada;
    historial.push_back(inicial);
    
    // Procesar cada caracter de la entrada
    for (int i = 0; i < x.size(); i++) {
        char caracter = x[i];
        if (caracter == 'a') {
            pilaPDA.push('A'); // Push 'A'
        } else if (caracter == 'b') {
            if (!pilaPDA.empty()) {
                pilaPDA.pop(); // Pop 'A'
            }
        }
        // Se elimina el primer caracter de la entrada (simula que ya fue procesado)
        entrada.erase(0, 1);
        ConfigPDA cfg;
        cfg.contenidoPila = pilaPDAaString(pilaPDA);
        cfg.entradaRestante = entrada;
        historial.push_back(cfg);
    }
    
    // Si la entrada ya se consumio y la pila esta vacia, ajustar la ultima configuracion
    if (entrada.empty() && pilaPDA.empty()) {
        historial.back().entradaRestante = "(vacia)";
        historial.back().contenidoPila = "(vacia)";
    }
    
    return historial;
}

// Funcion que imprime una tabla con tres columnas:
// 1. Regla aplicada
// 2. Sentencia derivada (por la izquierda)
// 3. Configuraciones de M
void imprimirDerivacionYPDA(const vector<PasoDerivacion> &derivacion,
                           const vector<ConfigPDA> &configsPDA,
                           const string &entrada) 
{
    cout << "================================================\n";
    cout << "Derivacion y Configuracion para: \"" << entrada << "\"\n";
    cout << "Regla                                     | Sentencia derivada por la izquierda    | Configuraciones de M\n";
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    
    size_t filas = max(derivacion.size(), configsPDA.size());
    const int anchoRegla = 40;
    const int anchoSentencia = 40;
    for (size_t i = 0; i < filas; i++) {
        string colRegla = (i < derivacion.size()) ? derivacion[i].regla : "";
        string colSentencia = (i < derivacion.size()) ? derivacion[i].formaSentencial : "";
        string colConfig = (i < configsPDA.size()) ? "(q, " + configsPDA[i].entradaRestante + ", " + configsPDA[i].contenidoPila + ")" : "";
        
        cout << colRegla << string(anchoRegla - colRegla.size(), ' ') << " | "
             << colSentencia << string(anchoSentencia - colSentencia.size(), ' ') << " | "
             << colConfig << "\n";
    }
    cout << "-------------------------------------------------------------------------------------------------------------------\n\n";
}

// Lee las cadenas aceptadas desde "Cadenas_aceptadas.txt"
// y construye la tabla de derivacion y configuracion para cada cadena.
void ejecutarAlgoritmo3() {
    cout << "====================================================================================\n";
    cout << "                      ALGORITHM_3 \n";
    cout << "          (Lectura 24, Dexter Kozen pagina 169)\n";
    
    ifstream archivoEntrada("Cadenas_aceptadas.txt");
    if (!archivoEntrada) {
        cerr << "Error: No se pudo abrir 'Cadenas_aceptadas.txt'.\n";
        return;
    }
    
    vector<string> cadenasAceptadas;
    string linea;
    while (getline(archivoEntrada, linea)) {
        if (!linea.empty()) {
            cadenasAceptadas.push_back(linea);
        }
    }
    archivoEntrada.close();

    for (auto &cadena : cadenasAceptadas) {
        vector<PasoDerivacion> deriv = derivacionIzquierda(cadena);
        vector<ConfigPDA> configs = computacionAceptacionPDA(cadena);
        imprimirDerivacionYPDA(deriv, configs, cadena);
    }
    cout << "Fin de ALGORITHM_3.\n\n";
}