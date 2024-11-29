#include "transformandconquer.h"

// Function to swap two `Product` structures
void swapTaC(Product *a, Product *b) {
    Product t = *a;
    *a = *b;
    *b = t;
}

// Function to swap two `double` values
void swapRatioTaC(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

// Partition function for quicksort
int partitionTaC(Product products[], double ratio[], int low, int high) {
    double pivot = ratio[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (ratio[j] > pivot) { // Descending order
            i++;
            swapTaC(&products[i], &products[j]);
            swapRatioTaC(&ratio[i], &ratio[j]);
        }
    }
    swapTaC(&products[i + 1], &products[high]);
    swapRatioTaC(&ratio[i + 1], &ratio[high]);
    return i + 1;
}

// Quicksort function for `Product` array based on `ratio[]`
void quickSortTaC(Product products[], double ratio[], int low, int high) {
    if (low < high) {
        int pi = partitionTaC(products, ratio, low, high);
        quickSortTaC(products, ratio, low, pi - 1);
        quickSortTaC(products, ratio, pi + 1, high);
    }
}

// Function to solve the Fractional Knapsack Problem
int fractionalKnapsack(int n, int capacity, Product products[]) {
    double ratio[n];
    for (int i = 0; i < n; i++) {
        ratio[i] = (double)products[i].cost / products[i].weight;
    }

    // Sort items by value-to-weight ratio in descending order
    quickSortTaC(products, ratio, 0, n - 1);

    double totalValue = 0.0;  // Total value of items in the knapsack
    int remainingCapacity = capacity;

    for (int i = 0; i < n; i++) {
        if (products[i].weight <= remainingCapacity) {
            // If the entire item can fit, take it
            totalValue += products[i].cost;
            remainingCapacity -= products[i].weight;
        } else {
            // Take the fraction of the item that fits
            totalValue += ratio[i] * remainingCapacity;
            break;
        }
    }

    return (int)totalValue;
}