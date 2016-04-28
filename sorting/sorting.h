#include <stdio.h>
#include <stdbool.h>

typedef struct {
    bool (*compare)(void *data, int a, int b);
    void (*swap)(void *data, int a, int b);
} compare_functions;

typedef struct {
    int swaps;
    int compares;
} sorting_metrics;

bool int_array_compare(void *raw, int a, int b) {
    int *data = raw;

    return data[a] > data[b];
}

void int_array_swap(void *raw, int a, int b) {
    int *data = raw;
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

typedef sorting_metrics sorting_function(void *data, int len, compare_functions);
