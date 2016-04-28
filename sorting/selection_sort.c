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
sorting_metrics selection_sort(int *data, int len, compare_functions funcs) {
    sorting_metrics metrics = {0, 0};

    int i = len-1;
    int m = 0;
    int j = 0;

    for(; i > 0; i--) {
        m = 0;
        for(j = 1; j <= i; j++) {
            metrics.compares++;
            if(funcs.compare(data, j, m)) {
                m = j;
            }
        }
        metrics.swaps++;
        funcs.swap(data, i, m);
    }

    return metrics;
}

int main(int argc, char *argv[]) {
    int array[5] = {4, 2, 5, 3, 1};
    printf("%s: {%i, %i, %i, %i, %i}\n", "array before sorting", array[0], array[1], array[2], array[3], array[4]);
    sorting_metrics m = selection_sort(&array[0], 5, (compare_functions){.compare = int_array_compare, .swap = int_array_swap});
    printf("%s: {%i, %i, %i, %i, %i}\n", "array after sorting", array[0], array[1], array[2], array[3], array[4]);
    printf("took %i compares and %i swaps to sort.", m.compares, m.swaps);
    return 0;
}
