#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_INPUT_SIZE 5000


void merge(int* src, int* dest, int left, int mid, int right) {
    int i = left, j = mid, k = left;
    while (i < mid && j < right) {
        dest[k++] = (src[i] <= src[j]) ? src[i++] : src[j++];
    }
    while (i < mid) dest[k++] = src[i++];
    while (j < right) dest[k++] = src[j++];
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
}

void merge_sort_v(int* array, int size) {
    int* temp = (int*)malloc(size * sizeof(int));
    if (!temp) {
        perror("malloc failed");
        return;
    }

    int* src = array;
    int* dest = temp;

    for (int width = 1; width < size; width *= 2) {
        printf("Merging subarrays of size %d (run 1 → temp):\n", width);
        for (int i = 0; i < size; i += 2 * width) {
            int left = i;
            int mid = (i + width < size) ? i + width : size;
            int right = (i + 2 * width < size) ? i + 2 * width : size;

            printf("  Merging [%d:%d] and [%d:%d] → ", left, mid - 1, mid, right - 1);
            merge(src, dest, left, mid, right);
        }

        // swap buffers
        int* tmp = src;
        src = dest;
        dest = tmp;

    }

    // if final result is in temp (because of an odd number of passes), copy back
    if (src != array) {
        for (int i = 0; i < size; ++i)
            array[i] = src[i];
    }
    
    printf("Memory Usage Info (from /proc/self/status):\n");
    MemoryUsage();

    free(temp);
}


int main() {
    int pre_sort_array[MAX_INPUT_SIZE+1] = {0}, i = 0;//+1 is for the end of input flag aka -1

    while (1) {
        scanf("%d", &pre_sort_array[i]);
        if (pre_sort_array[i] == -1) break;
        i++;
    }

    clock_t start = clock();
    merge_sort_v(pre_sort_array,i);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("MergeSort interactive version duration: %.9lf seconds\n", duration);

    

    return 0;
}
