#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>
#include <sys/stat.h>
#include "structure.h"
#include "GeneticAlgorithm/GA.h"

#define NUM_TOP_RESULTS 1000
#define NUM_THREADS 4 // Number of threads

typedef struct {
    int maxCost;
    int population_size;
    int num_generations;
    float mutation_rate;
    float elitism_rate;
    double time_taken;
} Result;

// Shared top results and mutex for thread safety
Result topResults[NUM_TOP_RESULTS] = {{INT_MIN, 0, 0, 0.0, 0.0, 0.0}};
pthread_mutex_t mutex;

// Function to update top results
void updateTopResults(Result newResult) {
    pthread_mutex_lock(&mutex); // Lock the mutex
    for (int i = NUM_TOP_RESULTS - 1; i >= 0; i--) {
        if (newResult.maxCost > topResults[i].maxCost) {
            if (i < NUM_TOP_RESULTS - 1) {
                topResults[i + 1] = topResults[i];
            }
            topResults[i] = newResult;
        } else {
            break;
        }
    }
    pthread_mutex_unlock(&mutex); // Unlock the mutex
}

// Function to write top results to a file
void writeTopResultsToFile(int n) {
    char filename[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(filename, sizeof(filename), "results/top_results_%02d%02d%02d_%02d%02d%02d.txt",
             t->tm_year % 100, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }

    fprintf(file, "Top %d Genetic Algorithm Results:\n", NUM_TOP_RESULTS);
    fprintf(file, "%d Parameters\n" , n);
    fprintf(file, "---------------------------------\n");
    for (int i = 0; i < NUM_TOP_RESULTS; i++) {
        fprintf(file, "Cost: %d, Pop Size: %d, Generations: %d, Mutation Rate: %.2f, Elitism Rate: %.2f, Time: %.2lf sec\n",
                topResults[i].maxCost,
                topResults[i].population_size,
                topResults[i].num_generations,
                topResults[i].mutation_rate,
                topResults[i].elitism_rate,
                topResults[i].time_taken);
    }

    fclose(file);
    printf("Top results saved to %s\n", filename);
}

// Thread data structure
typedef struct {
    int thread_id;
    int n;
    Product *products;
    int maxWeight;
    int population_size_start;
    int population_size_end;
    int maxRunning;
} ThreadData;

// Thread function
void *threadFunc(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    int count = 0;
    clock_t t;

    for (int population_size = data->population_size_start; population_size < data->population_size_end; population_size += 10) {
        for (int num_generations = 500; num_generations <= 1000; num_generations += 20) {
            for (float mutation_rate = 0.01; mutation_rate <= 0.05; mutation_rate += 0.01) {
                for (float elitism_rate = 0.01; elitism_rate <= 0.1; elitism_rate += 0.01) {
                    int elitism_count = (int)(elitism_rate * population_size);
                    count++;

                    // Run genetic algorithm
                    t = clock();
                    int maxCost = genetic_algorithm(data->n, data->products, data->maxWeight, population_size, num_generations, mutation_rate, elitism_count);
                    t = clock() - t;
                    double time_taken = ((double)t) / CLOCKS_PER_SEC;

                    // Create a result structure
                    Result newResult = {maxCost, population_size, num_generations, mutation_rate, elitism_rate, time_taken};

                    // Update top results
                    updateTopResults(newResult);

                    // Print progress
                    printf("Thread %d: %.3f%% Finished case %d %d %.3f %.3f\n",
                           data->thread_id,(count * 100.0 / data->maxRunning), population_size, num_generations, mutation_rate, elitism_rate);
                }
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    int n, maxWeight ,i=0 ;
    Product *products = NULL;
    const char *testcase[] = {"testcase/25.txt", "testcase/50.txt", "testcase/100.txt"};
    for(int i = 0 ; i <= 2 ; i++){
    FILE *fp = fopen(testcase[i], "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", testcase[i]);
        return 1;
    }
    fscanf(fp, "%d", &n); // Read number of products
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
    fscanf(fp, "%d", &maxWeight); // Read max weight
    fclose(fp);

    pthread_t threads[NUM_THREADS];
    ThreadData threadData[NUM_THREADS];
    int population_size_step = 1;
    int totalCases = 15600; // Total iterations

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadData[i].thread_id = i;
        threadData[i].n = n;
        threadData[i].products = products;
        threadData[i].maxWeight = maxWeight;
        threadData[i].population_size_start = 50 + i * population_size_step;
        threadData[i].population_size_end = (i == NUM_THREADS - 1) ? 160 : threadData[i].population_size_start + population_size_step;
        threadData[i].maxRunning = totalCases / NUM_THREADS;
        pthread_create(&threads[i], NULL, threadFunc, &threadData[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print top results
    printf("Top %d Results:\n", NUM_TOP_RESULTS);
    for (int i = 0; i < NUM_TOP_RESULTS; i++) {
        printf("Cost: %d, Pop Size: %d, Generations: %d, Mutation Rate: %.2f, Elitism Rate: %.2f, Time: %.2lf sec\n",
               topResults[i].maxCost,
               topResults[i].population_size,
               topResults[i].num_generations,
               topResults[i].mutation_rate,
               topResults[i].elitism_rate,
               topResults[i].time_taken);
    }

    // Write results to file
    writeTopResultsToFile(n);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);
    free(products);
}
    return 0;
}