# Composite Sort

## 解題說明

本題要求找出在各個 n 時，哪個排序法最快 Time Comparison (以表格等形式呈現)，並寫一個結合多種排序法的函式 (Composite Sort)，可以對應不同輸入資料，在最短的時間內完成排序。

### 解題策略

1. 小於等於 100 個資料時使用Insertion sort。

2. 小於等於 1000 且大於100 個資料時使用Heap sort。

3. 大於 1000 個資料時使用Ｑuick sort。

4. 計算運行時間使用 std::chrono 測量排序時間。  

## 程式實作

以下為Time Comparison的程式碼：
```cpp
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
        } else {
            quickSort(arr, pivotIndexNew + 1, right);
            quickSort(arr, left, pivotIndexNew - 1);
        }
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

    vector<int> sizes = {50, 500, 1000, 3000, 5000, 10000};

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
```
以下為Composite Sort的程式碼：

```cpp
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

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < leftArr.size() && j < rightArr.size()) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k++] = leftArr[i++];
            }
            else {
                arr[k++] = rightArr[j++];
            }
        }

        while (i < leftArr.size()) {
            arr[k++] = leftArr[i++];
        }
        while (j < rightArr.size()) {
            arr[k++] = rightArr[j++];
        }
    }
}

template <typename T>
void compositeSort(T& arr, int size) {
    if (size <= 100) {
        insertionSort(arr.data(), size);
        cout<<"Using Insertion sort"<<endl;
    }
    else if (size <= 1000) {
        heapsort(arr.data(), size);
        cout<<"\nUsing Heap sort"<<endl;
    }
    else {
        quickSort(arr, 0, size - 1);
        cout<<"\nUsing Quick sort"<<endl;
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

int main() {
    srand(time(0));

    vector<int> sizes = { 100, 500, 1000, 3000, 5000, 10000 };

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
```
## 效能分析

1. Insertion Sort:

   時間複雜度： $O(n^2)$

   空間複雜度： $O(1)$

2. Quick Sort:

   時間複雜度： $O(nlogn)$

   空間複雜度： $O(logn)$
   
3. Merge sort:

   時間複雜度： $O()$

   空間複雜度： $O()$

4. Heap Sort:

   時間複雜度： $O(nlogn)$

   空間複雜度： $O(1)$
    

## 測試與驗證

### Time Comparison測試案例

| 測試案例 | 參數個數 $n$ | Insertion Sort所耗時間 | Quick Sort所耗時間 | Merge Sort所耗時間 | Heap Sort所耗時間 |
|----------|--------------|----------|----------|----------|----------|
| 測試一   | $n = 50$      | 2 microseconds | 4 microseconds | 3 microseconds | 6 microseconds |
| 測試二   | $n = 500$      | 195 microseconds | 71 microseconds | 38 microseconds | 108 microseconds | 
| 測試三   | $n = 1000$      | 677 microseconds | 176 microseconds | 91 microseconds | 219 microseconds |
| 測試四   | $n = 3000$      | 6567 microseconds | 679 microseconds | 341 microseconds | 842 microseconds |
| 測試五   | $n = 5000$      | 16612 microseconds | 966 microseconds | 488 microseconds | 1337 microseconds |
| 測試六   | $n = 10000$      | 63314 microseconds | 2079 microseconds | 1006 microseconds | 2879 microseconds |

![output](https://github.com/user-attachments/assets/e5ce1243-08bc-4d3b-9dea-c9bf2a6b35dd)


## 申論及開發報告

### 在本程式中，使用了結合多種排序法的主要原因如下：

  **選擇最快的排序方式:**
    
   可以針對輸入的資料量來用最快的排序法來做排序。
 
