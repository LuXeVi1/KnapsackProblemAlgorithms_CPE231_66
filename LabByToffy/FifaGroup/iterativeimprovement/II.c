#include "II.h"

// Function to calculate the total value of items in the knapsack
int knapsackValue(Product products[], int n, int capacity) {
    int totalValue = 0;
    int totalWeight = 0;

    for (int i = 0; i < n; i++) {
        if (products[i].isPick) {
            totalValue += products[i].cost;
            totalWeight += products[i].weight;
        }
    }

    // If the weight exceeds capacity, return a very small value (invalid solution)
    if (totalWeight > capacity) {
        return -1;
    }

    return totalValue;
}
// Function to implement Iterative Improvement for 0/1 Knapsack problem
int iterativeImprovementKnapsack(int n, int capacity,Product items[]) {
    double ratio[n];  // Use a double array for ratios
    // Step 1: Initialize the solution using a greedy approach
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)items[i].cost / items[i].weight;
        items[i].isPick = 0; // Initially, none of the items are in the knapsack
    }
    
    // Sort items by value-to-weight ratio
    quickSortTaC(items, ratio, 0, n - 1);

    // Greedily pick items until the capacity is exceeded
    int totalWeight = 0;
    for (int i = 0; i < n && totalWeight + items[i].weight <= capacity; i++) {
        items[i].isPick = 1;
        totalWeight += items[i].weight;
    }

    // Step 2: Iteratively improve the solution
    int currentValue = knapsackValue(items, n, capacity);
    int improved = 1;
    while (improved) {
        improved = 0;

        // Try swapping items in the knapsack with items outside
        for (int i = 0; i < n; i++) {
            if (items[i].isPick) {
                // Try removing the item and check if the value increases
                items[i].isPick = 0;
                int tempValue = knapsackValue(items, n, capacity);
                if (tempValue > currentValue) {
                    currentValue = tempValue;
                    improved = 1;
                    break; // Break and recheck the solution
                } else {
                    // Revert if no improvement
                    items[i].isPick = 1;
                }
            } else {
                // Try adding the item if it is not in the knapsack
                items[i].isPick = 1;
                int tempValue = knapsackValue(items, n, capacity);
                if (tempValue > currentValue) {
                    currentValue = tempValue;
                    improved = 1;
                    break; // Break and recheck the solution
                } else {
                    // Revert if no improvement
                    items[i].isPick = 0;
                }
            }
        }
    }

    return currentValue;
}