# Insertion Sort

## 解題說明

本題要求實現一個插入排序法，以最快的時間去排序出結果，求出Worst-case和Average-case的排序時間和空間複雜度。

### 解題策略

1. Worst-case 的整數變數產生使用 n, n-1, n-2, ...... ,1。

2. Average-case 的整數變數產生使用隨機亂數(範圍設在0~9999)。

3. 測量排序時間使用 std::chrono。

4. 依記憶體的使用量推敲出空間複雜度 

## 程式實作

以下為Worst-case的程式碼：

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h>  
#include <psapi.h>    

using namespace std;
using namespace std::chrono;

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

void MemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB\n" << endl;
}

int main() {
    int sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int n : sizes) {
        int* arr = new int[n];

        srand(time(0));

        WorstCaseNum(arr, n);

        cout << "n =  " << n << endl;

        auto start = high_resolution_clock::now();
        insertionSort(arr, n);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start); 
        cout << "Worst-case time " << ": " << duration.count() << " microseconds" << endl;

        MemoryUsage();

        delete[] arr;
    }

    return 0;
}

```
以下為Average-case的程式碼：

```cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
//#include <windows.h>  
//#include <psapi.h>    

using namespace std;
using namespace std::chrono;

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
        arr[i] = rand() % 10000;
    }
}

void MemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

    cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 << " KB" << endl;
    cout << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 << " KB" << endl;
    cout << "Pagefile Usage: " << pmc.PagefileUsage / 1024 << " KB\n" << endl;
}

int main() {
    int sizes[] = { 500, 1000, 2000, 3000, 4000, 5000 };
    for (int n : sizes) {
        int* arr = new int[n];

        srand(time(0));

        RandomNum(arr, n);

        cout << "n =  " << n << endl;

        auto start = high_resolution_clock::now();
        insertionSort(arr, n);
        auto end = high_resolution_clock::now(); 

        auto duration = duration_cast<microseconds>(end - start); 
        cout << "Average-case time " << ": " << duration.count() << " microseconds." << endl;

        MemoryUsage();

        delete[] arr;
    }

    return 0;
}
```
## 效能分析

1. 
    Worst-case:

     時間複雜度： $O(n²)$。
 
     空間複雜度： $O(1)$。
2. 
   Average-case：

     時間複雜度： $O(n²)$。
 
     空間複雜度： $O(1)$。

   **不需要額外的資料結構來存儲中間結果，它只是在原來的陣列上進行操作，因此空間複雜度是 $O(1)$。**


## 測試與驗證

### 測試案例

| 測試案例 | 參數個數 $n$ | Average-case所耗時間 | Worst-case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 262 microseconds | 497 microseconds |
| 測試二   | $n = 1000$      | 696 microseconds | 1962 microseconds | 
| 測試三   | $n = 2000$      | 2721 microseconds | 8785 microseconds |
| 測試四   | $n = 3000$      | 7718 microseconds | 43188 microseconds |
| 測試五   | $n = 4000$      | 13504 microseconds | 33950 microseconds |
| 測試六   | $n = 5000$      | 22764 microseconds | 48361 microseconds |

![output (2)](https://github.com/user-attachments/assets/337db611-2a87-4ece-bcaa-351d812ea73a)
## 申論及開發報告

### 在本程式中，使用插入排序法的主要原因如下：

1.  **簡單易懂**

      插入排序的邏輯簡單，容易實作和理解。


2. **處理小資料時效率較高**

     對於小型陣列，插入排序表現較好。時間複雜度在最好的情況是 $O(n)$ ，當陣列部分已經排序時，用插入排序時就會很快。

3. **穩定性**

     插入排序是一個穩定的排序方式，當有一樣的東西，排序後它們的順序不會改變。

### 插入排序法的缺點如下：

1. **不適合處理很多的資料**

     由於 $O(n²)$ 的時間複雜度，插入排序在處理很多資訊（例如數十萬或數百萬個資料）時效能會明顯下降，因此對大型資料的處理並不高效。

2. **交換次數多**

     在最壞情況下，插入排序需要大量的交換資料，尤其是在資料完全相反時的情況下。
