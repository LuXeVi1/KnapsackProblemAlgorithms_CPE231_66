#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Function to read the knapsack problem's input from a file
void readInputFromFile(const char *filename, int *n, int *capacity, int **weights, int **values) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    // Read number of items and capacity
    fscanf(file, "%d %d", n, capacity);

    // Allocate memory for weights and values
    *weights = (int *)malloc(*n * sizeof(int));
    *values = (int *)malloc(*n * sizeof(int));

    // Read weights and values
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d %d", &(*weights)[i], &(*values)[i]);
    }

    fclose(file);
}

// Function to write the results to a file
void writeOutputToFile(const char *filename, int result) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "Maximum value: %d\n", result);
    fclose(file);
}
