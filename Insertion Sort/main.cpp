#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

template <class T>
void Permute(T* arr, int n) {
    for (int i = n - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

template <class T>
void printArray(const T* arr, int size) {
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

int main() {
    int n = 10000;  // 測試據量為100
    vector<int> arr(n);

    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }

    srand(time(0));

    Permute(arr.data(), n);

    cout << "Before sorting: ";
    printArray(arr.data(), n);

    clock_t start = clock();
    insertionSort(arr.data(), n);
    clock_t end = clock();

    cout << "After sorting: ";
    printArray(arr.data(), n);

    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "Sorting time: " << duration << " seconds." << endl;

    return 0;
}

