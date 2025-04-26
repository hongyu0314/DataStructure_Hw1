#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define swap(a,b) temp=a;\
a=b;\
b=temp;

int temp;

void localHeapSort(int* arr, int n, int i) {
    int largest = i;         // 最大值的索引
    int left = 2 * i + 1;    // 左子節點
    int right = 2 * i + 2;   // 右子節點

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
    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        localHeapSort(arr, n, i);
    
    // 一個一個取出元素
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // 把最大值換到最後
        localHeapSort (arr, i, 0);    // 依序向下做heapsort
    }
}

void MemoryUsage() {
    FILE* file = fopen("/proc/self/status", "r");
    if (!file) {
        perror("Failed to open /proc/self/status");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0 || strncmp(line, "VmPeak:", 7) == 0) {
            printf("%s", line);
        }
    }

    fclose(file);
}//MemoryUsage

int main() {
    int pre_sort_array[1024] = {0}, i = 0;

    while (1) {
        scanf("%d", &pre_sort_array[i]);
        if (pre_sort_array[i] == -1) break;
        i++;
    }

    clock_t start = clock();
    heapsort(pre_sort_array, i);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MergeSort recursion version duration: %.9lf seconds\n", duration);

    printf("Memory Usage Info (from /proc/self/status):\n");
    MemoryUsage();

    return 0;
}
