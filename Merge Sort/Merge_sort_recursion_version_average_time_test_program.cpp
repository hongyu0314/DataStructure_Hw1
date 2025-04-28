#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_INPUT_SIZE 5000


void merge_sort(int* array_start, int* array_end) {
    int size = array_end - array_start;
    if (size <= 1) {
        
        return;
    }
    int* midpoint = array_start + size / 2;

    merge_sort(array_start, midpoint);
    merge_sort(midpoint, array_end);

    int* temp = (int*)malloc(size * sizeof(int));
    int *left = array_start, *right = midpoint, *dest = temp;

    while (left < midpoint && right < array_end) {
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

    for (int i = 0; i < size; ++i) {
        array_start[i] = temp[i];
    }

    free(temp);
}//merge_sort

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
}

void fill_random(int* arr, int size, int range) {
    srand(time(0));
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % range;  // [0, range-1]
    }
}


int main() {
    int pre_sort_array[MAX_INPUT_SIZE+1] = {0}, i = 0;//+1 is for the end of input flag aka -1
    int test_element_count = 1000, test_repeat;
    double avg_duration=0;

    while (1) 
    {
        scanf("%d", &test_repeat);
        if (test_repeat == -1) break;
    
        i = test_repeat;
    
        while(i--){
            fill_random(pre_sort_array,test_element_count,2000);
        
            clock_t start = clock();
            merge_sort(pre_sort_array,pre_sort_array+test_element_count);
            clock_t end = clock();
        
            avg_duration += (double)(end - start) / CLOCKS_PER_SEC;
        }
        
        printf("MergeSort interactive version total duration: %.9lf seconds\n", avg_duration);
        printf("MergeSort interactive version average duration: %.9lf seconds\n", avg_duration/test_repeat);
    
        printf("Memory Usage Info (from /proc/self/status):\n");
        MemoryUsage();
    
    }

    return 0;
}
