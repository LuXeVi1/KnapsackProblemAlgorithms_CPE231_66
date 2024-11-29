#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

// Structure to represent an item
typedef struct {
    int weight;
    int value;
    float ratio;  // Value-to-weight ratio
} Item;

// Function to compare items based on value-to-weight ratio in descending order
int compare(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) {
        return 1;
    } else if (itemA->ratio > itemB->ratio) {
        return -1;
    }
    return 0;
}

// Fractional Knapsack solution to the problem
float knapsackFractional(int capacity, int n, int weights[], int values[]) {
    // Create an array of items
    Item *items = (Item *)malloc(n * sizeof(Item));

    // Fill the items array with weights, values, and value-to-weight ratios
    for (int i = 0; i < n; i++) {
        items[i].weight = weights[i];
        items[i].value = values[i];
        items[i].ratio = (float)values[i] / weights[i];
    }

    // Sort the items in decreasing order of value-to-weight ratio
    qsort(items, n, sizeof(Item), compare);

    // Now, start filling the knapsack
    float totalValue = 0.0;
    for (int i = 0; i < n; i++) {
        if (capacity == 0) {
            break; // Knapsack is full
        }

        // If the current item can be fully included
        if (items[i].weight <= capacity) {
            capacity -= items[i].weight;
            totalValue += items[i].value;
        } else {
            // If the item can't be fully included, take the fraction that fits
            totalValue += items[i].value * ((float)capacity / items[i].weight);
            break; // The knapsack is now full
        }
    }

    // Free the allocated memory for items array
    free(items);

    return totalValue;
}
