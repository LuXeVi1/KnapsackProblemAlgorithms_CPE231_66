#include "greedy.h"

/**
 * Comparator function for sorting items based on their value-to-weight ratio.
 * @param a Pointer to the first item.
 * @param b Pointer to the second item.
 * @return 1 if item a should be before item b, otherwise -1.
 */
int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    double ratioA = (double)itemA->value / itemA->weight;
    double ratioB = (double)itemB->value / itemB->weight;

    if (ratioA > ratioB) return -1;
    else if (ratioA < ratioB) return 1;
    return 0;
}

/**
 * Solves the knapsack problem using the greedy algorithm.
 * @param items Array of items.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @param solution Pointer to the solution structure to update.
 */
void knapsackGreedy(const Item items[], int size, int maxWeight, Solution *solution) {
    // Sort items by value-to-weight ratio in descending order
    qsort((void *)items, size, sizeof(Item), compareItems);

    solution->totalValue = 0;
    solution->totalWeight = 0;

    // Greedily select items
    for (int i = 0; i < size; i++) {
        if (solution->totalWeight + items[i].weight <= maxWeight) {
            solution->totalValue += items[i].value;
            solution->totalWeight += items[i].weight;
            solution->included[i] = true;
        } else {
            solution->included[i] = false;
        }
    }
}

/**
 * Solves the knapsack problem using the greedy approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runGreedy(const Item items[], int size, int maxWeight) {
    Solution bestSolution = { .totalValue = 0, .totalWeight = 0 };

    // Initialize the solution array to all false (no items included)
    for (int i = 0; i < MAX_ITEMS; i++) {
        bestSolution.included[i] = false;
    }

    // Solve the problem using the greedy approach
    knapsackGreedy(items, size, maxWeight, &bestSolution);

    return bestSolution;
}
