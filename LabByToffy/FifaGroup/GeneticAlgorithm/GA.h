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

void readTestCase(const char *filename, int *numItems, Product **weight_value, int *capacity);
int **initialize_population(int population_size, int numItems);
int fitness(int *chromosome, Product *weight_value, int numItems, int capacity, int *total_weight);
void cumulation(int *fitness_values, int population_size, int *total_fitness, int *cumulative_fitness);
int roulette_wheel_selection(int total_fitness, int *cumulative_fitness, int population_size);
int determine_breakpoints(int num_items);
void crossover(int *parent1, int *parent2, int numItems, int num_breakpoints, int *child1, int *child2);
void mutate(int *chromosome, int numItems, double mutation_rate);
void elitism_selection(int **population, int *fitness_values, int population_size, int elitism_count, int **elites, int numItems);
void swap(int *a, int *b);
int partition(int *fitness_values, int *indices, int low, int high);
int quickselect(int *fitness_values, int *indices, int low, int high, int k);
int genetic_algorithm(int num_items, int capacity, Product *weight_value, int population_size, int num_generations, double mutation_rate, int elitism_count);

#endif // GA_H
