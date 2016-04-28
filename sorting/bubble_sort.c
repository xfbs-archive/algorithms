#include <stdio.h>
#include "sorting.h"

/* bubble sort
 *
 * this works by repeatedly iterating over the list, 
 * 'pushing' the largest element to the back of the list
 * to finally sort it.
 */
sorting_metrics bubble_sort(int *data, int len, compare_functions funcs) {
    sorting_metrics metrics = {0, 0};

    int i = len-1;
    int j = 0;

    for(; i > 0; i--) {
        for(j = 1; j <= i; j++) {
            metrics.compares++;
            if(funcs.compare(data, j-1, j)) {
                metrics.swaps++;
                funcs.swap(data, j-1, j);
            }
        }
    }

    return metrics;
}

int main(int argc, char *argv[]) {
    int array[5] = {4, 2, 5, 3, 1};
    printf("%s: {%i, %i, %i, %i, %i}\n", "array before sorting", array[0], array[1], array[2], array[3], array[4]);
    sorting_metrics m = bubble_sort(&array[0], 5, (compare_functions){.compare = int_array_compare, .swap = int_array_swap});
    printf("%s: {%i, %i, %i, %i, %i}\n", "array after sorting", array[0], array[1], array[2], array[3], array[4]);
    printf("took %i compares and %i swaps to sort.", m.compares, m.swaps);
    return 0;
}
