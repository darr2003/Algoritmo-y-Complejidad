#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

/*
 * Función que selecciona una mediana de tres elementos para usar como pivote en el algoritmo de QuickSort.
 * @param arr: Vector de enteros que se está ordenando.
 * @param low: Índice inicial del rango de elementos a considerar.
 * @param high: Índice final del rango de elementos a considerar.
 * @return: El valor del pivote seleccionado.
 */
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;

    if (arr[low] > arr[mid])
        swap(arr[low], arr[mid]);
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);
    if (arr[mid] > arr[high])
        swap(arr[mid], arr[high]);

    swap(arr[mid], arr[high]);
    return arr[high];
}

/*
 * Función que particiona el vector alrededor de un pivote para el algoritmo de QuickSort.
 * @param arr: Vector de enteros que se está ordenando.
 * @param low: Índice inicial del rango de elementos a considerar.
 * @param high: Índice final del rango de elementos a considerar.
 * @return: El índice de la posición del pivote después de la partición.
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
  
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

/*
 * Función que ordena un vector de enteros usando el algoritmo de QuickSort.
 * @param arr: Vector de enteros que se desea ordenar.
 * @param low: Índice inicial del rango de elementos a ordenar.
 * @param high: Índice final del rango de elementos a ordenar.
 */
void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    ifstream infile("dataset.txt");
    ofstream outfile("OrdenadasQuicksort.txt");

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
    quickSort(lista, 0 , lista.size()-1);
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