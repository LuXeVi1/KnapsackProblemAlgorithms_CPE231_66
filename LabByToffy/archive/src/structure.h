#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Constants
#define MAX_ITEMS 1000    // Maximum number of items for algorithms
#define MAX_WEIGHT 10000  // Maximum weight capacity for knapsack problems

// Common Data Structures

// Represents an item for optimization problems (e.g., knapsack)
typedef struct {
    int id;         // Unique identifier
    int weight;     // Weight of the item
    int value;      // Value of the item
} Item;

// Represents a solution for optimization problems
typedef struct {
    int totalValue;     // Total value of the solution
    int totalWeight;    // Total weight of the solution
    bool included[MAX_ITEMS]; // Boolean array to track included items
} Solution;

// Utility Macros
#define MIN(a, b) (((a) < (b)) ? (a) : (b))  // Minimum of two numbers
#define MAX(a, b) (((a) > (b)) ? (a) : (b))  // Maximum of two numbers

// Debugging Utilities
#ifdef DEBUG
    #define LOG(fmt, ...) fprintf(stderr, "DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
    #define LOG(fmt, ...) // Disabled in non-debug mode
#endif

// Common Utility Functions

/**
 * Prints an array of items.
 * @param items The array of items to print.
 * @param size The number of items in the array.
 */
static inline void printItems(const Item items[], int size) {
    printf("ID\tWeight\tValue\n");
    for (int i = 0; i < size; i++) {
        printf("%d\t%d\t%d\n", items[i].id, items[i].weight, items[i].value);
    }
}

/**
 * Prints a solution.
 * @param solution The solution to print.
 * @param size The number of items considered.
 */
static inline void printSolution(const Solution *solution, int size) {
    printf("Total Value: %d\n", solution->totalValue);
    printf("Total Weight: %d\n", solution->totalWeight);
    printf("Included Items: ");
    for (int i = 0; i < size; i++) {
        if (solution->included[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

#endif // STRUCTURE_H
