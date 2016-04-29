#include <stdio.h>
#include "sorting.h"

/* selection sort
 *
 * this algorith works 'backwards': we sweep thru the 
 * list to find the biggest element, and make that 
 * the last element of the list. we repeat that 
 * over and over again to fill up the list in a 
 * sorted way from the back.
 */
sorting_metrics selection_sort(void *data, size_t len, compare_functions funcs, void *unused) {
    sorting_metrics metrics = {0, 0};

    size_t i = len-1;
    size_t m = 0;
    size_t j = 0;

    for(; i > 0; i--) {
        m = 0;
        for(j = 1; j <= i; j++) {
            metrics.compares++;
            if(funcs.compare(data, j, data, m)) {
                m = j;
            }
        }
        metrics.swaps++;
        funcs.swap(data, i, data, m);
    }

    return metrics;
}

int main(int argc, char *argv[]) {
    int array[5] = {4, 2, 5, 3, 1};
    printf("%s: {%i, %i, %i, %i, %i}\n", "array before sorting", array[0], array[1], array[2], array[3], array[4]);
    sorting_metrics m = selection_sort(&array[0], 5, (compare_functions){.compare = int_array_compare, .swap = int_array_swap}, NULL);
    printf("%s: {%i, %i, %i, %i, %i}\n", "array after sorting", array[0], array[1], array[2], array[3], array[4]);
    printf("took %i compares and %i swaps to sort.", m.compares, m.swaps);
    return 0;
}
