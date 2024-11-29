#ifndef ITERATIVE_IMPROVEMENT_H
#define ITERATIVE_IMPROVEMENT_H

#include "../src/structure.h"  

// Function prototypes for iterative improvement algorithms

/**
 * Improves an initial solution iteratively.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the improved result.
 */
Solution runIterativeImprovement(const Item items[], int size, int maxWeight);

#endif // ITERATIVE_IMPROVEMENT_H
