#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "algorithms.h"

// Function to compute the total value of items in the knapsack
int computeTotalValue(int n, int weights[], int values[], bool knapsack[]) {
    int totalValue = 0;
    for (int i = 0; i < n; i++) {
        if (knapsack[i]) {
            totalValue += values[i];
        }
    }
    return totalValue;
}

// Function to compute the total weight of items in the knapsack
int computeTotalWeight(int n, int weights[], bool knapsack[]) {
    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        if (knapsack[i]) {
            totalWeight += weights[i];
        }
    }
    return totalWeight;
}

// Function to perform the Iterative Improvement algorithm
int knapsackIterativeImprovement(int capacity, int n, int weights[], int values[]) {
    // Create an initial solution (greedy solution) where items are selected based on value-to-weight ratio
    bool *knapsack = (bool *)malloc(n * sizeof(bool));
    for (int i = 0; i < n; i++) {
        knapsack[i] = false;
    }

    // Sort items by value-to-weight ratio to initialize with a greedy solution
    int *indices = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        indices[i] = i;
    }

    // Sort items by value-to-weight ratio in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            double ratioA = (double)values[indices[i]] / weights[indices[i]];
            double ratioB = (double)values[indices[j]] / weights[indices[j]];
            if (ratioA < ratioB) {
                // Swap indices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Select items greedily
    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        if (totalWeight + weights[indices[i]] <= capacity) {
            knapsack[indices[i]] = true;
            totalWeight += weights[indices[i]];
        }
    }

    // Iterative Improvement loop
    bool improved = true;
    while (improved) {
        improved = false;
        // Try swapping items in the knapsack with those not in it
        for (int i = 0; i < n; i++) {
            if (knapsack[indices[i]]) {
                // Item i is in the knapsack, try removing it and replacing with others
                for (int j = 0; j < n; j++) {
                    if (!knapsack[indices[j]] && totalWeight - weights[indices[i]] + weights[indices[j]] <= capacity) {
                        // Swap item i with item j
                        knapsack[indices[i]] = false;
                        knapsack[indices[j]] = true;
                        totalWeight = totalWeight - weights[indices[i]] + weights[indices[j]];
                        improved = true;
                        break;
                    }
                }
            }
            if (improved) break;  // Break outer loop if improvement was made
        }
    }

    // Compute and return the final total value of the selected items
    int totalValue = computeTotalValue(n, weights, values, knapsack);

    // Free dynamically allocated memory
    free(knapsack);
    free(indices);

    return totalValue;
}
