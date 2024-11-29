#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "bruteforce/bruteforce.h"
#include "decreaseandconquer/decreaseandconquer.h"
#include "divideandconquer/divideandconquer.h"
#include "dynamicprogramming/dynamicprogramming.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "greedytechnique/greedytechnique.h"
#include "iterativeimprovement/iterativeimprovement.h"
#include "spaceandtimetradeoff/spaceandtimetradeoff.h"
#include "transformandconquer/transformandconquer.h"

int main() {
    int capacity, n;
    int *weights, *values;

    // Read test case
    readTestCase("testcase/25.txt", &capacity, &n, &weights, &values);

    // Call different algorithms
    int result;

    result = knapsackBruteforce(capacity, n, weights, values);
    printf("Brute Force Result: %d\n", result);

    result = knapsackDecreaseAndConquer(capacity, n, weights, values);
    printf("Decrease and Conquer Result: %d\n", result);

    result = knapsackDivideAndConquer(capacity, n, weights, values);
    printf("Divide and Conquer Result: %d\n", result);

    result = knapsackDynamicProgramming(capacity, n, weights, values);
    printf("Dynamic Programming Result: %d\n", result);

    result = knapsackGeneticAlgorithm(capacity, n, weights, values);
    printf("Genetic Algorithm Result: %d\n", result);

    result = knapsackGreedy(capacity, n, weights, values);
    printf("Greedy Technique Result: %d\n", result);

    result = knapsackIterativeImprovement(capacity, n, weights, values);
    printf("Iterative Improvement Result: %d\n", result);

    result = knapsackSpaceTimeTradeoff(capacity, n, weights, values);
    printf("Space-Time Tradeoff Result: %d\n", result);

    result = knapsackTransformAndConquer(capacity, n, weights, values);
    printf("Transform and Conquer Result: %d\n", result);

    // Free allocated memory
    free(weights);
    free(values);

    return 0;
}

void readTestCase(const char *filename, int *capacity, int *n, int **weights, int **values) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d %d", capacity, n);
    *weights = (int *)malloc(*n * sizeof(int));
    *values = (int *)malloc(*n * sizeof(int));

    for (int i = 0; i < *n; i++) {
        fscanf(file, "%d %d", &(*weights)[i], &(*values)[i]);
    }

    fclose(file);
}
