#include <bits/stdc++.h> // Incluye todas las librerías estándar en C++, (en este caso se usará sort).
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    vector<int> arr; // Vector para almacenar los datos a ordenar.
    string filename = "dataset_Random_200000.txt", line; // Nombre del archivo y variable para leer las líneas.
    ifstream file(filename); // Abre el archivo para lectura.
    
    // Lee cada línea del archivo, convierte a entero y la agrega al vector.
    while(file >> line){
        arr.push_back(stoi(line));
    }
    file.close(); // Cierra el archivo de entrada.

    long unsigned int size = arr.size(); // Tamaño del vector.

    cout << "Sorting...\n";

    // Toma el tiempo de inicio de la ordenación.
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    sort(arr.begin(), arr.end()); // Llama a la función de ordenamiento sort().
    // Toma el tiempo de finalización de la ordenación.
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // Calcula el tiempo transcurrido durante la ordenación.
    chrono::duration<double> elapsed_seconds = end - begin;

    // Imprime el tiempo transcurrido.
    cout << "Sort complete, elapsed time: " << elapsed_seconds.count() << " seconds." << endl;

    // Abre un archivo para guardar el resultado del ordenamiento.
    ofstream resultado("sort_" + filename);
    
    // Escribe los elementos ordenados en el archivo.
    for(long unsigned int i = 0; i < size; i++){
        resultado << arr[i] << endl;
    }
    resultado.close(); // Cierra el archivo de salida.

    return 0;
}
