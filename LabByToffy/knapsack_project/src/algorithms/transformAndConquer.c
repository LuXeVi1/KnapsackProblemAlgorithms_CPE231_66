#include "./include/transformAndConquer.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * A comparison function for sorting items by their value-to-weight ratio.
 * @param a First item.
 * @param b Second item.
 * @return Comparison result based on value-to-weight ratio.
 */
int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;

    if (ratioA > ratioB) return -1;  // Sort in descending order
    else if (ratioA < ratioB) return 1;
    else return 0;
}

/**
 * Solves the Knapsack problem using the Transform and Conquer approach.
 * First, sorts the items by their value-to-weight ratio and then uses a greedy algorithm.
 * @param items Array of items.
 * @param size Number of items.
 * @return The best solution found.
 */
Solution runTransformAndConquer(const Item items[], int size) {
    // Copy items to preserve the original order for further use
    Item *sortedItems = (Item *)malloc(size * sizeof(Item));
    for (int i = 0; i < size; i++) {
        sortedItems[i] = items[i];
    }

    // Sort the items based on their value-to-weight ratio
    qsort(sortedItems, size, sizeof(Item), compareItems);

    int totalValue = 0;
    int totalWeight = 0;
    bool *included = (bool *)calloc(size, sizeof(bool));

    // Greedily include items until the weight exceeds the capacity
    for (int i = 0; i < size; i++) {
        if (totalWeight + sortedItems[i].weight <= MAX_WEIGHT) {
            included[i] = true;
            totalValue += sortedItems[i].value;
            totalWeight += sortedItems[i].weight;
        } else {
            break;
        }
    }

    // Clean up the sorted items array
    free(sortedItems);

    // Return the solution as a struct
    Solution result = { .totalValue = totalValue, .totalWeight = totalWeight };

    return result;
}
