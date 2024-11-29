#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algorithms.h"

// Structure for the individual (chromosome) representation
typedef struct {
    int *genes;       // Array of genes (0 or 1)
    int fitness;      // Fitness of the solution (value of the knapsack)
} Individual;

// Function to create a new individual with random genes
Individual *createIndividual(int n) {
    Individual *ind = (Individual *)malloc(sizeof(Individual));
    ind->genes = (int *)malloc(n * sizeof(int));

    // Randomly generate genes (0 or 1)
    for (int i = 0; i < n; i++) {
        ind->genes[i] = rand() % 2;
    }
    return ind;
}

// Function to calculate the fitness of an individual (value of the knapsack)
int calculateFitness(Individual *ind, int n, int weights[], int values[], int capacity) {
    int totalWeight = 0;
    int totalValue = 0;

    // Calculate the total weight and value based on the genes
    for (int i = 0; i < n; i++) {
        if (ind->genes[i] == 1) {  // Item is included
            totalWeight += weights[i];
            totalValue += values[i];
        }
    }

    // If the weight exceeds the capacity, return a negative fitness value
    if (totalWeight > capacity) {
        return -1;
    }

    return totalValue;  // Fitness is the total value of the selected items
}

// Function to perform tournament selection
Individual *tournamentSelection(Individual **population, int popSize, int n, int weights[], int values[], int capacity) {
    int tournamentSize = 5;
    Individual *best = NULL;

    for (int i = 0; i < tournamentSize; i++) {
        int randIndex = rand() % popSize;
        Individual *candidate = population[randIndex];
        if (best == NULL || candidate->fitness > best->fitness) {
            best = candidate;
        }
    }

    return best;
}

// Function to perform crossover between two individuals (single-point crossover)
Individual *crossover(Individual *parent1, Individual *parent2, int n) {
    Individual *child = createIndividual(n);

    int crossoverPoint = rand() % n;
    for (int i = 0; i < crossoverPoint; i++) {
        child->genes[i] = parent1->genes[i];
    }
    for (int i = crossoverPoint; i < n; i++) {
        child->genes[i] = parent2->genes[i];
    }

    return child;
}

// Function to perform mutation (flip a random gene with a small probability)
void mutate(Individual *ind, int n) {
    int mutationRate = 1;  // 1% mutation rate
    for (int i = 0; i < n; i++) {
        if (rand() % 100 < mutationRate) {
            ind->genes[i] = 1 - ind->genes[i];  // Flip the gene
        }
    }
}

// Function to perform the genetic algorithm
Individual *geneticAlgorithm(int capacity, int n, int weights[], int values[], int popSize, int generations) {
    // Initialize the population
    Individual **population = (Individual **)malloc(popSize * sizeof(Individual *));
    for (int i = 0; i < popSize; i++) {
        population[i] = createIndividual(n);
    }

    // Evaluate fitness for each individual in the population
    for (int i = 0; i < popSize; i++) {
        population[i]->fitness = calculateFitness(population[i], n, weights, values, capacity);
    }

    Individual *bestIndividual = NULL;

    // Run the genetic algorithm for the specified number of generations
    for (int gen = 0; gen < generations; gen++) {
        // Create a new population
        Individual **newPopulation = (Individual **)malloc(popSize * sizeof(Individual *));
        for (int i = 0; i < popSize; i++) {
            // Select parents using tournament selection
            Individual *parent1 = tournamentSelection(population, popSize, n, weights, values, capacity);
            Individual *parent2 = tournamentSelection(population, popSize, n, weights, values, capacity);

            // Perform crossover to create a child
            Individual *child = crossover(parent1, parent2, n);

            // Perform mutation on the child
            mutate(child, n);

            // Evaluate the child's fitness
            child->fitness = calculateFitness(child, n, weights, values, capacity);

            // Add the child to the new population
            newPopulation[i] = child;
        }

        // Replace the old population with the new population
        for (int i = 0; i < popSize; i++) {
            free(population[i]->genes);
            free(population[i]);
        }
        free(population);
        population = newPopulation;

        // Track the best individual found
        for (int i = 0; i < popSize; i++) {
            if (bestIndividual == NULL || population[i]->fitness > bestIndividual->fitness) {
                bestIndividual = population[i];
            }
        }
    }

    // Clean up the population and return the best individual
    for (int i = 0; i < popSize; i++) {
        free(population[i]->genes);
        free(population[i]);
    }
    free(population);

    return bestIndividual;
}

// Wrapper function for the Genetic Algorithm
int knapsackGeneticAlgorithm(int capacity, int n, int weights[], int values[]) {
    srand(time(NULL));  // Seed the random number generator

    int popSize = 100;         // Population size
    int generations = 1000;    // Number of generations

    Individual *best = geneticAlgorithm(capacity, n, weights, values, popSize, generations);

    // Return the fitness of the best solution found
    int result = best->fitness;

    // Free the best individual
    free(best->genes);
    free(best);

    return result;
}
