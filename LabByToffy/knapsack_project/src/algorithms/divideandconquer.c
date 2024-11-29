#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Helper function to find the maximum value between two solutions
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Divide and Conquer solution to the Knapsack problem
int knapsackDivideAndConquer(int capacity, int n, int weights[], int values[]) {
    // Base case: no items or capacity is zero
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // If the weight of the nth item is greater than the capacity, we cannot include it
    if (weights[n - 1] > capacity) {
        return knapsackDivideAndConquer(capacity, n - 1, weights, values);
    }

    // Otherwise, divide the problem into two subproblems:
    // 1. Exclude the nth item
    int exclude = knapsackDivideAndConquer(capacity, n - 1, weights, values);
    
    // 2. Include the nth item (reduce the capacity by the weight of the nth item)
    int include = values[n - 1] + knapsackDivideAndConquer(capacity - weights[n - 1], n - 1, weights, values);

    // Return the maximum of both solutions
    return max(exclude, include);
}
