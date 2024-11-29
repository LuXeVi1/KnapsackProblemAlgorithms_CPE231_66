#ifndef DYNAMIC_PROGRAMMING_H
#define DYNAMIC_PROGRAMMING_H

#include "../src/structure.h"  

// Function prototypes for dynamic programming algorithms

/**
 * Solves the knapsack problem using dynamic programming.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runDynamicProgramming(const Item items[], int size, int maxWeight);

#endif // DYNAMIC_PROGRAMMING_H
