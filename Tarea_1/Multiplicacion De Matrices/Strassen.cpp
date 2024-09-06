#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

void dividirMatriz(const vector<vector<int>>& A, vector<vector<int>>& A11, vector<vector<int>>& A12, vector<vector<int>>& A21, vector<vector<int>>& A22) {
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

vector<vector<int>> combinarMatrices(const vector<vector<int>>& A11, const vector<vector<int>>& A12, const vector<vector<int>>& A21, const vector<vector<int>>& A22) {
    int n = A11.size() * 2;
    vector<vector<int>> C(n, vector<int>(n));
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

vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C;
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }
    if (n == 2) {
        vector<vector<int>> temp(2, vector<int>(2));
        temp[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
        temp[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
        temp[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
        temp[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
        return temp;
    }

    vector<vector<int>> A11(n / 2, vector<int>(n / 2)), A12(n / 2, vector<int>(n / 2)),
                        A21(n / 2, vector<int>(n / 2)), A22(n / 2, vector<int>(n / 2)),
                        B11(n / 2, vector<int>(n / 2)), B12(n / 2, vector<int>(n / 2)),
                        B21(n / 2, vector<int>(n / 2)), B22(n / 2, vector<int>(n / 2)),
                        M1(n / 2, vector<int>(n / 2)), M2(n / 2, vector<int>(n / 2)),
                        M3(n / 2, vector<int>(n / 2)), M4(n / 2, vector<int>(n / 2)),
                        M5(n / 2, vector<int>(n / 2)), M6(n / 2, vector<int>(n / 2)),
                        M7(n / 2, vector<int>(n / 2)),
                        temp1(n / 2, vector<int>(n / 2)), temp2(n / 2, vector<int>(n / 2));

    dividirMatriz(A, A11, A12, A21, A22);
    dividirMatriz(B, B11, B12, B21, B22);

    temp1 = sumarMatrices(A11, A22);
    temp2 = sumarMatrices(B11, B22);
    M1=strassen(temp1, temp2);

    temp1 = sumarMatrices(A21, A22);
    M2=strassen(temp1, B11);

    temp1 = restarMatrices(B12, B22);
    M3=strassen(A11, temp1);

    temp1 = restarMatrices(B21, B11);
    M4=strassen(A22, temp1);

    temp1 = sumarMatrices(A11, A12);
    M5=strassen(temp1, B22);

    temp1 = restarMatrices(A21, A11);
    temp2 = sumarMatrices(B11, B12);
    M6=strassen(temp1, temp2);

    temp1 = restarMatrices(A12, A22);
    temp2 = sumarMatrices(B21, B22);
    M7=strassen(temp1, temp2);

    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    C = combinarMatrices(C11, C12, C21, C22);
    return C;
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

    if (colsA != rowsB || colsA!=colsB || colsA!=rowsA) {
        cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación." << endl;
        return 1;
    }

    vector<vector<int>> resultado = strassen(matrizA, matrizB);

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

