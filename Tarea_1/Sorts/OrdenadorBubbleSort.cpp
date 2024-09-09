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
        
vector<int> BubbleSort(vector<int> &array_elementos) {
    int n = array_elementos.size();
    bool swapped;
    
    for (int a = 0; a < n - 1; a++) {
        swapped = false;
        
        for (int b = 0; b < n - 1 - a; b++) {
            if (array_elementos[b] > array_elementos[b + 1]) {
                swap(array_elementos[b], array_elementos[b + 1]);
                swapped = true;
            }
        }
        
        if (!swapped) break;
    }
    
    return array_elementos;
}

int main() {
    ifstream infile("datasetDesordenado.txt");
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