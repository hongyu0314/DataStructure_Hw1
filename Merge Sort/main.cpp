#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void merge_sort(int* array_start, int* array_end) {
    int size = array_end - array_start;
    if (size <= 1) return;

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
}//MemoryUsage

int main() {
    int pre_sort_array[1024] = {0}, i = 0;

    while (1) {
        scanf("%d", &pre_sort_array[i]);
        if (pre_sort_array[i] == -1) break;
        i++;
    }

    clock_t start = clock();
    merge_sort(pre_sort_array, pre_sort_array + i);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MergeSort recursion version duration: %.9lf seconds\n", duration);

    printf("Memory Usage Info (from /proc/self/status):\n");
    MemoryUsage();

    return 0;
}
