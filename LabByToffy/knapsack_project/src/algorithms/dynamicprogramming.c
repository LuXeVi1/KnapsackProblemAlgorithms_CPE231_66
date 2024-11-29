#include "./include/dynamicProgramming.h"

/**
 * Solves the 0/1 Knapsack Problem using dynamic programming.
 * This method builds a DP table to determine the optimal solution.
 * @param items Array of items.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @param solution Pointer to the solution structure to update.
 */
void knapsackDynamicProgramming(const Item items[], int size, int maxWeight, Solution *solution) {
    int dp[size + 1][maxWeight + 1];

    // Initialize DP table
    for (int i = 0; i <= size; i++) {
        for (int w = 0; w <= maxWeight; w++) {
            dp[i][w] = 0;
        }
    }

    // Fill the DP table using the recurrence relation
    for (int i = 1; i <= size; i++) {
        for (int w = 0; w <= maxWeight; w++) {
            if (items[i - 1].weight <= w) {
                // Item can be included, choose the maximum value
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            } else {
                // Item can't be included, carry forward the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The optimal solution value is found in dp[size][maxWeight]
    solution->totalValue = dp[size][maxWeight];

    // Reconstruct the solution to find which items are included
    int w = maxWeight;
    for (int i = size; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            solution->included[i - 1] = true; // Include the item
            solution->totalWeight += items[i - 1].weight;
            w -= items[i - 1].weight; // Reduce the weight capacity
        } else {
            solution->included[i - 1] = false; // Item not included
        }
    }
}

/**
 * Solves the knapsack problem using dynamic programming approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runDynamicProgramming(const Item items[], int size, int maxWeight) {
    Solution bestSolution = { .totalValue = 0, .totalWeight = 0 };
    
    // Initialize the solution array to all false (no items included)
    for (int i = 0; i < MAX_ITEMS; i++) {
        bestSolution.included[i] = false;
    }

    // Solve the problem using dynamic programming
    knapsackDynamicProgramming(items, size, maxWeight, &bestSolution);

    return bestSolution;
}
