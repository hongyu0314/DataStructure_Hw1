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

### 複雜度分析

#### 時間複雜度分析

| 測試案例 | 參數個數 $n$ | interaction version worst case 所耗時間 | recursion version worst case 所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 0.000018234 seconds | 0.000025638 seconds |
| 測試二   | $n = 1000$      | 0.000050844 seconds | 0.000079725 seconds | 
| 測試三   | $n = 2000$      | 0.000124384 seconds | 0.000192790 seconds |
| 測試四   | $n = 3000$      | 0.000236307 seconds | 0.000364234 seconds |
| 測試五   | $n = 4000$      | 0.000382066 seconds | 0.000609600 seconds |
| 測試六   | $n = 5000$      | 0.000592382 seconds | 0.000926802 seconds |

以下為圖表:
![image](https://raw.githubusercontent.com/hongyu0314/DataStructure_Hw1/refs/heads/main/Merge%20Sort/picture/%E5%9C%96%E7%89%871.png)

因 interaction method 的表現明顯更快
所以以下平均複雜度使用 interaction method 

| 測試案例 | 參數個數 $n$ | worst case 所耗時間 | average case 所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 0.000018234 seconds | 0.000017133 seconds |
| 測試二   | $n = 1000$      | 0.000050844 seconds | 0.000046048 seconds | 
| 測試三   | $n = 2000$      | 0.000124384 seconds | 0.000170176 seconds |
| 測試四   | $n = 3000$      | 0.000236307 seconds | 0.000384653 seconds |
| 測試五   | $n = 4000$      | 0.000382066 seconds | 0.000692233 seconds |
| 測試六   | $n = 5000$      | 0.000592382 seconds | 0.001098362 seconds |

以下為圖表:
![image](https://raw.githubusercontent.com/hongyu0314/DataStructure_Hw1/refs/heads/main/Merge%20Sort/picture/%E5%9C%96%E7%89%873.png)

因為算法不完美所以 worst case 比 average case 耗時要短
基於耗時成長幅度決定其複雜度為: O(nlogn)

#### 空間複雜度分析

| 測試案例 | 參數個數 $n$ | interactive version 所用最大空間 | recusion version 所用最大空間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 2680 KB | 2680 KB |
| 測試二   | $n = 1000$      | 2680 KB | 2680 KB |
| 測試三   | $n = 2000$      | 2680 KB | 2680 KB |
| 測試四   | $n = 3000$      | 2680 KB | 2680 KB |
| 測試五   | $n = 4000$      | 2680 KB | 2680 KB |
| 測試六   | $n = 5000$      | 2680 KB | 2680 KB |

因使用 malloc 多用的空間只占極小部分所以所有輸出皆為 2680 KB 為正常現象

interactive version ：因 malloc 只在一開始叫了一組temp，故遞迴消耗記憶體恆為 O(n);

recusion version ：因在每個遞迴呼叫出來後才使用 malloc 故遞迴消耗記憶體恆為 O(n);

## 申論及開發報告

### 根據報告中，使用 merge sort 的主要理由如下：

1.  **要處裡的數據多時**

      mergesort 的資料筆數多了依舊可以保持較快的排序速度 O(nlogn)。

3. **穩定性**

     merge sort 是一個穩定的排序方式，排序資料的狀況並不太影響其處理速度。

### merge sort 不適用的原因如下：

1. **處理較少的資料時**

     由於 merge sort 特性他處理較小的資料筆數時複雜度也是 O(nlogn)，但處理小筆資料有更優秀的排序法。
   
