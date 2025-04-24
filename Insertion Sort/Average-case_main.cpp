#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>  
#include <psapi.h>    

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

void RandomNum(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001;
    }
}

void MemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB" << endl;
}

int main() {
    int sizes[] = {500, 1000, 2000, 3000, 4000, 5000}; 
    for (int n : sizes) {
        int* arr = new int[n]; 
        
        srand(time(0));

        RandomNum(arr, n);

        cout << "\nSorting array of size " << n << endl;

        clock_t start = clock();
        insertionSort(arr, n);
        clock_t end = clock();

        double duration = double(end - start) / CLOCKS_PER_SEC;
        cout << "Sorting time "<< ": " << duration << " seconds." << endl;

        MemoryUsage();

        delete[] arr;
    }

    return 0;
}
