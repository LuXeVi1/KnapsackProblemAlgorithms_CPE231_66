#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Function to log the execution details
void logExecution(const char *filename, const char *algorithmName, int capacity, int n, int *weights, int *values, int result) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Algorithm: %s\n", algorithmName);
    fprintf(file, "Knapsack Capacity: %d, Items: %d\n", capacity, n);
    fprintf(file, "Weights and Values:\n");

    for (int i = 0; i < n; i++) {
        fprintf(file, "Item %d: Weight = %d, Value = %d\n", i + 1, weights[i], values[i]);
    }

    fprintf(file, "Maximum Value: %d\n", result);
    fprintf(file, "------------------------------------\n");

    fclose(file);
}
