# Insertion Sort

## 解題說明

本題要求實現一個插入排序法，以最好的時間/空間複雜度去排序，求出Worst-case的排序時間和Average-case的排序時間。

### 解題策略

1. Worst-case 的整數變數產生使用 n, n-1, n-2, ...... ,1。

2. Average-case 的整數變數產生使用隨機亂數(範圍在0~1000)。

3. 計算運行時間使用 clock( ) 測量排序時間。

## 程式實作

以下為Worst-case的程式碼：

```cpp
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
```
以下為Average-case的程式碼：

```cpp
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

void RandomNum(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1001;
    }
}

int main() {
    int n = 500;
    int arr[n];

    srand(time(0));
    RandomNum(arr, n);

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


## 測試與驗證

### 測試案例

| 測試案例 | 參數個數 $n$ | Average-case所耗時間 | Worst-case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 0.000161 seconds | 0.000418 seconds |
| 測試二   | $n = 1000$      | 0.000639 seconds | 0.001944 seconds | 
| 測試三   | $n = 2000$      | 0.002534 seconds | 0.007495 seconds |
| 測試四   | $n = 3000$      | 0.006434 seconds | 0.016573 seconds |
| 測試五   | $n = 4000$      | 0.011112 seconds | 0.029255 seconds |
| 測試六   | $n = 5000$      | 0.019719 seconds | 0.037256 seconds |

## 申論及開發報告

### 在本程式中，使用插入排序法的主要原因如下：

1. 簡單易懂：插入排序的邏輯簡單，容易實作和理解。

2. 處理小資料時效率較高：對於小型陣列，插入排序表現較好。其時間複雜度在最好的情況下是 $O(n)$ ，當陣列部分已經排序時，用插入排序時就會很快。

3. 穩定性：插入排序是一個穩定的排序方式，當有一樣的東西，排序後它們的順序不會改變。

### 而插入排序法的缺點如下：

1. 不適合處理極大的資料：由於 $O(n²)$ 的時間複雜度，插入排序在處理很多資訊（例如數十萬或數百萬個資料）時效能會明顯下降，因此對大型資料的處理並不高效。

2. 交換次數多：在最壞情況下，插入排序需要大量的資料交換，尤其是在資料完全相反時的情況下。
