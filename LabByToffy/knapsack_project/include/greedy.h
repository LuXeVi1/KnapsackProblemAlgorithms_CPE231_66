#ifndef GREEDY_ALGORITHM_H
#define GREEDY_ALGORITHM_H

#include "../src/structure.h"  

// Function prototypes for greedy algorithms

/**
 * Solves the knapsack problem using a greedy approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runGreedyAlgorithms(const Item items[], int size, int maxWeight);

#endif // GREEDY_ALGORITHM_H
