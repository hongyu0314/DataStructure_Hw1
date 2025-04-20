# Insertion Sort

## 解題說明

本題要求使用插入排序法，以最好的時間/空間複雜度去計算出排序所耗費時間，還有跟最差的情況去做比較。

### 解題策略

1. 使用template <class Ｔ>來處理任何資料型態。

2. 計算運行時間使用 clock( ) 測量排序時間。

3. 輸出結果為排序前與排序後的資料和排序資料所需的時間。

## 程式實作

以下為程式碼：

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
        arr[i] = rand();
    }
}

int main() {
    int n = 10;
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

1. 時間複雜度：程式的時間複雜度為 $O(n²)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| 測試案例 | 隨機參數 $n$ | 平均所耗時間 | worst-case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      |  4e-06 seconds  |   |
| 測試二   | $n = 1000$      |            |    | 
| 測試三   | $n = 2000$      |            |   |
| 測試四   | $n = 3000$      |            |   |
| 測試五   | $n = 4000$      |            |   |
| 測試六   | $n = 5000$      |            |   |

## 申論及開發報告

### 在本程式中，使用插入排序法的主要原因如下：

1. 簡單易懂：插入排序的邏輯非常簡單，容易實現和理解。

2. 處理小資料時效率較高：對於小型陣列，插入排序表現較好。其時間複雜度在最好的情況下是 O(n)，即當陣列部分已經排序時，用插入排序時就會很快。

3. 穩定性：插入排序是一個穩定的排序算法，當有一樣的東西，排序後它們的順序不會改變。

### 而插入排序法的缺點如下：

1. 不適合處理極大的資料：由於 O(n²) 的時間複雜度，插入排序在處理很多資訊（例如數十萬或數百萬個資料）時效能會明顯下降，因此對大型資料的處理並不高效，例如測試案例的測試六。

2. 如果交換次數較多：在最壞情況下，插入排序需要大量的資料交換，這會影響效率，尤其是在資料完全相反時的情況下。
