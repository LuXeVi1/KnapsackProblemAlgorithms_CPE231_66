// src/utils/inputhandler.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/utils.h"
#include "../../include/product.h"

Product* manualInputProducts(int* n, int* maxWeight) {
    printf("Enter number of products: ");
    scanf("%d", n);

    if (*n <= 0) {
        printf("Invalid number of products.\n");
        return NULL;
    }

    Product* products = malloc(*n * sizeof(Product));
    if (!products) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    printf("Enter products [weight cost] (e.g., 10 20):\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d %d", &products[i].weight, &products[i].cost);
        products[i].productID = i + 1;
        products[i].isPick = 0;
    }

    printf("Enter maximum weight capacity: ");
    scanf("%d", maxWeight);

    return products;
}

Product* loadPredefinedTestCase(int* n, int* maxWeight) {
    const char* testCaseFiles[] = {
        "testcase/25.txt", 
        "testcase/50.txt", 
        "testcase/100.txt"
    };

    int caseChoice;
    printf("Select Test Case:\n");
    printf("0: 25 Parameters\n1: 50 Parameters\n2: 100 Parameters\n");
    scanf("%d", &caseChoice);

    if (caseChoice < 0 || caseChoice > 2) {
        printf("Invalid choice.\n");
        return NULL;
    }

    FILE* fp = fopen(testCaseFiles[caseChoice], "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", testCaseFiles[caseChoice]);
        return NULL;
    }

    fscanf(fp, "%d", n);
    Product* products = malloc(*n * sizeof(Product));
    if (!products) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        return NULL;
    }

    for (int i = 0; i < *n; i++) {
        fscanf(fp, "%d %d", &products[i].weight, &products[i].cost);
        products[i].productID = i + 1;
        products[i].isPick = 0;
    }

    fscanf(fp, "%d", maxWeight);
    fclose(fp);

    return products;
}

Product* generateRandomTestCase(int* n, int* maxWeight) {
    printf("Enter number of products: ");
    scanf("%d", n);

    printf("Enter max weight capacity: ");
    scanf("%d", maxWeight);

    int weightLimit, costLimit;
    printf("Enter max product weight and cost (e.g., 20 50): ");
    scanf("%d %d", &weightLimit, &costLimit);

    Product* products = malloc(*n * sizeof(Product));
    if (!products) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    srand(time(NULL));
    for (int i = 0; i < *n; i++) {
        products[i].weight = rand() % weightLimit + 1;
        products[i].cost = rand() % costLimit + 1;
        products[i].productID = i + 1;
        products[i].isPick = 0;
    }

    return products;
}

void generateTimestampedFilename(char* filename, size_t size, int params) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    snprintf(filename, size, "results/%02d%02d%02d_%02d%02d%02d_%dparameters.txt", 
             t->tm_year % 100, t->tm_mon + 1, t->tm_mday, 
             t->tm_hour, t->tm_min, t->tm_sec, params);
}

void writeAlgorithmResults(const char* filename, const char* algorithmName, 
                            int maxCost, double timeTaken, int n) {
    FILE* file = fopen(filename, "a");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "\nAlgorithm: %s\n", algorithmName);
    fprintf(file, "Number of Products: %d\n", n);
    fprintf(file, "Maximum cost: %d\n", maxCost);
    fprintf(file, "Run time: %lf seconds\n", timeTaken);
    fprintf(file, "==============================================\n");

    fclose(file);
}

void runAlgorithmComparisons(Product* products, int n, int maxWeight, const char* filename) {
    clock_t start, end;
    double cpu_time_used;
    int maxCost;

    // Example of running and comparing multiple algorithms
    printf("Running Algorithm Comparisons:\n");

    // Bruteforce Algorithm
    start = clock();
    maxCost = bruteforceKnapsack(n, maxWeight, products);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Bruteforce - Max Cost: %d, Time: %lf seconds\n", maxCost, cpu_time_used);
    writeAlgorithmResults(filename, "Bruteforce", maxCost, cpu_time_used, n);

    // Add other algorithm calls similarly...
    // Dynamic Programming
    start = clock();
    maxCost = dynamic_programming(n, maxWeight, products);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Dynamic Programming - Max Cost: %d, Time: %lf seconds\n", maxCost, cpu_time_used);
    writeAlgorithmResults(filename, "Dynamic Programming", maxCost, cpu_time_used, n);

    // Add more algorithms as needed...
}