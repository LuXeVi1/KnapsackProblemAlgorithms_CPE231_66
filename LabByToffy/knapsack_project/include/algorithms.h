#ifndef ALGORITHMS_H
#define ALGORITHMS_H

// Function prototypes for the various algorithms
int knapsackBruteForce(int capacity, int n, int weights[], int values[]);
int knapsackDynamicProgramming(int capacity, int n, int weights[], int values[]);
int knapsackGreedy(int capacity, int n, int weights[], int values[]);
int knapsackFractional(int capacity, int n, int weights[], int values[]);
int knapsackGeneticAlgorithm(int capacity, int n, int weights[], int values[]);
int knapsackIterativeImprovement(int capacity, int n, int weights[], int values[]);
int knapsackDivideAndConquer(int capacity, int n, int weights[], int values[]);
int knapsackDecreaseAndConquer(int capacity, int n, int weights[], int values[]);
int knapsackSpaceTimeTradeoff(int capacity, int n, int weights[], int values[]);

#endif // ALGORITHMS_H
