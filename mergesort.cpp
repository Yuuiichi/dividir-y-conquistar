#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
using namespace std;

// Función que mezcla dos subarreglos de 'arr[]', esta función es parte de Merge sort
void merge(vector<int>& arr, int left, int mid, int right){
    int n1 = mid - left + 1; // Tamaño del primer subarreglo.
    int n2 = right - mid;    // Tamaño del segundo subarreglo.

    // Crear vectores temporales para almacenar los subarreglos.
    vector<int> L(n1), R(n2);

    // Copiar datos a los vectores temporales L[] y R[].
    for(int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }
    for(int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0; // Índices iniciales de los vectores L y R.
    int k = left;     // Índice inicial del subarreglo mezclado.

    // Combinar los vectores temporales nuevamente en 'arr[left..right]'.
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){  // Comparar y mover el elemento más pequeño.
            arr[k] = L[i];
            i++;
        }else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay.
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay.
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función que ordena usando el algoritmo Merge Sort.
void mergeSort(vector<int>& arr, int left, int right){
    // Condición base: si el subarreglo tiene un solo elemento o está vacío.
    if(left >= right){
        return;
    }

    int mid = left + (right - left) / 2; // Calcula el punto medio para dividir el subarreglo.
    mergeSort(arr, left, mid);           // Ordena la primera mitad.
    mergeSort(arr, mid + 1, right);      // Ordena la segunda mitad.
    merge(arr, left, mid, right);        // Combina las dos mitades ordenadas.
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
    mergeSort(arr, 0, size - 1); // Llama a la función de ordenamiento Merge Sort.
    // Toma el tiempo de finalización de la ordenación.
    chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    
    // Calcula el tiempo transcurrido durante la ordenación.
    chrono::duration<double> elapsed_seconds = end - begin;

    // Imprime el tiempo transcurrido.
    cout << "Mergesort complete, elapsed time: " << elapsed_seconds.count() << " seconds." << endl;

    // Abre un archivo para guardar el resultado del ordenamiento.
    ofstream resultado("mergesort_" + filename);
    // Escribe los elementos ordenados en el archivo.
    for (long unsigned int i = 0; i < size; i++) {
        resultado << arr[i] << endl;
    }
    resultado.close(); // Cierra el archivo de salida.
    return 0;
}
