#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bruteforce/bruteforce.h"
#include "divideandconquer/divideandconquer.h"
#include "dynamicprogramming/dp.h"
#include "greedytechnique/greedy.h"
#include "decreaseandconquer/decreaseandconquer.h"
#include "GeneticAlgorithm/GA.h"
#include "transformandconquer/transformandconquer.h"
#include "spaceandtimetradeoff/SaTTo.h"
#include "iterativeimprovement/II.h"

// Function declarations
void generateTestCase(int n, int maxWeight, Product* products, int weightLimit, int costLimit);
void writeToFile(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n);
void createTimestampedFile(char *filename, size_t filename_size, const char *role, Product *products, int maxWeight, int n);
void getDeviceModel(char *deviceModel, size_t size);
void writeToFileForGA(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n, int elitism_count, float mutation_rate, int num_generations, int population_size);

// Helper function to allocate memory for products
Product* allocateProducts(int n) {
    Product* products = (Product *)malloc(n * sizeof(Product));
    if (!products) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return products;
}

// Helper function to process user inputs
void processUserInput(int *n, int *maxWeight, Product **products) {
    printf("Enter your Product quantity: ");
    scanf("%d", n);
    if (*n <= 0) {
        printf("No products available.\n");
        exit(EXIT_SUCCESS);
    }
    *products = allocateProducts(*n);

    printf("Enter all your Products [weight cost] (e.g., 10 20):\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d %d", &(*products)[i].weight, &(*products)[i].cost);
        (*products)[i].productID = i + 1;
        (*products)[i].isPick = 0;
    }

    printf("Enter your weight capacity: ");
    scanf("%d", maxWeight);
}

// Helper function to load test case from file
void loadTestCase(const char *filename, int *n, int *maxWeight, Product **products) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    fscanf(fp, "%d", n); // Read number of products
    *products = allocateProducts(*n);

    for (int i = 0; i < *n; i++) {
        fscanf(fp, "%d %d", &(*products)[i].weight, &(*products)[i].cost);
        (*products)[i].productID = i + 1;
        (*products)[i].isPick = 0;
    }
    fscanf(fp, "%d", maxWeight); // Read max weight
    fclose(fp);
}

// Helper function to execute an algorithm and log results
void executeAlgorithm(const char *algorithmName, int (*algorithm)(int, int, Product*), 
                      const char *filename, int n, int maxWeight, Product *products) {
    clock_t start = clock();
    int maxCost = algorithm(n, maxWeight, products);
    double timeTaken = (double)(clock() - start) / CLOCKS_PER_SEC;

    printf("Algorithm: %s\n", algorithmName);
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time: %.6lf seconds\n", timeTaken);

    writeToFile(filename, algorithmName, maxCost, timeTaken, n);
}

int main() {
    int n, maxWeight, choice;
    Product *products = NULL;
    char filename[150];

    while (true) {
        printf("|||| Enter Your Choice ||||\n");
        printf("0 : To Enter Your Testcase\n");
        printf("1 : To use TA Testcase\n");
        printf("2 : To use Random Testcase\n");
        printf("3 : Exit\n");
        printf("Enter Number: ");
        scanf("%d", &choice);

        if (choice == 0) {
            processUserInput(&n, &maxWeight, &products);
            createTimestampedFile(filename, sizeof(filename), "User", products, maxWeight, n);
        } else if (choice == 1) {
            printf("|||| Select TA Testcase ||||\n");
            printf("0 : 25 Parameters\n1 : 50 Parameters\n2 : 100 Parameters\n");
            int caseTA;
            scanf("%d", &caseTA);

            const char *testCaseFiles[] = {"testcase/25.txt", "testcase/50.txt", "testcase/100.txt"};
            if (caseTA < 0 || caseTA >= 3) {
                printf("Invalid choice. Try again.\n");
                continue;
            }
            loadTestCase(testCaseFiles[caseTA], &n, &maxWeight, &products);
            createTimestampedFile(filename, sizeof(filename), "TA", products, maxWeight, n);
        } else if (choice == 2) {
            int weightLimit, costLimit;
            printf("Enter number of products: ");
            scanf("%d", &n);
            printf("Enter max weight capacity: ");
            scanf("%d", &maxWeight);
            printf("Enter max product weight and cost (e.g., 20 50): ");
            scanf("%d %d", &weightLimit, &costLimit);

            products = allocateProducts(n);
            generateTestCase(n, maxWeight, products, weightLimit, costLimit);
            createTimestampedFile(filename, sizeof(filename), "Random", products, maxWeight, n);
        } else if (choice == 3) {
            printf("Exiting program.\n");
            break;
        } else {
            printf("Invalid choice. Please select 0, 1, 2, or 3.\n");
            continue;
        }

        // Run algorithms and log results
        printf("================================================ Output ================================================\n");
        executeAlgorithm("Bruteforce", bruteforceKnapsack, filename, n, maxWeight, products);
        executeAlgorithm("Decrease and Conquer", decreaseAndConquerKnapsack, filename, n, maxWeight, products);
        executeAlgorithm("Divide and Conquer", divideAndConquerKnapSack, filename, n, maxWeight, products);
        executeAlgorithm("Transform and Conquer", fractionalKnapsack, filename, n, maxWeight, products);
        executeAlgorithm("Space & Time Trade-Offs", SaTToknapsack, filename, n, maxWeight, products);
        executeAlgorithm("Dynamic Programming", dynamic_programming, filename, n, maxWeight, products);
        executeAlgorithm("Iterative Improvement", iterativeImprovementKnapsack, filename, n, maxWeight, products);
        executeAlgorithm("Greedy", greedy, filename, n, maxWeight, products);

        // Special handling for Genetic Algorithm
        printf("Running Genetic Algorithm...\n");
        int population_size = 151, num_generations = 900;
        float mutation_rate = 0.01;
        int elitism_count = (int)(0.09 * population_size);
        srand(time(NULL));
        executeAlgorithm("Genetic Algorithm", 
                         (int (*)(int, int, Product*))genetic_algorithm, 
                         filename, n, maxWeight, products);
        printf("================================================ End Process ================================================\n");

        // Cleanup
        free(products);
        products = NULL;
    }

    return 0;
}


// Function to write results to the file
void writeToFile(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n)
{
    FILE *file = fopen(filename, "a"); // Use "a" to append to the file
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

        // Write algorithm results
    fprintf(file, "\nAlgorithm: %s\n", algorithmName);
    fprintf(file, "Maximum Cost: %d\n", maxCost);
    fprintf(file, "Time Taken: %.6lf seconds\n", timeTaken);
    fclose(file);
}

// Function to write results specific to Genetic Algorithm
void writeToFileForGA(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n,
                      int elitism_count, float mutation_rate, int num_generations, int population_size)
{
    FILE *file = fopen(filename, "a"); // Use "a" to append to the file
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    // Write genetic algorithm results
    fprintf(file, "\nAlgorithm: %s\n", algorithmName);
    fprintf(file, "Maximum Cost: %d\n", maxCost);
    fprintf(file, "Time Taken: %.6lf seconds\n", timeTaken);
    fprintf(file, "Population Size: %d\n", population_size);
    fprintf(file, "Number of Generations: %d\n", num_generations);
    fprintf(file, "Mutation Rate: %.2f%%\n", mutation_rate * 100);
    fprintf(file, "Elitism Count: %d\n", elitism_count);
    fclose(file);
}

// Function to generate random test cases
void generateTestCase(int n, int maxWeight, Product *products, int weightLimit, int costLimit)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        products[i].weight = rand() % weightLimit + 1; // Random weight [1, weightLimit]
        products[i].cost = rand() % costLimit + 1;     // Random cost [1, costLimit]
        products[i].productID = i + 1;
        products[i].isPick = 0;
    }
}
