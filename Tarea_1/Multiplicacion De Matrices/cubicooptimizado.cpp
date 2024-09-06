#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

vector<vector<int>> MatrixMultOp(vector<vector<int>> a, vector<vector<int>> b) {
    int n = a.size();
    int m = b.size();
    int p = b[0].size();

    vector<vector<int>> c(n, vector<int>(p, 0));

    if (a[0].size() != m) {
        return {};
    }

    int T = sqrt(m); 

    for (int I = 0; I < n; I += T) {
        for (int J = 0; J < p; J += T) {
            for (int K = 0; K < m; K += T) {
                for (int i = I; i < min(I + T, n); ++i) {
                    for (int j = J; j < min(J + T, p); ++j) {
                        int sum = 0;
                        for (int k = K; k < min(K + T, m); ++k) {
                            sum += a[i][k] * b[k][j];
                        }
                        c[i][j] += sum;
                    }
                }
            }
        }
    }

    return c;
}

int main() {
    ifstream infile("Input.txt"); 
    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo 'Input.txt' para leer." << endl;
        return 1;
    }

    ofstream outfile("Resultados.txt");  
    if (!outfile.is_open()) {
        cerr << "No se pudo abrir el archivo 'Resultados.txt' para escribir." << endl;
        return 1;
    }

    int rowsA, colsA, rowsB, colsB;

    infile >> rowsA >> colsA;
    vector<vector<int>> matrizA(rowsA, vector<int>(colsA));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            infile >> matrizA[i][j];
        }
    }

    infile >> rowsB >> colsB;
    vector<vector<int>> matrizB(rowsB, vector<int>(colsB));

    // Read matrix B
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            infile >> matrizB[i][j];
        }
    }

    if (colsA != rowsB) {
        cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación." << endl;
        return 1;
    }

    vector<vector<int>> resultado = MatrixMultOp(matrizA, matrizB);

    outfile << "Matriz A:" << endl;
    for (const auto& fila : matrizA) {
        for (int num : fila) {
            outfile << num << " ";
        }
        outfile << endl;
    }

    outfile << endl << "Matriz B:" << endl;
    for (const auto& fila : matrizB) {
        for (int num : fila) {
            outfile << num << " ";
        }
        outfile << endl;
    }

    outfile << endl << "Resultado de la multiplicación:" << endl;
    for (const auto& fila : resultado) {
        for (int num : fila) {
            outfile << num << " ";
        }
        outfile << endl;
    }

    infile.close();
    outfile.close();

    cout << "La multiplicación de matrices ha sido escrita en 'Resultados.txt'." << endl;

    return 0;
}

