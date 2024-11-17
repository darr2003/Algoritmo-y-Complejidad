#include <iostream>
#include <string>
#include <limits>
#include <chrono> 

using namespace std;

// Función para calcular el costo de sustituir un carácter por otro.
// Si los caracteres son iguales, el costo es 0; de lo contrario, es 2.
int costo_sub(char a, char b) { return (a == b) ? 0 : 2; }

// Función para calcular el costo de insertar un carácter. El costo siempre es 1.
int costo_ins(char b) { return 1; }

// Función para calcular el costo de eliminar un carácter. El costo siempre es 1.
int costo_del(char a) { return 1; }

// Función para calcular el costo de transponer (intercambiar) dos caracteres consecutivos.
// Si los caracteres son iguales, el costo es 0; de lo contrario, es 1.
int costo_trans(char a, char b) { return (a == b) ? 0 : 1; }

// Función recursiva para calcular el costo mínimo de transformar una cadena "origen" en otra "objetivo".
// Los parámetros son:
// - origen: la cadena inicial.
// - objetivo: la cadena final deseada.
// - i, j: índices actuales en las cadenas "origen" y "objetivo" respectivamente.
// - costo_acumulado: el costo acumulado hasta el momento.
int transformar(const string& origen, const string& objetivo, int i = 0, int j = 0, int costo_acumulado = 0) {
    // Caso base: si ambas cadenas han sido procesadas completamente, retorna el costo acumulado.
    if (i == (int)origen.length() && j == (int)objetivo.length()) {
        return costo_acumulado;
    }
    // Caso base: si se llegó al final de la cadena "origen", agrega el costo de insertar los caracteres restantes de "objetivo".
    if (i == (int)origen.length()) {
        return costo_acumulado + (objetivo.length() - j);
    }
    // Caso base: si se llegó al final de la cadena "objetivo", agrega el costo de eliminar los caracteres restantes de "origen".
    if (j == (int)objetivo.length()) {
        return costo_acumulado + (origen.length() - i);
    }

    // Inicializa el costo mínimo como un valor muy grande (infinito).
    int costo_min = numeric_limits<int>::max();

    // Opción 1: Sustitución. Calcula el costo acumulado y llama recursivamente avanzando ambos índices.
    int costo_sust = costo_acumulado + costo_sub(origen[i], objetivo[j]);
    costo_min = min(costo_min, transformar(origen, objetivo, i + 1, j + 1, costo_sust));

    // Opción 2: Inserción. Calcula el costo acumulado y llama recursivamente avanzando el índice de "objetivo".
    int costo_inser = costo_acumulado + costo_ins(objetivo[j]);
    costo_min = min(costo_min, transformar(origen, objetivo, i, j + 1, costo_inser));

    // Opción 3: Eliminación. Calcula el costo acumulado y llama recursivamente avanzando el índice de "origen".
    int costo_elim = costo_acumulado + costo_del(origen[i]);
    costo_min = min(costo_min, transformar(origen, objetivo, i + 1, j, costo_elim));

    // Opción 4: Transposición. Solo aplica si hay al menos dos caracteres disponibles en ambas cadenas y coinciden intercambiados.
    if (i + 1 < (int)origen.length() && j + 1 < (int)objetivo.length() && origen[i] == objetivo[j + 1] && origen[i + 1] == objetivo[j]) {
        int costo_transp = costo_acumulado + costo_trans(origen[i], origen[i + 1]);
        costo_min = min(costo_min, transformar(origen, objetivo, i + 2, j + 2, costo_transp));
    }

    // Retorna el costo mínimo calculado.
    return costo_min;
}

int main() {
    // Declaración de las cadenas "origen" y "objetivo".
    string origen, objetivo;

    // Leer ambas cadenas desde la entrada estándar.
    getline(cin, origen);
    getline(cin, objetivo);

    // auto start = chrono::high_resolution_clock::now();

    // Calcula el costo mínimo de transformar "origen" en "objetivo".
    int costo_minimo = transformar(origen, objetivo);
    // auto end = chrono::high_resolution_clock::now();
    // float duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();


    // Imprime el costo mínimo.
    cout << costo_minimo << endl;
    // cout << duration/1000000<<"\n";

    return 0;
}