#include <iostream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// Función para calcular el costo de sustituir un carácter por otro.
// Si los caracteres son iguales, el costo es 0; de lo contrario, es 2.
int costoSub(char a, char b) { return (a == b) ? 0 : 2; }

// Función para calcular el costo de insertar un carácter. El costo siempre es 1.
int costoIns(char b) { return 1; }

// Función para calcular el costo de eliminar un carácter. El costo siempre es 1.
int costoDel(char a) { return 1; }

// Función para calcular el costo de transponer (intercambiar) dos caracteres consecutivos.
// Si los caracteres son iguales, el costo es 0; de lo contrario, es 1.
int costoTrans(char a, char b) { return (a == b) ? 0 : 1; }

// Función para calcular el costo mínimo de transformar una cadena "s1" en otra "s2" utilizando programación dinámica.
int transformar(const string &s1, const string &s2) {
    int m = s1.size(); // Longitud de la cadena "s1".
    int n = s2.size(); // Longitud de la cadena "s2".

    // Crear una tabla `dp` de dimensiones (m+1) x (n+1) inicializada con valores muy grandes (INT_MAX).
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));

    // Caso base: transformar una cadena vacía en otra vacía tiene costo 0.
    dp[0][0] = 0;

    // Caso base: transformar "s1" en una cadena vacía implica eliminar todos los caracteres de "s1".
    for (int i = 1; i <= m; i++) {
        dp[i][0] = dp[i - 1][0] + costoDel(s1[i - 1]);
    }

    // Caso base: transformar una cadena vacía en "s2" implica insertar todos los caracteres de "s2".
    for (int j = 1; j <= n; j++) {
        dp[0][j] = dp[0][j - 1] + costoIns(s2[j - 1]);
    }

    // Llenar la tabla `dp` usando programación dinámica.
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            // Opción 1: Sustitución. Cambiar el carácter actual de "s1" por el de "s2".
            int costoSust = dp[i - 1][j - 1] + costoSub(s1[i - 1], s2[j - 1]);
            dp[i][j] = min(dp[i][j], costoSust);

            // Opción 2: Inserción. Insertar el carácter actual de "s2" en "s1".
            int costoInser = dp[i][j - 1] + costoIns(s2[j - 1]);
            dp[i][j] = min(dp[i][j], costoInser);

            // Opción 3: Eliminación. Eliminar el carácter actual de "s1".
            int costoElim = dp[i - 1][j] + costoDel(s1[i - 1]);
            dp[i][j] = min(dp[i][j], costoElim);

            // Opción 4: Transposición. Intercambiar dos caracteres consecutivos.
            if (i > 1 && j > 1 && s1[i - 1] == s2[j - 2] && s1[i - 2] == s2[j - 1]) {
                int costoTransp = dp[i - 2][j - 2] + costoTrans(s1[i - 2], s1[i - 1]);
                dp[i][j] = min(dp[i][j], costoTransp);
            }
        }
    }

    // El costo mínimo para transformar "s1" en "s2" está en la celda dp[m][n].
    return dp[m][n];
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