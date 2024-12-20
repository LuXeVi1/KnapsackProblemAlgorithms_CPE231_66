#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "bruteforce/bruteforce.h"
#include "divideandconquer/divideandconquer.h"
#include "dynamicprogramming/dynamicprogramming.h"
#include "greedytechnique/greedytechnique.h"
#include "decreaseandconquer/decreaseandconquer.h"
#include "GeneticAlgorithm/GeneticAlgorithm.h"
#include "transformandconquer/transformandconquer.h"
#include "spaceandtimetradeoff/spaceandtimetradeoff.h"
#include "iterativeimprovement/iterativeimprovement.h"

void generateTestCase(int n, int maxWeight, Product* products, int weightLimit, int costLimit);
void writeToFile(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n);
void createTimestampedFile(char *filename, size_t filename_size, int params, const char *role , Product *products ,int maxWeight , int n);
void getDeviceModel(char *deviceModel, size_t size);
void writeToFileForGA(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n,int elitism_count , float mutation_rate ,int num_generations , int population_size);
void runAlgorithms(const char *filename, int n, int maxWeight, Product *products);

int main() {
    int n, maxWeight, choice, isLoop = 0;
    Product *products = NULL;
    char filename[150];

    do {
        printf("|||| Enter Your Choice ||||\n");
        printf("0 : To Enter Your Testcase\n");
        printf("1 : To use TA Testcase\n");
        printf("2 : To use Random Testcase\n");
        printf("Enter Number : ");
        scanf("%d", &choice);

        if (choice == 0) {
            printf("Enter your Product quantity : ");
            scanf("%d", &n);
            if (n <= 0) {
                printf("No products available.\n");
                return 0;
            }
            products = (Product *)malloc(n * sizeof(Product));
            if (products == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }
            printf("Enter all your Product [weight cost] (eg. 10 20)\n");
            for (int i = 0; i < n; i++) {
                scanf("%d %d", &products[i].weight, &products[i].cost);
                products[i].productID = i + 1;
                products[i].isPick = 0;
            }
            printf("Enter your weight capacity : ");
            scanf("%d", &maxWeight);

            createTimestampedFile(filename, sizeof(filename), n, "User", products, maxWeight, n);
        } else if (choice == 1) {
            int caseTA;
            printf("||||What Testcase you want to test with||||\n0 : 25 Parameters\n1 : 50 Parameters\n2 : 100 Parameters\nEnter Number : ");
            scanf("%d", &caseTA);

            const char *testCaseFiles[] = {"testcase/25.txt", "testcase/50.txt", "testcase/100.txt"};
            if (caseTA < 0 || caseTA > 2) {
                printf("Invalid choice. Exiting.\n");
                return 1;
            }

            FILE *fp = fopen(testCaseFiles[caseTA], "r");
            if (fp == NULL) {
                printf("Error: Could not open file %s\n", testCaseFiles[caseTA]);
                return 1;
            }
            fscanf(fp, "%d", &n);
            products = (Product *)malloc(n * sizeof(Product));
            if (products == NULL) {
                printf("Memory allocation failed.\n");
                fclose(fp);
                return 1;
            }
            for (int i = 0; i < n; i++) {
                fscanf(fp, "%d %d", &products[i].weight, &products[i].cost);
                products[i].productID = i + 1;
                products[i].isPick = 0;
            }
            fscanf(fp, "%d", &maxWeight);
            fclose(fp);

            createTimestampedFile(filename, sizeof(filename), n, "TA", products, maxWeight, n);
        } else if (choice == 2) {
            printf("Enter number of products: ");
            scanf("%d", &n);
            printf("Enter max weight capacity: ");
            scanf("%d", &maxWeight);
            int weightLimit, costLimit;
            printf("Enter max product weight and cost (e.g., 20 50): ");
            scanf("%d %d", &weightLimit, &costLimit);

            products = (Product *)malloc(n * sizeof(Product));
            if (products == NULL) {
                printf("Memory allocation failed.\n");
                return 1;
            }
            generateTestCase(n, maxWeight, products, weightLimit, costLimit);

            createTimestampedFile(filename, sizeof(filename), n, "Random", products, maxWeight, n);
        } else {
            printf("Please Enter Number 0, 1, or 2!\n");
            continue;
        }

        printf("================================================ Output ================================================\n");
        runAlgorithms(filename, n, maxWeight, products);
        printf("================================================ End Process ================================================\n");

        do {
            printf("|||| Do you want to run again? ||||\n");
            printf("0 : To Exit\n1 : To Do Again\nEnter Number: ");
            scanf("%d", &isLoop);
            if (isLoop != 1 && isLoop != 0) {
                printf("Please Enter Number 0 or 1!\n");
            }
        } while (isLoop != 1 && isLoop != 0);
    } while (isLoop == 1);

    free(products);
    return 0;
}

void runAlgorithms(const char *filename, int n, int maxWeight, Product *products) {
    clock_t t;
    double time_taken;
    int maxCost;

    // Bruteforce
    t = clock();
    maxCost = bruteforceKnapsack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    if (maxCost != -1) {
        printf("Maximum cost: %d\n", maxCost);
        printf("Run time of Bruteforce is %lf second\n", time_taken);
        writeToFile(filename, "Bruteforce", maxCost, time_taken, n);
    }

    // Decrease and Conquer
    t = clock();
    maxCost = decreaseAndConquerKnapsack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Decrease and Conquer is %lf second\n", time_taken);
    writeToFile(filename, "Decrease and Conquer", maxCost, time_taken, n);

    // Divide and Conquer
    t = clock();
    maxCost = divideAndConquerKnapSack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Divide and Conquer is %lf second\n", time_taken);
    writeToFile(filename, "Divide and Conquer", maxCost, time_taken, n);

    // Transform and Conquer
    t = clock();
    maxCost = fractionalKnapsack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Transform and Conquer is %lf second\n", time_taken);
    writeToFile(filename, "Transform and Conquer", maxCost, time_taken, n);

    // Space & Time Trade-Offs
    t = clock();
    maxCost = SaTToknapsack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Space & Time Trade-Offs is %lf second\n", time_taken);
    writeToFile(filename, "Space & Time Trade-Offs", maxCost, time_taken, n);

    // Dynamic Programming
    t = clock();
    maxCost = dynamic_programming(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Dynamic Programming is %lf second\n", time_taken);
    writeToFile(filename, "Dynamic Programming", maxCost, time_taken, n);

    // Iterative Improvement
    t = clock();
    maxCost = iterativeImprovementKnapsack(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Iterative Improvement is %lf second\n", time_taken);
    writeToFile(filename, "Iterative Improvement", maxCost, time_taken, n);

    // Greedy
    t = clock();
    maxCost = greedy(n, maxWeight, products);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Greedy is %lf second\n", time_taken);
    writeToFile(filename, "Greedy", maxCost, time_taken, n);

    // Genetic Algorithm
    t = clock();
    int population_size = 151;
    int num_generations = 900;
    float mutation_rate = 0.01;
    int elitism_count = (int)(0.09 * population_size);
    srand(time(NULL));
    maxCost = genetic_algorithm(n, maxWeight, products, population_size, num_generations, mutation_rate, elitism_count);
    t = clock() - t;
    time_taken = ((double)t) / CLOCKS_PER_SEC;
    printf("Maximum cost: %d\n", maxCost);
    printf("Run time of Genetic Algorithm is %lf second\n", time_taken);
    writeToFileForGA(filename, "Genetic Algorithm", maxCost, time_taken, n, elitism_count, mutation_rate, num_generations, population_size);
}

void getDeviceModel(char *deviceModel, size_t size) {
#ifdef _WIN32
    FILE *fp = popen("wmic computersystem get model", "r");
    if (fp == NULL) {
        snprintf(deviceModel, size, "UnknownDevice");
        return;
    }
    fgets(deviceModel, size, fp); // Skip header line
    fgets(deviceModel, size, fp); // Read the actual model
    pclose(fp);
#elif __APPLE__
    FILE *fp = popen("sysctl -n hw.model", "r");
    if (fp == NULL) {
        snprintf(deviceModel, size, "UnknownDevice");
        return;
    }
    fgets(deviceModel, size, fp);
    pclose(fp);
#elif __linux__
    FILE *fp = fopen("/sys/devices/virtual/dmi/id/product_name", "r");
    if (fp == NULL) {
        snprintf(deviceModel, size, "UnknownDevice");
        return;
    }
    fgets(deviceModel, size, fp);
    fclose(fp);
#else
    snprintf(deviceModel, size, "UnknownDevice");
#endif

    size_t len = strlen(deviceModel);
    if (len > 0 && deviceModel[len - 1] == '\n') {
        deviceModel[len - 1] = '\0';
    }
}

void createTimestampedFile(char *filename, size_t filename_size, int params, const char *role, Product *products, int maxWeight, int n) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    snprintf(filename, filename_size, "results/%02d%02d%02d_%02d%02d%02d_%s%dparameters.txt", t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, role, params);

    char deviceModel[100] = {0};
    getDeviceModel(deviceModel, sizeof(deviceModel));

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }

    fprintf(file, "Device: %s\n", deviceModel);
    fprintf(file, "\nInput Data:\n");
    for (int i = 0; i < n; i++) {
        fprintf(file, "Product %d: Weight = %d, Cost = %d\n", products[i].productID, products[i].weight, products[i].cost);
    }
    fprintf(file, "Max Weight: %d\n", maxWeight);
    fclose(file);
}

void writeToFile(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "\nAlgorithm: %s\n", algorithmName);
    fprintf(file, "Maximum cost: %d\n", maxCost);
    fprintf(file, "Run time: %lf seconds\n", timeTaken);
    fprintf(file, "==============================================\n");

    fclose(file);
}

void writeToFileForGA(const char *filename, const char *algorithmName, int maxCost, double timeTaken, int n, int elitism_count, float mutation_rate, int num_generations, int population_size) {
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    fprintf(file, "\nAlgorithm: %s\n", algorithmName);
    fprintf(file, "Population Size: %d\n", population_size);
    fprintf(file, "Generations Quantity: %d\n", num_generations);
    fprintf(file, "Mutation Rate: %f\n", mutation_rate);
    fprintf(file, "Elitism Size: %d\n", elitism_count);
    fprintf(file, "\nMaximum cost: %d\n", maxCost);
    fprintf(file, "Run time: %lf seconds\n", timeTaken);
    fprintf(file, "==============================================\n");

    fclose(file);
}

void generateTestCase(int n, int maxWeight, Product* products, int weightLimit, int costLimit) {
    for (int i = 0; i < n; i++) {
        products[i].weight = rand() % weightLimit + 1;
        products[i].cost = rand() % costLimit + 1;
        products[i].productID = i + 1;
        products[i].isPick = false;
    }
}