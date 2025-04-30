#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace std::chrono;

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

void merge(int* src, int* dest, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        dest[k++] = (src[i] <= src[j]) ? src[i++] : src[j++];
    }
    while (i < mid) dest[k++] = src[i++];
    while (j < right) dest[k++] = src[j++];
}

void merge_sort_v(int* array, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp) {
        perror("malloc failed");
        return;
    }

    int* src = array;
    int* dest = temp;

    for (int width = 1; width < size; width *= 2) {
        for (int i = 0; i < size; i += 2 * width) {
            int left = i;
            int mid = (i + width < size) ? i + width : size;
            int right = (i + 2 * width < size) ? i + 2 * width : size;
            merge(src, dest, left, mid, right);
        }

        int* tmp = src;
        src = dest;
        dest = tmp;
    }

    if (src != array) {
        for (int i = 0; i < size; ++i)
            array[i] = src[i];
    }

    free(temp);
}

void localHeapSort(int* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        localHeapSort(arr, n, largest);
    }
}

void heapsort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        localHeapSort(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        localHeapSort(arr, i, 0);
    }
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        int pivotIndex = left;
        if (arr[mid] < arr[left])
            pivotIndex = mid;
        if (arr[right] < arr[pivotIndex])
            pivotIndex = right;
        swap(arr[pivotIndex], arr[right]);

        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]);
        int pivotIndexNew = i + 1;

        if (pivotIndexNew - 1 < right - pivotIndexNew) {
            quickSort(arr, left, pivotIndexNew - 1);
            quickSort(arr, pivotIndexNew + 1, right);
        }
        else {
            quickSort(arr, pivotIndexNew + 1, right);
            quickSort(arr, left, pivotIndexNew - 1);
        }
    }
}

void MemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB\n"
            << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024  << " KB\n"
            << "Pagefile Usage: " << pmc.PagefileUsage / 1024<< " KB\n" << endl;
    }
}

template <typename T>
void compositeSort(T& arr, int size) {
    if (size <= 10) {
        insertionSort(arr.data(), size);
    }
    else if (size < 1000 && size > 10) {
        heapsort(arr.data(), size);
    }
    else {
        quickSort(arr, 0, size - 1);
    }
}

int main() {
    srand(time(0));

    vector<int> sizes = { 50, 500, 1000, 3000, 5000, 10000 };

    for (int n : sizes) {
        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % 10000;
        }

        auto start = high_resolution_clock::now();
        compositeSort(arr, n);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "n = " << n << endl << "Composite Sort time: " << duration.count() << " microseconds" << endl;
        MemoryUsage();
    }

    return 0;
}
