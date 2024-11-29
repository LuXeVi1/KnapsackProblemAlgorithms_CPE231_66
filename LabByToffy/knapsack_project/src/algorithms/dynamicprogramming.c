#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Dynamic Programming solution to the Knapsack problem
int knapsackDynamicProgramming(int capacity, int n, int weights[], int values[]) {
    // Create a 2D DP array to store solutions to subproblems
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int *)malloc((capacity + 1) * sizeof(int));
    }

    // Initialize the DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0) {
                dp[i][w] = 0; // Base case: no items or zero capacity
            } else if (weights[i - 1] <= w) {
                // Take the maximum value between including or excluding the item
                dp[i][w] = (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) 
                            ? values[i - 1] + dp[i - 1][w - weights[i - 1]] 
                            : dp[i - 1][w];
            } else {
                // If the item cannot be included, just carry forward the previous value
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The bottom-right cell contains the maximum value
    int result = dp[n][capacity];

    // Free the DP array memory
    for (int i = 0; i <= n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result;
}
