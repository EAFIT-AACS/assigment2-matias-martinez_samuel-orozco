# Derivación de Gramática y PDA ⚙️
- **Nombres Completos:**
  - Matías Martinez Moreno
  - Samuel Orozco Valencia

- **Clase:**
  - Miércoles SI2002-2 (7309)

---
> **Las lecturas 23 y 24 de Kozen (1997) se utilizaron como referencia para los conceptos de Autómatas de Pila y Gramáticas Libres de Contexto usados en este proyecto.**  
> Kozen, D. C. (1997). *Automata and Computability.* Springer-Verlag, Berlin, Heidelberg.  
---

## Sobre este proyecto 🚀

Este proyecto implementa tres algoritmos en C++ que muestran el análisis y procesamiento de una gramática libre de contexto y su correspondiente Autómata de Pila (PDA). La gramática utilizada es:

> **G:**  
> **S → aSb | ε**


1. **Algoritmo 1:**  
   - Genera cadenas que pertenecen al lenguaje definido por la gramática (cadenas aceptadas) y cadenas que no pertenecen.
   - Las cadenas generadas se muestran y se almacenan en el archivo `Cadenas_generadas.txt`.

2. **Algoritmo 2:**  
   - Implementa un PDA que reconoce las cadenas generadas por la gramática G.  
   - El PDA procesa la entrada símbolo por símbolo, gestionando una pila y registra cada configuración.  
   - Las cadenas aceptadas se almacenan en el archivo `Cadenas_aceptadas.txt`.  

3. **Algoritmo 3:**  
   - Lee las cadenas aceptadas desde `Cadenas_aceptadas.txt` y construye una tabla que muestra una derivación por la izquierda de cada cadena junto con las configuraciones correspondientes del PDA.  
   - La tabla se muestra en tres columnas:
     - **Columna 1:** La regla de producción aplicada
     - **Columna 2:** La forma sentencial obtenida después de la aplicación de la regla.
     - **Columna 3:** La configuración del PDA en la forma *(q, Pila, cadena  de entrada restante)*

---
## Entorno y Herramientas Utilizadas 💻

- **Sistema Operativo:**  
  - Windows 11

- **Lenguaje de Programación:**  
  - C++ (compilado usando g++)

- **Herramientas Requeridas**  
  - Visual Studio Code (IDE/Editor)  
  - MSYS2 / MinGW (Compilación)  
  - Símbolo del Sistema / Terminal

---

## Estructura de Archivos del Proyecto 📁

- **ALGORITHM_1_LFCO_2025_MM_SA.cpp**  
- **ALGORITHM_2_LFCO_2025_MM_SA.cpp**  
- **ALGORITHM_3_LFCO_2025_MM_SA.cpp**  
- **Main.cpp:**  
 El archivo (`Main.cpp`) incluye los tres algoritmos, ejecutándolos secuencialmente sin necesidad de pedirle datos de entrada al usuario. Toda la salida se muestra en la consola.

---

## Cómo Compilar y Ejecutar el Proyecto ❓

1. **Preparación:**
   - Coloca todos los archivos (`ALGORITHM_1_LFCO_2025_MM_SA.cpp`, `ALGORITHM_2_LFCO_2025_MM_SA.cpp`, `ALGORITHM_3_LFCO_2025_MM_SA.cpp` y `Main.cpp`) en el mismo directorio.

2. **Compilación:**
   - Abre el CMD.
   - Navega al directorio que contiene los archivos fuente.
   - Compila el proyecto ejecutando:
     ```
     g++ Main.cpp -o SimulacionPDA.exe
     ```
     (Dado que `Main.cpp` incluye los otros archivos fuente, compilar este único archivo es suficiente.)

3. **Ejecución:**
   - luego , ejecuta el ejecutable:
     ```
     .\SimulacionPDA.exe
     ```
   - El programa se ejecutará automáticamente sin requerir ninguna entrada del usuario.
   - **La salida importante se mostrará en la consola**, y se generarán dos archivos adicionales, que solo fueron para los propósitos de la ejecución interna del programa:
     - `Cadenas_generadas.txt` – contiene todas las cadenas generadas.
     - `Cadenas_aceptadas.txt` – contiene solo las cadenas aceptadas por el PDA.

---
# Explicación de los Algoritmos 🔍

## 1. ALGORITHM_1: Generación de las cadenas
Este módulo genera las cadenas **válidas** e **inválidas** según la regla de producción . Las cadenas generadas se imprimen en la consola y se guardan en el archivo `Cadenas_generadas.txt` que servirán de input para el segundo algoritmo.

### Funciones importantes

#### `generarCadenaValida`

Genera una cadena válida recursivamente según la producción **S → aSb | ε**.

```cpp
string generarCadenaValida(int profundidad) {
    if (profundidad <= 0) return ""; // Caso base: cadena vacía
    return "a" + generarCadenaValida(profundidad - 1) + "b";
}
```

#### `generarCadenaValidaAleatoria`

Selecciona una profundidad aleatoria (entre 1 y un máximo dado ( 12 en el caso que hicimos ) ) y genera una cadena válida usando `generarCadenaValida`.

```cpp
string generarCadenaValidaAleatoria(int profundidadMaxima) {
    int profundidad = rand() % profundidadMaxima + 1;
    return generarCadenaValida(profundidad);
}
```

#### `generarCadenaInvalida`

Genera una cadena inválida usando el mismo alfabeto `{a, b}`. Si la cadena generada aleatoriamente cumple accidentalmente con el patrón aⁿbⁿ, se cambia un carácter para romper la validez.

```cpp
string generarCadenaInvalida() {
    int longitud = rand() % 6 + 1; 
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
    // Si la cadena generada es válida, se altera el primer símbolo para invalidarla
    if (esValida && !cadena.empty()) {
        cadena[0] = (cadena[0] == 'a') ? 'b' : 'a';
    }
    return cadena;
}
```

#### `generarYGuardarCadenas`

GEnera 4 cadenas válidas y 4 inválidas , las muestra en la consola y las guarda en `Cadenas_generadas.txt`.

----------

## 2. ALGORITHM_2: Simulación del PDA
Este módulo simula un PDA que reconoce cadenas generadas por la gramática
 **S → aSb | ε**
 El PDA utiliza una pila donde:

-   Al leer un `'a'`, **apila** un `'A'`.
-   Al leer un `'b'`, **desapila** de la pila.

Si se intenta desapilar cuando la pila está vacía o si se encuentra un símbolo no reconocido, la cadena es rechazada. 

### Estructuras y funciones clave

#### Estructura `Configuracion`

Almacena cada paso de la simulación con la siguiente información:

-   **paso**
-   **indice:** Posición en la cadena de entrada.
-   **entradaRestante:** Porción de la entrada que queda por procesar.
-   **contenidoPila:** Contenido actual de la pila.
-   **mensaje:** Mensaje que describe la acción (apilar, desapilar, error).

#### `pilaAString`

Convierte el contenido de la pila en una cadena para facilitar su visualización (con la derivacion a la izquierda).

```cpp
string pilaAString(stack<char> pila) {
    string resultado;
    while (!pila.empty()) {
        resultado += pila.top();
        pila.pop();
    }
    reverse(resultado.begin(), resultado.end());
    return resultado;
}
```
#### `simularPDAYGuardarAceptadas`

Lee las cadenas desde `Cadenas_generadas.txt`, procesa cada cadena a través del PDA y guarda solo las cadenas aceptadas en `Cadenas_aceptadas.txt`, que serviran de input para el tercer algoritmo.

----------

## 3. ALGORITHM_3: Tabla de Derivación por la Izquierda y Configuración del PDA

Este módulo lee las cadenas aceptadas desde `Cadenas_aceptadas.txt` y, para cada cadena:

-   Construye una tabla que muestra la **derivación por la izquierda** de la cadena (según la gramática **S → aSb | ε**).
-   Muestra la **configuración del PDA** en cada paso del procesamiento de la cadena.

### Estructuras y funciones clave

#### Estructura `PasoDerivacion`

Almacena cada paso de la derivación con:

-   **regla:** La regla de producción aplicada.
-   **formaSentencial:** La forma sentencial obtenida después de aplicar la regla.

#### `derivacionIzquierda`

Genera la derivación por la izquierda para una cadena dada:

-   Comienza con la forma sentencial inicial `S`.
-   Aplica la regla **S → aSb** repetidamente según el recuento de caracteres `'a'` consecutivos.
-   Finalmente, aplica la regla **S → ε** para completar la derivación.

```cpp
vector<PasoDerivacion> derivacionIzquierda(const string &x) {
    // Contamos el número de 'a' en la cadena (n)
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
    
    // Aplicar la regla (ii): S -> ε 
    string anterior = derivacion.back().formaSentencial;
    size_t posicion = anterior.find('S');
    if (posicion != string::npos) {
        // Eliminamos la S, generando la cadena final a^n b^n
        string siguiente = anterior.substr(0, posicion) + anterior.substr(posicion + 1);
        derivacion.push_back({"(ii) S->ε ", siguiente});
    }
    
    return derivacion;
}
```
#### `computacionAceptacionPDA`

Simula el procesamiento del PDA para la cadena dada:

-   Por cada `'a'`, apila un `'A'` en la pila.
-   Por cada `'b'`, desapila de la pila.
-   Registra cada configuración antes y después de procesar un símbolo.

#### `imprimirDerivacionYPDA`

Imprime una tabla con tres columnas:

1.  Regla de producción aplicada.
2.  Forma sentencial derivada por la izquierda.
3.  Configuración del PDA en la forma _(q, Entrada Restante, Contenido Pila)_.


---
## 4. MAIN: Integración de los Módulos

El archivo `Main.cpp` incluye los otros tres módulos y llama a sus funciones secuencialmente:
