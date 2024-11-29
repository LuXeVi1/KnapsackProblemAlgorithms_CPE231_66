#include "GeneticAlgorithm.h"

// Utility functions
static int max(int a, int b) { return a > b ? a : b; }

// Initialize population with random binary chromosomes
static int** create_population(int population_size, int num_items) {
    int** population = malloc(population_size * sizeof(int*));
    for (int i = 0; i < population_size; i++) {
        population[i] = malloc(num_items * sizeof(int));
        for (int j = 0; j < num_items; j++) {
            population[i][j] = rand() % 2;
        }
    }
    return population;
}

/ Swap integers
void swapIntegers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function for fitness values
int partitionFitness(int *fitness_values, int *indices, int low, int high) {
    int pivot = fitness_values[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (fitness_values[j] > pivot) { // Descending order
            i++;
            swapIntegers(&fitness_values[i], &fitness_values[j]);
            swapIntegers(&indices[i], &indices[j]);
        }
    }
    swapIntegers(&fitness_values[i + 1], &fitness_values[high]);
    swapIntegers(&indices[i + 1], &indices[high]);
    return i + 1;
}

// Calculate fitness of a chromosome
static int calculate_fitness(int* chromosome, Product* items, int num_items, int capacity, int* total_weight) {
    int total_value = 0;
    *total_weight = 0;

    for (int i = 0; i < num_items; i++) {
        if (chromosome[i]) {
            *total_weight += items[i].weight;
            total_value += items[i].value;
        }
    }
    
    return (*total_weight <= capacity) ? total_value : 0;
}

// Roulette wheel selection
static int select_parent(int total_fitness, int* cumulative_fitness, int population_size) {
    int random_value = rand() % total_fitness;
    for (int i = 0; i < population_size; i++) {
        if (random_value <= cumulative_fitness[i]) {
            return i;
        }
    }
    return population_size - 1;
}

// Crossover with adaptive breakpoints
static void perform_crossover(int* parent1, int* parent2, int num_items, int* child1, int* child2) {
    int num_breakpoints = (num_items <= 50) ? 2 : 
                          (num_items <= 100) ? 3 : 
                          (num_items <= 500) ? 4 : 9;
    
    int breakpoints[num_breakpoints + 2];
    breakpoints[0] = 0;
    breakpoints[num_breakpoints + 1] = num_items;

    // Generate random sorted breakpoints
    for (int i = 1; i <= num_breakpoints; i++) {
        breakpoints[i] = rand() % (num_items - 1) + 1;
    }
    qsort(breakpoints, num_breakpoints + 2, sizeof(int), 
          (int (*)(const void*, const void*))compare_ints);

    int toggle = 0;
    for (int i = 0; i < num_breakpoints + 1; i++) {
        for (int j = breakpoints[i]; j < breakpoints[i + 1]; j++) {
            child1[j] = toggle ? parent2[j] : parent1[j];
            child2[j] = toggle ? parent1[j] : parent2[j];
        }
        toggle = 1 - toggle;
    }
}

// Mutation with adaptive rate
static void mutate_chromosome(int* chromosome, int num_items, double mutation_rate) {
    for (int i = 0; i < num_items; i++) {
        if ((double)rand() / RAND_MAX < mutation_rate) {
            chromosome[i] = 1 - chromosome[i];
        }
    }
}

int genetic_algorithm(int num_items, int capacity, Product* items, 
                      int population_size, int generations, 
                      double mutation_rate, int elitism_count) {
    srand(time(NULL));  // Seed random number generator

    int** population = create_population(population_size, num_items);
    int best_fitness = 0;
    int* best_solution = malloc(num_items * sizeof(int));

    for (int gen = 0; gen < generations; gen++) {
        int* fitness_values = malloc(population_size * sizeof(int));
        int* weights = malloc(population_size * sizeof(int));

        // Evaluate fitness of current population
        for (int i = 0; i < population_size; i++) {
            fitness_values[i] = calculate_fitness(population[i], items, num_items, capacity, &weights[i]);
        }

        // Track best solution
        for (int i = 0; i < population_size; i++) {
            if (fitness_values[i] > best_fitness) {
                best_fitness = fitness_values[i];
                memcpy(best_solution, population[i], num_items * sizeof(int));
            }
        }

        // Create new population
        int** new_population = create_population(population_size, num_items);
        int new_pop_index = 0;

        // Elitism: copy best chromosomes
        for (int i = 0; i < elitism_count; i++) {
            int best_index = 0;
            for (int j = 1; j < population_size; j++) {
                if (fitness_values[j] > fitness_values[best_index]) {
                    best_index = j;
                }
            }
            memcpy(new_population[new_pop_index++], population[best_index], num_items * sizeof(int));
        }

        // Crossover and mutation for remaining population
        while (new_pop_index < population_size) {
            int parent1 = select_parent(best_fitness, fitness_values, population_size);
            int parent2 = select_parent(best_fitness, fitness_values, population_size);

            int* child1 = malloc(num_items * sizeof(int));
            int* child2 = malloc(num_items * sizeof(int));

            perform_crossover(population[parent1], population[parent2], num_items, child1, child2);

            mutate_chromosome(child1, num_items, mutation_rate);
            mutate_chromosome(child2, num_items, mutation_rate);

            memcpy(new_population[new_pop_index++], child1, num_items * sizeof(int));
            if (new_pop_index < population_size) {
                memcpy(new_population[new_pop_index++], child2, num_items * sizeof(int));
            }

            free(child1);
            free(child2);
        }

        // Free old population and update
        for (int i = 0; i < population_size; i++) {
            free(population[i]);
        }
        free(population);
        population = new_population;

        // Cleanup
        free(fitness_values);
        free(weights);
    }

    // Cleanup and return best fitness
    int result = best_fitness;
    for (int i = 0; i < population_size; i++) {
        free(population[i]);
    }
    free(population);
    free(best_solution);

    return result;
}