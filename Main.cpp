#include <iostream>
using namespace std;
// Incluimos los otros archivos de los algoritmos
#include "ALGORITHM_1_LFCO_2025_MM_SA.cpp"
#include "ALGORITHM_2_LFCO_2025_MM_SA.cpp"
#include "ALGORITHM_3_LFCO_2025_MM_SA.cpp"

int main() {

    cout << "Matias Martinez y Samuel Orozco\n\n";
    // Generar cadenas validas e invalidas (ALGORITHM_1)
    generarYGuardarCadenas();

    // Simular el PDA y guardar las cadenas aceptadas (ALGORITHM_2)
    simularPDAYGuardarAceptadas();

    // Mostrar la derivacion y configuraciones para las cadenas aceptadas (ALGORITHM_3)
    ejecutarAlgoritmo3();

    cout << "SIMULACION COMPLETA\n";
    return 0;
}