#include "./include/bruteforce.h"

/**
 * Helper function to evaluate a specific subset of items.
 * @param items Array of items.
 * @param size Number of items in the array.
 * @param subset Binary representation of the subset.
 * @param maxWeight Maximum allowable weight.
 * @param solution Pointer to the solution structure to update.
 */
static void evaluateSubset(const Item items[], int size, int subset, int maxWeight, Solution *solution) {
    int currentWeight = 0;
    int currentValue = 0;
    bool included[MAX_ITEMS] = { false };

    for (int i = 0; i < size; i++) {
        if (subset & (1 << i)) { // Check if item i is included in this subset
            currentWeight += items[i].weight;
            currentValue += items[i].value;
            included[i] = true;
        }
    }

    // If the current subset is valid and better than the best so far, update the solution
    if (currentWeight <= maxWeight && currentValue > solution->totalValue) {
        solution->totalValue = currentValue;
        solution->totalWeight = currentWeight;
        for (int i = 0; i < size; i++) {
            solution->included[i] = included[i];
        }
    }
}

Solution runBruteForce(const Item items[], int size, int maxWeight) {
    Solution bestSolution = { .totalValue = 0, .totalWeight = 0 };
    for (int i = 0; i < MAX_ITEMS; i++) {
        bestSolution.included[i] = false;
    }

    int totalSubsets = 1 << size; // Total subsets = 2^size
    for (int subset = 0; subset < totalSubsets; subset++) {
        evaluateSubset(items, size, subset, maxWeight, &bestSolution);
    }

    return bestSolution;
}
