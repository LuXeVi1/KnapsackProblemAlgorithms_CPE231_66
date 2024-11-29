#include "spaceandtimetradeoff.h"
#include <stdlib.h>

// Space-Optimized Dynamic Programming Knapsack
int spaceOptimizedKnapsack(int n, int maxWeight, Product *products) {
    // Allocate DP array for capacities up to maxWeight
    int *dp = (int *)malloc((maxWeight + 1) * sizeof(int));
    if (!dp) {
        perror("Memory allocation failed");
        return -1;
    }

    // Initialize DP array to 0
    for (int w = 0; w <= maxWeight; w++) {
        dp[w] = 0;
    }

    // Process each product
    for (int i = 0; i < n; i++) {
        // Traverse weights in reverse to prevent overwriting results from the same row
        for (int w = maxWeight; w >= products[i].weight; w--) {
            int includeValue = dp[w - products[i].weight] + products[i].cost;
            dp[w] = (dp[w] > includeValue) ? dp[w] : includeValue;
        }
    }

    int maxValue = dp[maxWeight]; // Maximum value for given capacity
    free(dp); // Free allocated memory
    return maxValue;
}
