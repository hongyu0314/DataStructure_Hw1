#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

template <class T>
void printArray(T* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void insertionSort(T* arr, int size) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void WorstCaseNum(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

int main() {
    int n = 500;
    int arr[n]; 

    srand(time(0));

    WorstCaseNum(arr, n);

    cout << "Before sorting: \n";
    printArray(arr, n);

    clock_t start = clock(); 
    insertionSort(arr, n); 
    clock_t end = clock(); 

    cout << "\nAfter sorting: \n";
    printArray(arr, n); 

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Sorting time: " << duration << " seconds." << endl;
    
    return 0;
}
