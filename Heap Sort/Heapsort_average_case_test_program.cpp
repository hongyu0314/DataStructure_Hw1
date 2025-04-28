#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_INPUT_SIZE 5000
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

void fill_random(int* arr, int size) {
    int range = size;
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % range;  // [0, range-1]
    }
}

int main() {
    int pre_sort_array[MAX_INPUT_SIZE+1] = {0}, i = 0;//+1 is for the end of input flag aka -1
    int test_element_count, test_repeat = 10000;
    double avg_duration=0;

    while (1) 
    {
        scanf("%d", &test_element_count);
        if (test_element_count == -1) break;
    
        i = test_repeat;
    
        while(i--){
        
        fill_random(pre_sort_array,test_element_count);
        
            clock_t start = clock();
            heapsort(pre_sort_array,test_element_count);
            clock_t end = clock();
        
            avg_duration += (double)(end - start) / CLOCKS_PER_SEC;
        }
        
        printf("HeapSort interactive version total duration: %.9lf seconds\n", avg_duration);
        printf("HeapSort interactive version average duration: %.9lf seconds\n", avg_duration/test_repeat);

    
        printf("Memory Usage Info (from /proc/self/status):\n");
        MemoryUsage();
    
    }

    return 0;
}
