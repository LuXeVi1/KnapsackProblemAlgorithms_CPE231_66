#include "./include/iterativeimprovement.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Evaluates the total value and weight of the current solution.
 * @param items Array of items.
 * @param size Number of items in the array.
 * @param included Boolean array indicating which items are included.
 * @return The total value of the current solution.
 */
int evaluateSolution(const Item items[], int size, bool included[]) {
    int totalValue = 0;
    int totalWeight = 0;

    for (int i = 0; i < size; i++) {
        if (included[i]) {
            totalValue += items[i].value;
            totalWeight += items[i].weight;
        }
    }

    // Penalize the solution if it exceeds the maximum weight
    if (totalWeight > MAX_WEIGHT) {
        return 0;
    }

    return totalValue;
}

/**
 * Performs a simple swap between two items in the solution.
 * @param included Boolean array indicating which items are included.
 * @param i Index of the first item to swap.
 * @param j Index of the second item to swap.
 */
void swapItems(bool included[], int i, int j) {
    bool temp = included[i];
    included[i] = included[j];
    included[j] = temp;
}

/**
 * Performs the Iterative Improvement algorithm to solve the Knapsack problem.
 * @param items Array of items.
 * @param size Number of items in the array.
 * @return The best solution found.
 */
Solution runIterativeImprovement(const Item items[], int size) {
    // Initialize the solution with all items excluded
    bool *currentSolution = (bool *)calloc(size, sizeof(bool));
    bool *bestSolution = (bool *)calloc(size, sizeof(bool));

    int bestValue = 0;

    // Initialize the best solution value
    bestValue = evaluateSolution(items, size, currentSolution);

    bool improved = true;

    // Keep iterating until no improvement is found
    while (improved) {
        improved = false;

        // Try swapping each pair of items
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                // Swap the two items and evaluate the new solution
                swapItems(currentSolution, i, j);
                int newValue = evaluateSolution(items, size, currentSolution);

                // If the new solution is better, update the best solution
                if (newValue > bestValue) {
                    bestValue = newValue;
                    // Save the new solution as the best solution
                    for (int k = 0; k < size; k++) {
                        bestSolution[k] = currentSolution[k];
                    }
                    improved = true;  // Set the flag to continue improving
                }

                // Undo the swap to test the next pair of items
                swapItems(currentSolution, i, j);
            }
        }
    }

    // Convert the best solution into the Solution struct
    Solution result = { .totalValue = bestValue, .totalWeight = 0 };
    for (int i = 0; i < size; i++) {
        if (bestSolution[i]) {
            result.totalWeight += items[i].weight;
        }
    }

    // Clean up memory
    free(currentSolution);
    free(bestSolution);

    return result;
}
