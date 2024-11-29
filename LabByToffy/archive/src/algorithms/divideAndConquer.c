#include "./include/divideAndConquer.h"

/**
 * Helper function to solve the knapsack problem using a divide and conquer approach.
 * This method divides the problem into smaller subproblems and then combines them.
 * @param items Array of items.
 * @param start The start index of the current subproblem.
 * @param end The end index of the current subproblem.
 * @param maxWeight The maximum allowable weight.
 * @param solution Pointer to the solution structure to update.
 */
static void knapsackDivideAndConquer(const Item items[], int start, int end, int maxWeight, Solution *solution) {
    // Base case: single item or no items
    if (start == end) {
        if (items[start].weight <= maxWeight) {
            if (items[start].value > solution->totalValue) {
                solution->totalValue = items[start].value;
                solution->totalWeight = items[start].weight;
                for (int i = 0; i <= end; i++) {
                    solution->included[i] = false;
                }
                solution->included[start] = true;
            }
        }
        return;
    }

    int mid = (start + end) / 2;
    
    // Recursively solve for the left half
    knapsackDivideAndConquer(items, start, mid, maxWeight, solution);
    
    // Recursively solve for the right half
    knapsackDivideAndConquer(items, mid + 1, end, maxWeight, solution);

    // Combine the results (evaluate both left and right subsets)
    for (int i = start; i <= mid; i++) {
        for (int j = mid + 1; j <= end; j++) {
            int totalWeight = items[i].weight + items[j].weight;
            int totalValue = items[i].value + items[j].value;

            if (totalWeight <= maxWeight && totalValue > solution->totalValue) {
                solution->totalValue = totalValue;
                solution->totalWeight = totalWeight;
                for (int k = 0; k < start; k++) {
                    solution->included[k] = false;
                }
                solution->included[i] = true;
                solution->included[j] = true;
            }
        }
    }
}

/**
 * Solves the knapsack problem using a divide and conquer approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runDivideAndConquer(const Item items[], int size, int maxWeight) {
    Solution bestSolution = { .totalValue = 0, .totalWeight = 0 };

    for (int i = 0; i < MAX_ITEMS; i++) {
        bestSolution.included[i] = false;
    }

    knapsackDivideAndConquer(items, 0, size - 1, maxWeight, &bestSolution);

    return bestSolution;
}
