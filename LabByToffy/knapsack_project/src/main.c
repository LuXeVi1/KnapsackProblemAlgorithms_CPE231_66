#include <stdio.h>
#include <stdlib.h>
#include "../src/structure.h"         // Shared structures and utilities
#include "../include/bruteforce.h"        // Brute force algorithms
#include "../include/divideAndConquer.h"  // Divide and conquer techniques
#include "../include/dynamicProgramming.h" // Dynamic programming techniques
#include "../include/genetic.h"           // Genetic algorithms
#include "../include/greedyAlgorithm.h"   // Greedy algorithms
#include "../include/iterativeImprovement.h" // Iterative improvement techniques
#include "../include/transformAndConquer.h"  // Transform and conquer techniques

// Function prototypes
void displayMenu();
void executeAlgorithm(int choice);

int main() {
    int choice;

    do {
        displayMenu();
        printf("\nEnter your choice (0 to exit): ");
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Invalid input. Please enter a number.\n");
            exit(EXIT_FAILURE);
        }

        if (choice == 0) {
            printf("\nExiting program. Goodbye!\n");
            break;
        }

        executeAlgorithm(choice);

    } while (choice != 0);

    return 0;
}

void displayMenu() {
    printf("\n========== Algorithm Selection Menu ==========\n");
    printf("1. Brute Force Algorithms\n");
    printf("2. Divide and Conquer\n");
    printf("3. Dynamic Programming\n");
    printf("4. Greedy Algorithms\n");
    printf("5. Genetic Algorithms\n");
    printf("6. Iterative Improvement\n");
    printf("7. Transform and Conquer\n");
    printf("0. Exit\n");
    printf("==============================================\n");
}

void executeAlgorithm(int choice) {
    switch (choice) {
        case 1:
            printf("\nRunning Brute Force Algorithms...\n");
            runBruteForce();  // Function in bruteforce.h
            break;
        case 2:
            printf("\nRunning Divide and Conquer...\n");
            runDivideAndConquer();  // Function in divideAndConquer.h
            break;
        case 3:
            printf("\nRunning Dynamic Programming...\n");
            runDynamicProgramming();  // Function in dynamicProgramming.h
            break;
        case 4:
            printf("\nRunning Greedy Algorithms...\n");
            runGreedyAlgorithms();  // Function in greedyAlgorithm.h
            break;
        case 5:
            printf("\nRunning Genetic Algorithms...\n");
            runGeneticAlgorithm();  // Function in genetic.h
            break;
        case 6:
            printf("\nRunning Iterative Improvement...\n");
            runIterativeImprovement();  // Function in iterativeImprovement.h
            break;
        case 7:
            printf("\nRunning Transform and Conquer...\n");
            runTransformAndConquer();  // Function in transformAndConquer.h
            break;
        default:
            printf("\nInvalid choice. Please select a valid option.\n");
            break;
    }
}