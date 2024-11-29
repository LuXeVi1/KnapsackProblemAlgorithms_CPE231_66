#include "SaTTo.h"

int SaTToknapsack(int n, int capacity, Product *products) {
    int *dp = (int *)malloc((capacity + 1) * sizeof(int));
    for (int i = 0; i <= capacity; i++) {
        dp[i] = 0; // Initialize DP array
    }

    for (int i = 0; i < n; i++) { // Process each item
        for (int j = capacity; j >= products[i].weight; j--) { // Reverse iteration
            dp[j] = (dp[j] > dp[j - products[i].weight] +products[i].cost) ? dp[j] : dp[j - products[i].weight] +products[i].cost;
        }
    }

    int maxValue = dp[capacity];
    free(dp);
    return maxValue;
}