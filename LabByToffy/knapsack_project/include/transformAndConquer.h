#ifndef TRANSFORM_AND_CONQUER_H
#define TRANSFORM_AND_CONQUER_H

#include "../src/structure.h"  

// Function prototypes for transform and conquer algorithms

/**
 * Solves a problem using a transform and conquer approach.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runTransformAndConquer(const Item items[], int size, int maxWeight);

#endif // TRANSFORM_AND_CONQUER_H
