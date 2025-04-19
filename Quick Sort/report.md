# Quick Sort

## 解題說明

本題要求使用median-of-three method來完成快速排序法，輸入為隨機產生的亂數，以最好的時間/空間複雜度排序出結果和計算出排序所耗費時間

### 解題策略

1. 使用template <class Ｔ>來處理任何資料型態。

2. 計算運行時間使用 clock( ) 測量排序時間。

3. 輸出結果為排序前與排序後的資料與排序資料所需時間。

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
    int n = 10;  // 測試數量為 10
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

| 測試案例 | 隨機參數 $n$ | 實際輸出 | 排序所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      |  太多了...  |            |
| 測試二   | $n = 1000$      |   太多了...    |           |
| 測試三   | $n = 2000$      |    太多了...    |           |
| 測試四   | $n = 3000$      |    太多了...    |           |
| 測試五   | $n = 4000$      |    太多了...    |           |
| 測試六   | $n = 5000$      |    太多了...    |           |

## 申論及開發報告

### 在本程式中，使用median-of-three method來完成快速排序法的主要原因如下：

