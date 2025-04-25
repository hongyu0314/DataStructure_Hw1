# Quick Sort

## 解題說明

本題要求實現一個快速排序法，以最快的時間去排序出結果，求出Worst-case和Average-case的排序時間和空間複雜度。

### 解題策略

1. Worst-case 的整數變數產生使用逆序排列的數字。

2. Average-case 的整數變數產生使用隨機亂數(範圍在0~9999)。

3. 計算運行時間使用 std::chrono 測量排序時間。

4. 依記憶體的使用量推敲出空間複雜度 

## 程式實作

以下為Worst-case的程式碼：

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

void quickSort(vector<int> arr, int left, int right) {
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

vector<int> WorstCase(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }
    return arr;
}

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 / 1024 << " MB\n"
             << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 / 1024 << " MB\n"
             << "Pagefile Usage: " << pmc.PagefileUsage / 1024 / 1024 << " MB\n" << endl;
    }
}

int main() {
    srand(time(0));

    vector<int> sizes = { 500, 1000 , 2000, 3000, 4000, 5000};

    for (int n : sizes) {
        vector<int> arr = WorstCase(n);

        auto start = high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "n = " << n << endl << "Worst-case time : " << duration.count() << " microseconds\n";
        printMemoryUsage();
    }
    return 0;
}
```
以下為Average-case的程式碼：

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

void quickSort(vector<int> arr, int left, int right) {
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

vector<int> Random(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

void printMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        cout << "Working Set Size: " << pmc.WorkingSetSize / 1024 / 1024 << " MB\n"
             << "Peak Working Set Size: " << pmc.PeakWorkingSetSize / 1024 / 1024 << " MB\n"
             << "Pagefile Usage: " << pmc.PagefileUsage / 1024 / 1024 << " MB\n" << endl;
    }
}

int main() {
    srand(time(0));

    vector<int> sizes = { 500, 1000, 2000, 3000, 4000, 5000 };

    for (int n : sizes) {
        vector<int> arr = Random(n);

        auto start = high_resolution_clock::now();
        quickSort(arr, 0, arr.size() - 1);
        auto end = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(end - start);
        cout << "n = " << n << endl << "Average-case time: " << duration.count() << " microseconds" << endl;
        printMemoryUsage();
    }
    return 0;
}
```
## 效能分析

1. 
    Worst-case:

     時間複雜度： $O(n²)$。
 
     空間複雜度： $O(n)$。
2. 
   Average-case：

     時間複雜度： $O(nlogn)$。
 
     空間複雜度： $O(logn)$。


## 測試與驗證

### 測試案例

| 測試案例 | 參數個數 $n$ | Average-case所耗時間 | Worst-case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 788 microseconds | 3703 microseconds |
| 測試二   | $n = 1000$      | 1621 microseconds | 13140 microseconds | 
| 測試三   | $n = 2000$      | 3994 microseconds | 20198 microseconds |
| 測試四   | $n = 3000$      | 7787 microseconds | 37154 microseconds |
| 測試五   | $n = 4000$      | 10081 microseconds | 51879 microseconds |
| 測試六   | $n = 5000$      | 55659 microseconds | 83206 microseconds |

## 申論及開發報告

### 在本程式中，使用快速排序法的主要原因如下：

1.  **簡單易懂**

      插入排序的邏輯簡單，容易實作和理解。


2. **處理小資料時效率較高**

     對於小型陣列，插入排序表現較好。其時間複雜度在最好的情況下是 $O(n)$ ，當陣列部分已經排序時，用插入排序時就會很快。

3. **穩定性**

     插入排序是一個穩定的排序方式，當有一樣的東西，排序後它們的順序不會改變。

### 插入排序法的缺點如下：

1. **不適合處理很多的資料**

     由於 $O(n²)$ 的時間複雜度，插入排序在處理很多資訊（例如數十萬或數百萬個資料）時效能會明顯下降，因此對大型資料的處理並不高效。

2. **交換次數多**

     在最壞情況下，插入排序需要大量的資料交換，尤其是在資料完全相反時的情況下。
