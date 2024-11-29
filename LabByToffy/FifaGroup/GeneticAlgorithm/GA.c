#include "GA.h"

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
int genetic_algorithm(int num_items, Product *weight_value, int capacity, int population_size, int num_generations, double mutation_rate, int elitism_count);


// Read test case file
void readTestCase(const char *filename, int *numItems, Product **weight_value, int *capacity) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", numItems);
    *weight_value = (Product *)malloc((*numItems) * sizeof(Product));

    for (int i = 0; i < *numItems; i++) {
        fscanf(file, "%d %d", &(*weight_value)[i].weight, &(*weight_value)[i].value);
    }

    fscanf(file, "%d", capacity);
    fclose(file);
}

// Initialize population
int **initialize_population(int population_size, int numItems) {
    int **population = (int **)malloc(population_size * sizeof(int *));
    for (int i = 0; i < population_size; i++) {
        population[i] = (int *)malloc(numItems * sizeof(int));
        for (int j = 0; j < numItems; j++) {
            population[i][j] = rand() % 2;
        }
    }
    return population;
}

// Fitness function
int fitness(int *chromosome, Product *weight_value, int numItems, int capacity, int *total_weight) {
    int total_value = 0;
    *total_weight = 0;

    for (int i = 0; i < numItems; i++) {
        if (chromosome[i]) {
            *total_weight += weight_value[i].weight;
            total_value += weight_value[i].value;
        }
    }
    if (*total_weight <= capacity){
        return total_value;
    }
    return 0;
}

// Cumulative fitness table
void cumulation(int *fitness_values, int population_size, int *total_fitness, int *cumulative_fitness) {
    *total_fitness = 0;
    for (int i = 0; i < population_size; i++) {
        *total_fitness += fitness_values[i];
        cumulative_fitness[i] = *total_fitness;
    }
}

// Roulette wheel selection
int roulette_wheel_selection(int total_fitness, int *cumulative_fitness, int population_size) {
    int random_value = rand() % total_fitness;
    for (int i = 0; i < population_size; i++) {
        if (random_value <= cumulative_fitness[i]) {
            return i;
        }
    }
    return population_size - 1; // fallback
}

// Determine breakpoints
int determine_breakpoints(int num_items) {
    if (num_items <= 50) return 2;
    if (num_items <= 100) return 3;
    if (num_items <= 500) return 4;
    return 9;
}

// Comparison function for qsort
int compare_ints(const void *a, const void *b) {
    int int_a = *((int *)a);
    int int_b = *((int *)b);
    
    if (int_a < int_b) return -1; // a is smaller than b
    if (int_a > int_b) return 1;  // a is larger than b
    return 0;  // a is equal to b
}

// Crossover
void crossover(int *parent1, int *parent2, int num_items, int num_breakpoints, int *child1, int *child2) {
    int *breakpoints = (int *)malloc((num_breakpoints + 2) * sizeof(int));
    breakpoints[0] = 0;
    breakpoints[num_breakpoints + 1] = num_items;

    for (int i = 1; i <= num_breakpoints; i++) {
        breakpoints[i] = rand() % (num_items - 1) + 1;
    }
    qsort(breakpoints, num_breakpoints + 2, sizeof(int), compare_ints);

    int toggle = 0;
    for (int i = 0; i < num_breakpoints + 1; i++) {
        for (int j = breakpoints[i]; j < breakpoints[i + 1]; j++) {
            if (toggle == 0) {
                child1[j] = parent1[j];
                child2[j] = parent2[j];
            } else {
                child1[j] = parent2[j];
                child2[j] = parent1[j];
            }
        }
        toggle = 1 - toggle;
    }

    free(breakpoints);
}


// Mutation
void mutate(int *chromosome, int num_items, double mutation_rate) {
    for (int i = 0; i < num_items; i++) {
        if ((rand() / (double)RAND_MAX) < mutation_rate) {
            chromosome[i] = 1 - chromosome[i];
        }
    }
}

// Elitism selection
void elitism_selection(int **population, int *fitness_values, int population_size, int elitism_count, int **elites, int numItems) {
    int *sorted_indices = (int *)malloc(population_size * sizeof(int));
    for (int i = 0; i < population_size; i++) {
        sorted_indices[i] = i;
    }

    for (int i = 0; i < population_size - 1; i++) {
        for (int j = 0; j < population_size - i - 1; j++) {
            if (fitness_values[sorted_indices[j]] < fitness_values[sorted_indices[j + 1]]) {
                int temp = sorted_indices[j];
                sorted_indices[j] = sorted_indices[j + 1];
                sorted_indices[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < elitism_count; i++) {
        for (int j = 0; j < numItems; j++) {
            elites[i][j] = population[sorted_indices[i]][j];
        }
    }

    free(sorted_indices);
}

// Quick Select Algorithm
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int *fitness_values, int *indices, int low, int high) {
    int pivot = fitness_values[indices[high]];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (fitness_values[indices[j]] >= pivot) {
            i++;
            swap(&indices[i], &indices[j]);
        }
    }
    swap(&indices[i + 1], &indices[high]);
    return i + 1;
}

int quickselect(int *fitness_values, int *indices, int low, int high, int k) {
    if (low <= high) {
        int pivot_index = partition(fitness_values, indices, low, high);

        if (pivot_index == k) {
            return indices[pivot_index];
        } else if (pivot_index > k) {
            return quickselect(fitness_values, indices, low, pivot_index - 1, k);
        } else {
            return quickselect(fitness_values, indices, pivot_index + 1, high, k);
        }
    }
    return -1;
}

int genetic_algorithm(int num_items, int capacity, Product *weight_value, int population_size, int num_generations, double mutation_rate, int elitism_count) {
    int num_breakpoints = determine_breakpoints(num_items);
    int **population = initialize_population(population_size, num_items);
    int best_fitness = 0, count = 0;
    int *best_solution = (int *)malloc(num_items * sizeof(int));

    for (int generation = 0; generation < num_generations; generation++) {
        int *fitness_values = (int *)malloc(population_size * sizeof(int));
        int *weights = (int *)malloc(population_size * sizeof(int));
        int total_fitness = 0;
        int *cumulative_fitness = (int *)malloc(population_size * sizeof(int));

        for (int i = 0; i < population_size; i++) {
            fitness_values[i] = fitness(population[i], weight_value, num_items, capacity, &weights[i]);
        }

        int *indices = (int *)malloc(population_size * sizeof(int));
        for (int i = 0; i < population_size; i++) {
            indices[i] = i;
        }

        int best_index = quickselect(fitness_values, indices, 0, population_size - 1, 0);
        if (fitness_values[best_index] > best_fitness) {
            best_fitness = fitness_values[best_index];
            for (int j = 0; j < num_items; j++) {
                best_solution[j] = population[best_index][j];
            }
        }

        free(indices);

        int **elites = (int **)malloc(elitism_count * sizeof(int *));
        for (int i = 0; i < elitism_count; i++) {
            elites[i] = (int *)malloc(num_items * sizeof(int));
        }

        elitism_selection(population, fitness_values, population_size, elitism_count, elites, num_items);

        cumulation(fitness_values, population_size, &total_fitness, cumulative_fitness);

        int **new_population = initialize_population(population_size, num_items);
        int index = 0;

        for (int i = 0; i < elitism_count; i++) {
            for (int j = 0; j < num_items; j++) {
                new_population[index][j] = elites[i][j];
            }
            index++;
        }

        while (index < population_size) {
            int parent1_index = roulette_wheel_selection(total_fitness, cumulative_fitness, population_size);
            int parent2_index = roulette_wheel_selection(total_fitness, cumulative_fitness, population_size);

            int *child1 = (int *)malloc(num_items * sizeof(int));
            int *child2 = (int *)malloc(num_items * sizeof(int));
            crossover(population[parent1_index], population[parent2_index], num_items, num_breakpoints, child1, child2);

            mutate(child1, num_items, mutation_rate);
            mutate(child2, num_items, mutation_rate);

            for (int j = 0; j < num_items; j++) {
                new_population[index][j] = child1[j];
            }
            index++;
            if (index < population_size) {
                for (int j = 0; j < num_items; j++) {
                    new_population[index][j] = child2[j];
                }
                index++;
            }

            free(child1);
            free(child2);
        }

        for (int i = 0; i < population_size; i++) {
            free(population[i]);
        }
        free(population);
        population = new_population;

        free(fitness_values);
        free(weights);
        free(cumulative_fitness);
        for (int i = 0; i < elitism_count; i++) {
            free(elites[i]);
        }
        free(elites);
    }
    
    for (int i = 0; i < population_size; i++) {
        free(population[i]);
    }

    free(population);

    free(best_solution);

    return best_fitness;
}
