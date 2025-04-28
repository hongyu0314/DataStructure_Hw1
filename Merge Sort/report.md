# Merge Sort

## 題目說明

題目要求 mergesort 的 worst case 與 average case 時間、空間的複雜度計算，並且如果有的話使用更快的 methhod。

### 解題細節

1. 將使用兩種 method 在一樣的環境下執行。 

3. average case 的整數變數產生使用隨機亂數(範圍在0~1000)。

4. 程式在 linux 下的 GDB 環境運行 (GDB 環境會記錄程式執行期間的記憶體使用峰值)。

5. 因 mergesort 演算法特性所有步驟皆會跑過一遍所以 worst case 將採用與 average case 相同的隨機生成。

## 程式碼片段分析

以下為 interactive version 的程式碼：
```cpp
void merge(int* src, int* dest, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) { //比較兩個片段的最小值 填入目標位置 aka 下一層片段 
        dest[k++] = (src[i] <= src[j]) ? src[i++] : src[j++];
    }
    while (i < mid) dest[k++] = src[i++];
    while (j < right) dest[k++] = src[j++];
}

void merge_sort_v(int* array, int size) { //merge sort 的主函式
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp) { //偵測取記憶體成功
        perror("malloc failed");
        return;
    }

    int* src = array; 
    int* dest = temp; // 把本來的陣列指派給第一個 run 並把 malloc 的陣列指派給 第二個 run

    for (int width = 1; width < size; width *= 2) { // 從一個單位開始每次結合兩個片段
        for (int i = 0; i < size; i += 2 * width) {
            int left = i;
            int mid = (i + width < size) ? i + width : size;
            int right = (i + 2 * width < size) ? i + 2 * width : size;
            merge(src, dest, left, mid, right);
        }

        // 交換兩個 run 的指標
        int* tmp = src;
        src = dest;
        dest = tmp;

    }

    // 把正確的結果複製到目標陣列
    if (src != array) {
        for (int i = 0; i < size; ++i)
            array[i] = src[i];
    }

    free(temp);
}
```

以下為 recursion version 的程式碼：

```cpp
void merge_sort(int* array_start, int* array_end) {
    int size = array_end - array_start;
    if (size <= 1) {
        // 遞迴的終點 aka 片段已經拆分到最小
        return;
    }
    int* midpoint = array_start + size / 2; // 計算片段中點準備拆分

    merge_sort(array_start, midpoint); // 根據中點與片段左最、最右點往下做遞迴
    merge_sort(midpoint, array_end);

    int* temp = (int*)malloc(size * sizeof(int)); // 取記憶體
    int *left = array_start, *right = midpoint, *dest = temp;

    while (left < midpoint && right < array_end) {  // 結合更高層遞迴回來的兩個較小片段
        if (*left <= *right) {
            *dest++ = *left++;
        } else {
            *dest++ = *right++;
        }
    }
    while (left < midpoint) {
        *dest++ = *left++;
    }
    while (right < array_end) {
        *dest++ = *right++;
    }

    for (int i = 0; i < size; ++i) { // 把結果送回接收的陣列
        array_start[i] = temp[i];
    }

    free(temp);
}
```
## 效能分析

### 測試案例

| 測試案例 | 參數個數 $n$ | interaction version所耗時間 | recursion version 所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 0.036974 seconds | 0.048030 seconds |
| 測試二   | $n = 1000$      | 0.049798 seconds | 0.136707 seconds | 
| 測試三   | $n = 2000$      | 0.101688 seconds | 0.302911 seconds |
| 測試四   | $n = 3000$      | 0.258972 seconds | 0.541366 seconds |
| 測試五   | $n = 4000$      | 0.462440 seconds | 0.856168 seconds |
| 測試六   | $n = 5000$      | 0.748762 seconds | 1.251639 seconds |

### 複雜度分析
以下為圖表連結:
![] (https://raw.githubusercontent.com/hongyu0314/DataStructure_Hw1/refs/heads/main/Merge%20Sort/picture/%E5%9C%96%E7%89%871.png)


## 申論及開發報告

### 在本程式中，使用插入排序法的主要原因如下：

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
