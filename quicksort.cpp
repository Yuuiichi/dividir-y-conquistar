#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

// Función para encontrar la mediana de tres elementos (primero, medio y último)
int medianaDeTres(vector<int>& arr, int low, int high){
    int mid = low + (high - low) / 2; // Calcula el índice del elemento medio.
    // Ordena los elementos arr[low], arr[mid], y arr[high].
    if(arr[low] > arr[mid]){
        swap(arr[low], arr[mid]);
    }
    if(arr[low] > arr[high]){
        swap(arr[low], arr[high]);
    }
    if(arr[mid] > arr[high]){
        swap(arr[mid], arr[high]);
    }
    return mid;  // Retorna el índice del pivote mediano.
}

// Función de partición que reorganiza los elementos alrededor del pivote, esta función es parte de Quicksort.
int partition(vector<int>& arr, int low, int high){
    // Selecciona la mediana de tres como el pivote.
    int median = medianaDeTres(arr, low, high);
    swap(arr[median], arr[high]); // Mueve el pivote al final del subarreglo.

    int pivot = arr[high]; // Elige el pivote.
    int i = low - 1;       // Índice del elemento más pequeño.

    // Recorre el subarreglo y mueve los elementos menores al pivote a la izquierda.
    for(int j = low; j <= high - 1; j++){
        if(arr[j] < pivot){
            i++;
            swap(arr[i], arr[j]); // Intercambia el elemento más pequeño encontrado con el elemento actual.
        }
    }

    // Mueve el pivote a su posición correcta.
    swap(arr[i + 1], arr[high]);
    return i + 1; // Retorna la posición del pivote.
}

// Función que ordena usando el algoritmo Quick Sort.
void quickSort(vector<int>& arr, int low, int high){
    if(low < high){
        int pi = partition(arr, low, high); // Particiona el subarreglo y obtiene el índice del pivote.
        quickSort(arr, low, pi - 1);        // Llama recursivamente para ordenar la parte izquierda del pivote.
        quickSort(arr, pi + 1, high);       // Llama recursivamente para ordenar la parte derecha del pivote.
    }
}

int main(){
    vector<int> arr; // Vector para almacenar los datos a ordenar.
    string filename = "dataset_Random_200000.txt", line; // Nombre del archivo y variable para leer las líneas.
    ifstream file(filename); // Abre el archivo para lectura.
    
    // Lee cada línea del archivo, convierte a entero y la agrega al vector.
    while (file >> line) {
        arr.push_back(stoi(line));
    }
    file.close(); // Cierra el archivo de entrada.

    long unsigned int size = arr.size(); // Tamaño del vector.

    cout << "Sorting...\n";

    // Toma el tiempo de inicio de la ordenación.
    chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    quickSort(arr, 0, size - 1); // Llama a la función de ordenamiento QuickSort.
    // Toma el tiempo de finalización de la ordenación.
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    // Calcula el tiempo transcurrido durante la ordenación.
    chrono::duration<double> elapsed_seconds = end - begin;

    // Imprime el tiempo transcurrido.
    cout << "Quicksort complete, elapsed time: " << elapsed_seconds.count() << " seconds." << endl;

    // Abre un archivo para guardar el resultado del ordenamiento.
    ofstream resultado("quicksort_" + filename);
    // Escribe los elementos ordenados en el archivo.
    for (long unsigned int i = 0; i < size; i++) {
        resultado << arr[i] << endl;
    }
    resultado.close(); // Cierra el archivo de salida.

    return 0;
}
