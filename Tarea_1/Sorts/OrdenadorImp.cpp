#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include <bits/stdc++.h> 

using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

int main() {
    ifstream infile("datasetDesordenado.txt");
    ofstream outfile("OrdenadasBubble.txt");
    std::chrono::duration<double, milli> duracion;

    if (!infile.is_open()) {
    cerr << "No se pudo abrir el archivo 'datasetDesordenado.txt' para leer." << endl;
    return 1;
    }

    if (!outfile.is_open()) {
    cerr << "No se pudo abrir el archivo 'OrdenadasBubble.txt' para escribir." << endl;
    return 1;
    }

    string line;
    getline(infile, line);
    vector<int> lista;
    stringstream ss(line);
    int number;

    while (ss >> number) {
    lista.push_back(number);
    }

    auto start = high_resolution_clock::now();
    std::sort(lista.begin(), lista.end());
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