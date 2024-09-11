#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
        
/*
 * Función que implementa el algoritmo de ordenamiento Bubble Sort.
 * @param array_elementos: Vector de enteros que se desea ordenar.
 * @return: El vector ordenado.
 */
vector<int> BubbleSort(vector<int> &array_elementos) {
    int n = array_elementos.size(); // Obtiene el tamaño del vector.
    bool swapped; // Variable para indicar si se realizó algún intercambio en la pasada actual.
    
    // Ciclo exterior que controla el número de iteraciones.
    for (int a = 0; a < n - 1; a++) {
        swapped = false;
        
        // Ciclo interior que compara los elementos.
        for (int b = 0; b < n - 1 - a; b++) {
            if (array_elementos[b] > array_elementos[b + 1]) {
                swap(array_elementos[b], array_elementos[b + 1]);
                swapped = true; 
            }
        }
        
        // Si no hubo intercambios en la pasada actual, el vector ya está ordenado.
        if (!swapped) break;
    }
    
    return array_elementos;
}

int main() {
    ifstream infile("dataset.txt");
    ofstream outfile("OrdenadasBubble.txt");

    if (!infile.is_open()) {
        cerr << "No se pudo abrir el archivo para leer." << endl;
        return 1;
    }

    if (!outfile.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return 1;
    }

    std::chrono::duration<double, milli> duracion;
    string line;
    getline(infile, line);
    vector<int> lista;
    istringstream ss(line);
    int number;

    while (ss >> number) {
        lista.push_back(number);
    }

    auto start = high_resolution_clock::now();
    lista=BubbleSort(lista);
    auto end = high_resolution_clock::now();
    
    duracion = end - start;

    for (const auto& elemento : lista) {
        outfile << elemento << " ";
    }

    std::cout <<duracion.count()<< endl;

    infile.close();
    outfile.close();
    
    return 0;
}