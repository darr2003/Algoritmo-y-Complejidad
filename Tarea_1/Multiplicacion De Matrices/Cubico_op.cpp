#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

using matrix=vector<vector<int>>;


/*
 * Función para imprimir una matriz en un archivo de salida.
 * @param outfile: Archivo de salida.
 * @param matrix: Matriz a imprimir.
 * @param matrixName: Nombre de la matriz a imprimir.
 */
void printMatrix(ofstream& outfile, const matrix& matrix, const string& matrixName) {
    outfile << matrixName << ":" << endl;
    for (const auto& row : matrix) {
        for (int num : row) {
            outfile << num << " ";
        }
        outfile << endl;
    }
    outfile << endl;
}

/*
 * Función para transponer una matriz.
 * @param B: Matriz que se desea transponer.
 * @return: Matriz transpuesta.
 */
matrix TMatrix(const matrix& B) {
    int rows = B.size();
    int cols = B[0].size();
    matrix t(cols, vector<int>(rows));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            t[j][i] = B[i][j];
        }
    }
    return t;
}

/*
 * Función para multiplicar dos matrices transponiendo la segunda matriz.
 * @param a: Primera matriz.
 * @param b: Segunda matriz.
 * @return: Resultado de la multiplicación de las matrices.
 */
matrix MatrixMult(const matrix& a, const matrix& b) {
    matrix bT = TMatrix(b);
    matrix c(a.size(), vector<int>(bT.size(), 0));

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)bT.size(); j++) {
            for (int k = 0; k < (int)a[0].size(); k++) { 
                c[i][j] += a[i][k] * bT[j][k];
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

    ofstream outfile("RCubicoOp.txt");  
    if (!outfile.is_open()) {
        cerr << "No se pudo abrir el archivo 'RCubicoOp.txt' para escribir." << endl;
        return 1;
    }

    int rowsA, colsA, rowsB, colsB;

    infile >> rowsA >> colsA;
    matrix matrizA(rowsA, vector<int>(colsA));

    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            infile >> matrizA[i][j];
        }
    }

    infile >> rowsB >> colsB;
    matrix matrizB(rowsB, vector<int>(colsB));

    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            infile >> matrizB[i][j];
        }
    }

    if (colsA != rowsB) {
        cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación." << endl;
        return 1;
    }


    auto start = high_resolution_clock::now();
    matrix resultado = MatrixMult(matrizA, matrizB);
    auto end = high_resolution_clock::now();
    
    std::chrono::duration<double, milli> duracion = end - start;

    std::cout << duracion.count() << endl;

    printMatrix(outfile, matrizA, "Matriz A");
    printMatrix(outfile, matrizB, "Matriz B");
    printMatrix(outfile, resultado, "Resultado de la multiplicación");

    infile.close();
    outfile.close();

    return 0;
}
