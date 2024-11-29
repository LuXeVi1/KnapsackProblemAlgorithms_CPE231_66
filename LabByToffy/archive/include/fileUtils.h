#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include "../src/structure.h"  

// Function prototypes for file handling utilities

/**
 * Reads items from a file.
 * @param filename The name of the file to read.
 * @param items Array to store the read items.
 * @return The number of items read.
 */
int readItemsFromFile(const char *filename, Item items[]);

/**
 * Writes a solution to a file.
 * @param filename The name of the file to write.
 * @param solution The solution to write.
 * @param size The number of items considered.
 */
void writeSolutionToFile(const char *filename, const Solution *solution, int size);

#endif // FILE_UTILS_H
