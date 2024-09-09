#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

//Función que ordena usando el algoritmo Insertion Sort.
void insertionSort(vector<int>& arr, int n){
    for(int i = 1; i < n; ++i){
        int insert = arr[i]; // Elemento actual a colocar en la posición correcta.
        int j = i - 1;

        // Mueve los elementos mayores que 'insert' una posición a la derecha.
        while(j >= 0 && arr[j] > insert){
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = insert; // Inserta en la posición correcta.
    }
}

int main(){
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
    insertionSort(arr, size); // Llama a la función de ordenamiento.
    // Toma el tiempo de finalización de la ordenación.
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    // Calcula el tiempo transcurrido durante la ordenación.
    chrono::duration<double> elapsed_seconds = end - begin;

    cout << "Insertionsort complete, elapsed time: " << elapsed_seconds.count() << " seconds." << endl;

    // Crea un archivo para guardar el resultado del ordenamiento.
    ofstream resultado("insertionsort_" + filename);
    // Escribe los elementos ordenados en el archivo.
    for(long unsigned int i = 0; i < size; i++){
        resultado << arr[i] << endl;
    }
    resultado.close(); // Cierra el archivo de salida.
    return 0;
}
