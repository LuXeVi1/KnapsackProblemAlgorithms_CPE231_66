#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "../src/structure.h"  

// Function prototypes for brute force algorithms

/**
 * Runs a brute force algorithm on the given items.
 * @param items Array of items to process.
 * @param size Number of items in the array.
 * @param maxWeight Maximum allowable weight.
 * @return Solution struct containing the best result.
 */
Solution runBruteForce(const Item items[], int size, int maxWeight);

#endif // BRUTEFORCE_H
