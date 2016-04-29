#include <stdio.h>
#include "sorting.h"

sorting_metrics merge_sort(void *data, size_t len, compare_functions funcs, void *unused) {
    sorting_metrics metrics = {0, 0, 0};

    if(len == 2) {
        metrics.compares++;
        if(funcs.compare(data, 0, data, 1)) {
            metrics.swaps++;
            funcs.swap(data, 0, data, 1);
        }
    } else if(len > 2) {
        // split task up into two equal portions. to do so,
        // we must determine the length of the portions first.
        size_t len_a = len/2;
        size_t len_b = len - len_a;

        // make a note that we are using additional memory here.
        metrics.memory += len;
        
        // create copies on the data that we can pass down to sorting
        void *data_a = funcs.copy(data, 0, len_a);
        void *data_b = funcs.copy(data, len_a, len_b);

        // sort the data and add up the noted resource usage
        sorting_metrics ret_a = merge_sort(data_a, len_a, funcs, unused);
        sorting_metrics ret_b = merge_sort(data_b, len_b, funcs, unused);
        metrics.compares += ret_a.compares + ret_b.compares;
        metrics.swaps    += ret_a.swaps    + ret_b.swaps;
        metrics.memory   += ret_a.memory   + ret_b.memory;

        // now we have to join the sorted lists.
        size_t ia = 0;
        size_t ib = 0;
        size_t i = 0;
        for(; i < len && ia < len_a && ib < len_b; i++) {
            metrics.compares++;
            if(funcs.compare(data_a, ia, data_b, ib)) {
                funcs.swap(data_b, ib, data, i);
                ib++;
            } else {
                funcs.swap(data_a, ia, data, i);
                ia++;
            }
            metrics.swaps++;
        }

        for(; ia < len_a || ib < len_b; i++) {
            if(ia < len_a) {
                funcs.swap(data_a, ia, data, i);
                ia++;
            } else {
                funcs.swap(data_b, ib, data, i);
                ib++;
            }
            metrics.swaps++;
        }

        // let's be a tidy kiwi.
        funcs.free(data_a);
        funcs.free(data_b);
    }
    return metrics;
}

int main(int argc, char *argv[]) {
    int array[5] = {4, 2, 5, 3, 1};
    printf("%s: {%i, %i, %i, %i, %i}\n", "array before sorting", array[0], array[1], array[2], array[3], array[4]);
    sorting_metrics m = merge_sort(&array[0], 5, (compare_functions){
            .compare = int_array_compare, 
            .swap = int_array_swap,
            .copy = int_array_copy,
            .free = int_array_free}, NULL);
    printf("%s: {%i, %i, %i, %i, %i}\n", "array after sorting", array[0], array[1], array[2], array[3], array[4]);
    printf("took %i compares and %i swaps to sort.", m.compares, m.swaps);
    return 0;
}
