#ifndef GA_H
#define GA_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../structure.h"

#define MAX_ITEMS 1000

typedef struct {
    int fitness;
    int chromosome[1000];
} Individual;

// Test case reading function
void readTestCase(const char *filename, int *numItems, Product **weight_value, int *capacity);

// Population initialization
int **initialize_population(int population_size, int numItems);

// Fitness calculation
int fitness(int *chromosome, Product *weight_value, int numItems, int capacity, int *total_weight);

// Cumulative fitness calculation
void cumulation(int *fitness_values, int population_size, int *total_fitness, int *cumulative_fitness);

// Parent selection
int roulette_wheel_selection(int total_fitness, int *cumulative_fitness, int population_size);

// Breakpoint determination
int determine_breakpoints(int num_items);

// Crossover operation
void crossover(int *parent1, int *parent2, int numItems, int num_breakpoints, int *child1, int *child2);

// Mutation operation
void mutate(int *chromosome, int numItems, double mutation_rate);

// Elitism selection
void elitism_selection(int **population, int *fitness_values, int population_size, int elitism_count, int **elites, int numItems);

// Utility functions for selection
// Rename `swap` to `swapIntegers`
void swapIntegers(int *a, int *b);
int partitionFitness(int *fitness_values, int *indices, int low, int high);
int quickselect(int *fitness_values, int *indices, int low, int high, int k);

// Main genetic algorithm function
int genetic_algorithm(int num_items, int capacity, Product *weight_value, int population_size, int num_generations, double mutation_rate, int elitism_count);

#endif // GA_H