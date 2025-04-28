# Heap Sort

## 解題說明

題目要求 heapsort 的 worst case 與 average case 時間、空間的複雜度計算，並且如果有的話使用更快的 methhod。

### 解題策略

1. 如作業題目提到的用不重複隨機數列來做 worst case。

2. 加入srand(time())來保證 average test 的資料多樣性。

## 程式實作

由於 heapsort 沒有兩個 method 所以只有一個 heapsort 主函式。

```cpp
void localHeapSort(int* arr, int n, int i) {
    int largest = i;         // 最大值的索引
    int left = 2 * i + 1;    // 左子節點
    int right = 2 * i + 2;   // 右子節點

    if (left < n && arr[left] > arr[largest]) // 做整理(交換)
        largest = left;
    
    if (right < n && arr[right] > arr[largest])
        largest = right;
    
    if (largest != i) {
        swap(arr[i], arr[largest]);
        localHeapSort(arr, n, largest); // 以遞迴做區域的整理 aka 節點和其後的枝條
    }
}

void heapsort(int* arr, int n) {
    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        localHeapSort(arr, n, i);
    
    // 一個一個取出元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // 把最大值換到最後
        localHeapSort (arr, i, 0);    // 依序向下做 heapsort 遞迴整理每個枝條
    }
}


```

## 效能分析
### 複雜度分析
#### 時間複雜度分析

| 測試案例 | 參數個數 $n$ | average case所耗時間 | worst case所耗時間 |
|----------|--------------|----------|----------|
| 測試一   | $n = 500$      | 0.000041765 seconds | 0.000038130 seconds |
| 測試二   | $n = 1000$      | 0.000153628 seconds | 0.000149688 seconds | 
| 測試三   | $n = 2000$      | 0.000456223 seconds | 0.000455043 seconds |
| 測試四   | $n = 3000$      | 0.000969935 seconds | 0.000947321 seconds |
| 測試五   | $n = 4000$      | 0.001660909 seconds | 0.001646394 seconds |
| 測試六   | $n = 5000$      | 0.002569854 seconds | 0.002557417 seconds |

以下折線圖:
![image](https://raw.githubusercontent.com/hongyu0314/DataStructure_Hw1/refs/heads/main/Heap%20Sort/picture/%E5%9C%96%E7%89%875.png)

根據折線圖成長把 heapsort 的時間複雜度訂為 n(nlogn)

#### 空間複雜度分析

由於整個程式沒有用上 malloc 多抓記憶體使得 heap sort 空間複雜度 n(1)

## 申論及開發報告

### 在本報告中 heap sort 的優缺點如下：

#### 優點

1. **適合處理大量資料**

Heap Sort 的時間複雜度是 O(n log n)，即使在最壞情況下也維持 O(n log n)，因此在處理大量資料時表現穩定且高效。
且是一種原地排序（In-place sorting），除了少量額外變數，不需要額外的儲存空間，因此空間複雜度是 O(1)。

2. **不受資料初始順序影響**

無論資料是隨機、已排序或反向排序，Heap Sort 的時間複雜度始終穩定在 O(n log n)。

#### 缺點

1. **不是穩定排序**

Heap Sort 不是穩定排序，也就是說如果有兩個相同鍵值的元素，排序後它們的相對順序可能會改變。

2. **對小型資料表現略遜於其他演算法**

由於 Heap Sort 的資料交換次數較多，且堆積維護的開銷，在小型資料集上，速度可能比插入排序或快速排序稍慢。
