#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "algorithms.h"

// Structure to represent an item with its weight, value, and value-to-weight ratio
typedef struct {
    int weight;
    int value;
    double ratio;  // value-to-weight ratio
} Item;

// Comparison function for sorting items by value-to-weight ratio in descending order
int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;

    if (itemA->ratio < itemB->ratio) {
        return 1;
    } else if (itemA->ratio > itemB->ratio) {
        return -1;
    } else {
        return 0;
    }
}

// Function to solve the Knapsack problem using the Greedy approach
int knapsackGreedy(int capacity, int n, int weights[], int values[]) {
    // Create an array of items
    Item *items = (Item *)malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        items[i].weight = weights[i];
        items[i].value = values[i];
        items[i].ratio = (double)values[i] / weights[i];
    }

    // Sort the items based on the value-to-weight ratio in descending order
    qsort(items, n, sizeof(Item), compareItems);

    int totalValue = 0;
    int totalWeight = 0;

    // Greedily pick items until the knapsack is full or all items are considered
    for (int i = 0; i < n; i++) {
        if (totalWeight + items[i].weight <= capacity) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        } else {
            break;  // No more items can be added
        }
    }

    // Free the allocated memory for items
    free(items);

    return totalValue;
}
