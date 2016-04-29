#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool (*compare)(void *data_a, size_t index_a, void *data_b, size_t index_b);
    void (*swap)(void *data_a, size_t index_a, void *data_b, size_t index_b);
    void *(*copy)(void *data, size_t begin, size_t amount);
    void (*free)(void *data);
} compare_functions;

typedef struct {
    int swaps;
    int compares;
    int memory;
} sorting_metrics;

bool int_array_compare(void *data_a, size_t index_a, void *data_b, size_t index_b) {
    int *ptr_a = data_a;
    int *ptr_b = data_b;
    return ptr_a[index_a] > ptr_b[index_b];
}

void int_array_swap(void *data_a, size_t index_a, void *data_b, size_t index_b) {
    int *ptr_a = data_a;
    int *ptr_b = data_b;
    int tmp = ptr_a[index_a];
    ptr_a[index_a] = ptr_b[index_b];
    ptr_b[index_b] = tmp;
}

void *int_array_copy(void *raw, size_t begin, size_t amount) {
    int *dest = calloc(amount, sizeof(int));
    int *src = raw;
    memcpy(dest, &src[begin], amount*sizeof(int));
    return dest;
}

void int_array_free(void *raw) {
    free(raw);
}

typedef sorting_metrics sorting_function(void *data, size_t len, compare_functions, void *parameters);
