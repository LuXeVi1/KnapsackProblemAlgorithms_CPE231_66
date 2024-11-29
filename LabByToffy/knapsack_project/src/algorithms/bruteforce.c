#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algorithms.h"

// Helper function to calculate the total value and weight of a subset
void getSubsetValueAndWeight(int *weights, int *values, int *subset, int n, int *totalWeight, int *totalValue) {
    *totalWeight = 0;
    *totalValue = 0;

    for (int i = 0; i < n; i++) {
        if (subset[i] == 1) {  // If the item is included in the subset
            *totalWeight += weights[i];
            *totalValue += values[i];
        }
    }
}

// Brute Force solution to the Knapsack problem
int knapsackBruteForce(int capacity, int n, int weights[], int values[]) {
    int maxValue = 0;

    // Total number of possible subsets = 2^n
    int totalSubsets = pow(2, n);

    // Loop through all subsets
    for (int subset = 0; subset < totalSubsets; subset++) {
        int subsetArray[n];
        int totalWeight = 0, totalValue = 0;

        // Generate the subset by checking each bit
        for (int i = 0; i < n; i++) {
            // Check if the i-th item is in the subset (bit is set)
            subsetArray[i] = (subset >> i) & 1;
        }

        // Calculate the total value and weight of this subset
        getSubsetValueAndWeight(weights, values, subsetArray, n, &totalWeight, &totalValue);

        // If the weight is within the capacity and the value is greater than the max value, update it
        if (totalWeight <= capacity && totalValue > maxValue) {
            maxValue = totalValue;
        }
    }

    return maxValue;
}
