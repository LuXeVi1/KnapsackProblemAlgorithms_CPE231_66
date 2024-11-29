#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
// #include <pthread.h>
#include "bruteforce/bruteforce.h"
#include "divideandconquer/divideandconquer.h"
#include "dynamicprogramming/dp.h"
#include "greedytechnique/greedy.h"
#include "decreaseandconquer/decreaseandconquer.h"
#include "GeneticAlgorithm/GA.h"
#include "transformandconquer/transformandconquer.h"
#include "spaceandtimetradeoff/SaTTo.h"
#include "iterativeimprovement/II.h"

// Global Array of Algorithm Names
const char *allAlgorithm[] = {
    "BruteForce", "DecreaseAndConquer", "DivideAndConquer",
    "TransformAndConquer", "SpaceAndTimeTradeOffs", "DynamicProgramming",
    "IterativeImprovement", "Greedy", "GeneticAlgorithm"
};

void generateTestCase(int n, int maxWeight, Product *products, int weightLimit, int costLimit);

int geneticAlgorithmWrapper(int numItems, int capacity, Product *products) {
    // Define default values for the additional parameters
    int population_size = 160;      // Example default value
    int num_generations = 800;    // Example default value
    float mutation_rate = 0.01;   // Example default value
    int elitism_count = (int)(0.09 * population_size);

    // Call the original genetic_algorithm function
    return genetic_algorithm(numItems, capacity, products, population_size, num_generations, mutation_rate, elitism_count);
}


// Directory Creation
void createNewDir(char *dirName) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(dirName, 150, "knapsackBF/KnapsackResults_%d-%02d-%02d_%02d-%02d-%02d/",
             t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);
    mkdir(dirName);
}

// File Creation
void createTimestampedFile(char *filename, int size, const char *algoName, const char *dirName) {
    snprintf(filename, size, "%s%s.txt", dirName, algoName);
    FILE *file = fopen(filename, "w");
    if (file) {
        fprintf(file, "Algorithm: %s\n", algoName);
        fclose(file);
    }
}

// Input Handling
void getUserInput(int *stopAlgo) {
    printf("Enter the number of test cases to execute (0 to 3): ");
    scanf("%d", stopAlgo);
}

// Product Initialization
int initializeProducts(int testCaseIndex, int *maxWeight, Product **products) {
    int n = (testCaseIndex + 1) * 25; // e.g., 25, 50, 75, 100
    *maxWeight = n * 10;
    *products = (Product *)malloc(n * sizeof(Product));
    if (!*products) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    generateTestCase(n, *maxWeight, *products, 100, 500);
    return n;
}

// Generate Test Cases
void generateTestCase(int n, int maxWeight, Product *products, int weightLimit, int costLimit) {
    for (int i = 0; i < n; i++) {
        products[i].weight = rand() % weightLimit + 1;
        products[i].cost = rand() % costLimit + 1;
        products[i].productID = i + 1;
        products[i].isPick = false;
    }
}

// Algorithm Execution
void runAllAlgorithms(int n, int maxWeight, Product *products, int *isAlgoComplete) {
    int (*algorithms[])(int, int, Product *) = {
        bruteforceKnapsack, decreaseAndConquerKnapsack, divideAndConquerKnapSack,
        fractionalKnapsack, SaTToknapsack, dynamic_programming,
        iterativeImprovementKnapsack, greedy, geneticAlgorithmWrapper
    };

    for (int i = 0; i < 9; i++) {
        if (isAlgoComplete[i]) continue;

        clock_t start = clock();
        int maxCost = algorithms[i](n, maxWeight, products);
        double timeTaken = (double)(clock() - start) / CLOCKS_PER_SEC;

        if (timeTaken > 60 * 45) {
            isAlgoComplete[i] = 1; // Skip if exceeds 45 minutes
        }

        printf("Algorithm: %s | Max Cost: %d | Time Taken: %.2lf seconds\n",
               allAlgorithm[i], maxCost, timeTaken);
    }
}

// Output to File
void writeToFile(const char *filename, const char *algoName, int maxCost, double timeTaken, int n) {
    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "Algorithm: %s\nMax Cost: %d\nTime Taken: %.2lf seconds\nTest Case Size: %d\n\n",
                algoName, maxCost, timeTaken, n);
        fclose(file);
    }
}


int main() {
    char dirName[150];
    int stopAlgo, maxWeight;
    Product *products = NULL;
    int isAlgoComplete[9] = {0}; // Tracks completion status of each algorithm

    // Create Output Directory
    createNewDir(dirName);

    // Input Handling
    getUserInput(&stopAlgo);

for (int i = 1; i <= stopAlgo; i++) {
    int n = initializeProducts(i, &maxWeight, &products);
    runAllAlgorithms(n, maxWeight, products, isAlgoComplete);
    free(products); // Clean up allocated memory
}

    return 0;
}