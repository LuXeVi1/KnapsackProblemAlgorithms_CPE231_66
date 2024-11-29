#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Function to generate random test cases
void generateRandomTestCase(const char *filename, int n, int capacity) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    // Write number of items and capacity
    fprintf(file, "%d %d\n", n, capacity);

    // Generate random weights and values
    srand(time(NULL));  // Seed the random number generator
    for (int i = 0; i < n; i++) {
        int weight = rand() % (capacity + 1);  // Random weight between 0 and capacity
        int value = rand() % 100 + 1;  // Random value between 1 and 100
        fprintf(file, "%d %d\n", weight, value);
    }

    fclose(file);
}
