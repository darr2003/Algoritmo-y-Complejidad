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

#include <vector>

using namespace std;

vector<int> merge(vector<int> &izq, vector<int> &der){
    vector<int> result;
    auto itIzq = izq.begin();
    auto itDer = der.begin();

    while (itIzq != izq.end() && itDer != der.end()) {
        if (*itIzq <= *itDer) {
            result.push_back(*itIzq++);
        } else {
            result.push_back(*itDer++);
        }
    }

    // Añadir los elementos restantes de izq o der
    result.insert(result.end(), itIzq, izq.end());
    result.insert(result.end(), itDer, der.end());

    return result;
}

vector<int> mergeSort(vector<int> &entrada){
    if (entrada.size() <= 1){
        return entrada;
    }

    size_t medio = entrada.size() / 2;
    vector<int> izq(entrada.begin(), entrada.begin() + medio);
    vector<int> der(entrada.begin() + medio, entrada.end());

    izq = mergeSort(izq);
    der = mergeSort(der);

    return merge(izq, der);
}


int main() {
    ifstream infile("dataset.txt");
    ofstream outfile("OrdenadasMergesort.txt");

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
    lista=mergeSort(lista);
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