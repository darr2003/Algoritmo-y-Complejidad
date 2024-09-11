#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <math.h>

using namespace std;
using matrix=vector<vector<int>>;


using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

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
 * Funcion que calcula la siguiente potencia de 2
 * @param x: Valor que calcula la siguiente potencia de 2
 * @return: siguiente potencia de 2.
 */
int nextPowerOfTwo(int x) {
    return pow(2, ceil(log2(x)));
}

/*
 * Función que ajusta una matriz para que sea de tamaño potencia de dos,
 * rellenando los espacios adicionales con ceros.
 * @param mat: Matriz original que se desea rellenar.
 * @return: Matriz ajustada con ceros.
 */
matrix padMatrix(const matrix& mat) {
    int n = mat.size();
    int m = mat[0].size();
    int newSize = nextPowerOfTwo(max(n, m));
    matrix padded(newSize, vector<int>(newSize, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            padded[i][j] = mat[i][j];
        }
    }
    return padded;
}

/*
 * Función que elimina el relleno de una matriz ajustada a potencia de dos,
 * devolviéndola a su tamaño original.
 * @param mat: Matriz ajustada.
 * @param originalRows: Número de filas de la matriz original.
 * @param originalCols: Número de columnas de la matriz original.
 * @return: Matriz con el tamaño original.
 */
matrix removePadding(const matrix& mat, int originalRows, int originalCols) {
    matrix result(originalRows, vector<int>(originalCols));
    for (int i = 0; i < originalRows; ++i) {
        for (int j = 0; j < originalCols; ++j) {
            result[i][j] = mat[i][j];
        }
    }
    return result;
}

/*
 * Función que suma dos matrices.
 * @param A: Primera matriz.
 * @param B: Segunda matriz.
 * @return: Matriz resultante de la suma de A y B.
 */
matrix sumarMatrices(const matrix& A, const matrix& B) {
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

/*
 * Función que resta dos matrices.
 * @param A: Primera matriz.
 * @param B: Segunda matriz.
 * @return: Matriz resultante de la resta de A y B.
 */
matrix restarMatrices(const matrix& A, const matrix& B) {
    int n = A.size();
    matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

/*
 * Función que divide una matriz en cuatro submatrices.
 * @param A: Matriz a dividir.
 * @param A11: Submatriz superior izquierda.
 * @param A12: Submatriz superior derecha.
 * @param A21: Submatriz inferior izquierda.
 * @param A22: Submatriz inferior derecha.
 */
void dividirMatriz(const matrix& A, matrix& A11, matrix& A12, matrix& A21, matrix& A22) {
    int n = A.size();
    int m = n / 2;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + m];
            A21[i][j] = A[i + m][j];
            A22[i][j] = A[i + m][j + m];
        }
    }
}

/*
 * Función que combina cuatro submatrices en una matriz más grande.
 * @param A11: Submatriz superior izquierda.
 * @param A12: Submatriz superior derecha.
 * @param A21: Submatriz inferior izquierda.
 * @param A22: Submatriz inferior derecha.
 * @return: Matriz combinada a partir de las submatrices.
 */
matrix combinarMatrices(const matrix& A11, const matrix& A12, const matrix& A21, const matrix& A22) {
    int n = A11.size() * 2;
    matrix C(n, vector<int>(n));
    int m = A11.size();
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; ++j) {
            C[i][j] = A11[i][j];
            C[i][j + m] = A12[i][j];
            C[i + m][j] = A21[i][j];
            C[i + m][j + m] = A22[i][j];
        }
    }
    return C;
}

/*
 * Implementación del algoritmo de Strassen para multiplicación de matrices.
 * @param A: Primera matriz.
 * @param B: Segunda matriz.
 * @return: Matriz resultante de la multiplicación de A y B.
 */
matrix strassen(const matrix& A, const matrix& B) {
    int n = A.size();
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    if (n == 2) {
        matrix temp(2, vector<int>(2));
        temp[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        temp[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        temp[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        temp[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
        return temp;
    }

    matrix A_padded = padMatrix(A);
    matrix B_padded = padMatrix(B);
    int newSize = A_padded.size();

    matrix A11(newSize / 2, vector<int>(newSize / 2)), A12(newSize / 2, vector<int>(newSize / 2)),
                        A21(newSize / 2, vector<int>(newSize / 2)), A22(newSize / 2, vector<int>(newSize / 2)),
                        B11(newSize / 2, vector<int>(newSize / 2)), B12(newSize / 2, vector<int>(newSize / 2)),
                        B21(newSize / 2, vector<int>(newSize / 2)), B22(newSize / 2, vector<int>(newSize / 2)),
                        M1(newSize / 2, vector<int>(newSize / 2)), M2(newSize / 2, vector<int>(newSize / 2)),
                        M3(newSize / 2, vector<int>(newSize / 2)), M4(newSize / 2, vector<int>(newSize / 2)),
                        M5(newSize / 2, vector<int>(newSize / 2)), M6(newSize / 2, vector<int>(newSize / 2)),
                        M7(newSize / 2, vector<int>(newSize / 2));

    dividirMatriz(A_padded, A11, A12, A21, A22);
    dividirMatriz(B_padded, B11, B12, B21, B22);

    auto temp1 = sumarMatrices(A11, A22);
    auto temp2 = sumarMatrices(B11, B22);
    M1 = strassen(temp1, temp2);

    M2 = strassen(sumarMatrices(A21, A22), B11);
    M3 = strassen(A11, restarMatrices(B12, B22));
    M4 = strassen(A22, restarMatrices(B21, B11));
    M5 = strassen(sumarMatrices(A11, A12), B22);
    M6 = strassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    M7 = strassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    matrix C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    matrix C12 = sumarMatrices(M3, M5);
    matrix C21 = sumarMatrices(M2, M4);
    matrix C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    matrix C_padded = combinarMatrices(C11, C12, C21, C22);

    return removePadding(C_padded, A.size(), B[0].size());
}


int main() {
    ifstream infile("Input.txt"); 
    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo 'Input.txt' para leer." << endl;
        return 1;
    }

    ofstream outfile("RStrassen.txt");  
    if (!outfile.is_open()) {
        cerr << "No se pudo abrir el archivo 'RStrassen.txt' para escribir." << endl;
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
    
    auto start = high_resolution_clock::now();
    matrix resultado = strassen(matrizA, matrizB);
    auto end = high_resolution_clock::now();
    
    std::chrono::duration<double, milli> duracion = end - start;

    std::cout <<duracion.count()<< endl;

    printMatrix(outfile, matrizA, "Matriz A");
    printMatrix(outfile, matrizB, "Matriz B");
    printMatrix(outfile, resultado, "Resultado de la multiplicación");

    infile.close();
    outfile.close();

    return 0;
}