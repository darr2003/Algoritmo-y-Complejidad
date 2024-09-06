#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> MatrixMult(vector<vector<int>> a, vector<vector<int>> b) {
    vector<vector<int>> c(a.size(), vector<int>(b[0].size(), 0));
    
    if (a[0].size() != b.size()) {
        return {};
    }

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b[0].size(); j++) {
            for (int k = 0; k < (int)b.size(); k++) {
                c[i][j] += a[i][k] * b[k][j];
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

    vector<vector<int>> resultado = MatrixMult(matrizA, matrizB);

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

