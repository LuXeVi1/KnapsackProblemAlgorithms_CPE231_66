#include "transformandconquer.h"
#include <stdlib.h>

// Function to swap two `Product` structures
void swapProduct(Product *a, Product *b) {
    Product temp = *a;
    *a = *b;
    *b = temp;
}

// Function to swap two `double` values
void swapDouble(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for quicksort
int partition(Product products[], double ratio[], int low, int high) {
    double pivot = ratio[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (ratio[j] > pivot) { // Descending order
            i++;
            swapProduct(&products[i], &products[j]);
            swapDouble(&ratio[i], &ratio[j]);
        }
    }
    swapProduct(&products[i + 1], &products[high]);
    swapDouble(&ratio[i + 1], &ratio[high]);
    return i + 1;
}

// Quicksort function for `Product` array based on `ratio[]`
void quickSort(Product products[], double ratio[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(products, ratio, low, high);
        quickSort(products, ratio, low, pivotIndex - 1);
        quickSort(products, ratio, pivotIndex + 1, high);
    }
}

// Function to solve the Fractional Knapsack Problem
int fractionalKnapsack(int n, int capacity, Product products[]) {
    // Edge case: No items or zero capacity
    if (n == 0 || capacity == 0) {
        return 0;
    }

    // Array to store value-to-weight ratios
    double *ratio = (double *)malloc(n * sizeof(double));
    if (!ratio) {
        perror("Memory allocation failed for ratio array");
        return -1;
    }

    // Compute value-to-weight ratio for each item
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)products[i].cost / (double)products[i].weight;
    }

    // Sort items by ratio in descending order
    quickSort(products, ratio, 0, n - 1);

    double totalValue = 0.0;  // Total value of items in the knapsack
    int remainingCapacity = capacity;

    for (int i = 0; i < n; i++) {
        if (products[i].weight <= remainingCapacity) {
            // Take the whole item
            totalValue += products[i].cost;
            remainingCapacity -= products[i].weight;
        } else {
            // Take the fractional part of the item
            totalValue += ratio[i] * remainingCapacity;
            break; // No more capacity
        }
    }

    free(ratio); // Free allocated memory
    return (int)totalValue; // Return the total value as an integer
}
