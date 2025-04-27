#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

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

void quickSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int pivot = arr[right];
        int i = left - 1;
        for (int j = left; j < right; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[right]);
        int pivotIndex = i + 1;

        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
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
        localHeapSort (arr, i, 0);
    }
}

vector<int> RandomNum(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int main() {
    srand(time(0));

    vector<int> sizes = {100, 500, 1000, 2000, 5000, 10000};

    cout << "Sorting times for each algorithm (in microseconds):" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "n\t\tInsertionSort\tQuickSort\tMergeSort\tHeapSort" << endl;

    for (int n : sizes) {
        vector<int> arr1 = RandomNum(n);
        vector<int> arr2 = arr1;
        vector<int> arr3 = arr1;
        vector<int> arr4 = arr1;

        auto start = high_resolution_clock::now();
        insertionSort<int>(arr1.data(), n);
        auto end = high_resolution_clock::now();
        double insertionTime = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        quickSort(arr2, 0, n - 1);
        end = high_resolution_clock::now();
        double quickSortTime = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        merge_sort_v(arr3.data(), n);
        end = high_resolution_clock::now();
        double mergeSortTime = duration_cast<microseconds>(end - start).count();

        start = high_resolution_clock::now();
        heapsort(arr4.data(), n);
        end = high_resolution_clock::now();
        double heapSortTime = duration_cast<microseconds>(end - start).count();

        cout << n << "\t\t" << insertionTime << "\t\t" << quickSortTime << "\t\t" << mergeSortTime << "\t\t" << heapSortTime << endl;
    }

    return 0;
}
