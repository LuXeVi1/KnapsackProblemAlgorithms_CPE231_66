#include "iterativeimprovement.h"

// Function to calculate the value-to-weight ratio and sort items
void sortItemsByRatio(Product items[], double ratio[], int n) {
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)items[i].cost / items[i].weight;
    }

    // Sort items by ratio in descending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ratio[i] < ratio[j]) {
                // Swap ratios
                double tempRatio = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = tempRatio;

                // Swap corresponding items
                Product temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

// Iterative Improvement Knapsack Function
int iterativeImprovementKnapsack(int n, int capacity, Product items[]) {
    double ratio[n];
    int currentWeight = 0;
    int currentValue = 0;

    // Step 1: Sort items by value-to-weight ratio
    sortItemsByRatio(items, ratio, n);

    // Step 2: Initialize solution with greedy approach
    for (int i = 0; i < n; i++) {
        items[i].isPick = 0; // Initially, no items are selected
        if (currentWeight + items[i].weight <= capacity) {
            items[i].isPick = 1; // Select item
            currentWeight += items[i].weight;
            currentValue += items[i].cost;
        }
    }

    // Step 3: Iteratively improve the solution
    int improved = 1;
    while (improved) {
        improved = 0;

        for (int i = 0; i < n; i++) {
            if (items[i].isPick) {
                // Try removing the item
                items[i].isPick = 0;
                currentWeight -= items[i].weight;
                currentValue -= items[i].cost;

                for (int j = 0; j < n; j++) {
                    if (!items[j].isPick && currentWeight + items[j].weight <= capacity) {
                        // Try adding another item
                        items[j].isPick = 1;
                        int newWeight = currentWeight + items[j].weight;
                        int newValue = currentValue + items[j].cost;

                        if (newValue > currentValue) {
                            currentValue = newValue;
                            currentWeight = newWeight;
                            improved = 1;
                            break; // Restart the improvement loop
                        }

                        // Revert addition if not better
                        items[j].isPick = 0;
                    }
                }

                // Revert removal if no improvement
                if (!improved) {
                    items[i].isPick = 1;
                    currentWeight += items[i].weight;
                    currentValue += items[i].cost;
                } else {
                    break; // Restart the loop if improved
                }
            }
        }
    }

    return currentValue;
}
