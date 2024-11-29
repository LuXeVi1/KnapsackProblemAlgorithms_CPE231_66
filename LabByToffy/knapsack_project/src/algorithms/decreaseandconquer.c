#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Decrease and Conquer solution to the Knapsack problem
int knapsackDecreaseAndConquer(int capacity, int n, int weights[], int values[]) {
    // Base case: if there are no items or the capacity is zero
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // If the weight of the nth item is greater than the capacity, we cannot include it
    if (weights[n - 1] > capacity) {
        return knapsackDecreaseAndConquer(capacity, n - 1, weights, values);
    }

    // Otherwise, we have two options:
    // 1. Exclude the nth item
    int exclude = knapsackDecreaseAndConquer(capacity, n - 1, weights, values);
    
    // 2. Include the nth item (reduce the capacity by the weight of the nth item)
    int include = values[n - 1] + knapsackDecreaseAndConquer(capacity - weights[n - 1], n - 1, weights, values);

    // Return the maximum of both options
    if (include > exclude) {
        return include;
    } else {
        return exclude;
    }
}
