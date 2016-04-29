#include <stdio.h>
#include "sorting.h"

/* bubble sort
 *
 * this works by repeatedly iterating over the list, 
 * 'pushing' the largest element to the back of the list
 * to finally sort it.
 */
sorting_metrics bubble_sort(void *data, size_t len, compare_functions funcs, void *unused) {
    sorting_metrics metrics = {0, 0};

    size_t i = len-1;
    size_t j = 0;

    for(; i > 0; i--) {
        for(j = 1; j <= i; j++) {
            metrics.compares++;
            if(funcs.compare(data, j-1, data, j)) {
                metrics.swaps++;
                funcs.swap(data, j-1, data, j);
            }
        }
    }

    return metrics;
}

int main(int argc, char *argv[]) {
    int array[5] = {4, 2, 5, 3, 1};
    printf("%s: {%i, %i, %i, %i, %i}\n", "array before sorting", array[0], array[1], array[2], array[3], array[4]);
    sorting_metrics m = bubble_sort(&array[0], 5, (compare_functions){.compare = int_array_compare, .swap = int_array_swap}, NULL);
    printf("%s: {%i, %i, %i, %i, %i}\n", "array after sorting", array[0], array[1], array[2], array[3], array[4]);
    printf("took %i compares and %i swaps to sort.", m.compares, m.swaps);
    return 0;
}
