#include <iostream>
#include <vector>

using namespace std;

void printArray(const vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i];
        if (i == arr.size() - 1) {
            cout << "";
        } else {
            cout << " ";
        }
    }
    cout << endl;
}

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int lomutoPartition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // El último elemento es el pivote
    int i = low;          

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    // Colocamos el pivote en su posición correcta central
    swap(arr[i], arr[high]);
    
    return i; // Retorna la posición final del pivote
}

// Función recursiva de Quicksort
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // Ejecuta la partición de Lomuto pura
        int p = lomutoPartition(arr, low, high);
        
        printArray(arr);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    quickSort(arr, 0, n - 1);

    return 0;
}