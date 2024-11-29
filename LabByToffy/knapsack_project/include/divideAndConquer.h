#ifndef DIVIDE_AND_CONQUER_H
#define DIVIDE_AND_CONQUER_H

#include "../src/structure.h"  

// Function prototypes for divide and conquer algorithms

/**
 * Solves a problem using divide and conquer approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runDivideAndConquer(const Item items[], int size, int maxWeight);

#endif // DIVIDE_AND_CONQUER_H
