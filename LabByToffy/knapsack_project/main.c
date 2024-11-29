#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"
#include "utils.h"

// Function to display the results of the chosen algorithm
void displayResults(int result) {
    printf("Optimal Value: %d\n", result);
}

// Function to handle user input and choose an algorithm
void chooseAlgorithm(int capacity, int n, int weights[], int values[]) {
    int choice;
    printf("Select an algorithm to solve the Knapsack problem:\n");
    printf("1. Brute Force\n");
    printf("2. Dynamic Programming\n");
    printf("3. Greedy\n");
    printf("4. Fractional Knapsack\n");
    printf("5. Genetic Algorithm\n");
    printf("6. Iterative Improvement\n");
    printf("7. Divide and Conquer\n");
    printf("8. Decrease and Conquer\n");
    printf("9. Space-Time Tradeoff\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int result = 0;

    switch (choice) {
        case 1:
            result = knapsackBruteForce(capacity, n, weights, values);
            break;
        case 2:
            result = knapsackDynamicProgramming(capacity, n, weights, values);
            break;
        case 3:
            result = knapsackGreedy(capacity, n, weights, values);
            break;
        case 4:
            result = knapsackFractional(capacity, n, weights, values);
            break;
        case 5:
            result = knapsackGeneticAlgorithm(capacity, n, weights, values);
            break;
        case 6:
            result = knapsackIterativeImprovement(capacity, n, weights, values);
            break;
        case 7:
            result = knapsackDivideAndConquer(capacity, n, weights, values);
            break;
        case 8:
            result = knapsackDecreaseAndConquer(capacity, n, weights, values);
            break;
        case 9:
            result = knapsackSpaceTimeTradeoff(capacity, n, weights, values);
            break;
        default:
            printf("Invalid choice\n");
            return;
    }

    displayResults(result);
}

int main() {
    // Test case setup
    int n = 5;  // Number of items
    int weights[] = {2, 3, 4, 5, 6};
    int values[] = {3, 4, 5, 6, 7};
    int capacity = 10;  // Knapsack capacity

    // Display welcome message
    printf("Knapsack Problem Solver\n");

    // Call the function to choose the algorithm
    chooseAlgorithm(capacity, n, weights, values);

    return 0;
}
