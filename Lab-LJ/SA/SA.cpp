#include "SA.h"
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;

// Helper function to calculate total weight and value of a solution
pair<int, int> evaluateSolution(const vector<int>& solution, const vector<Item>& items) {
    int totalWeight = 0, totalValue = 0;
    for (size_t i = 0; i < solution.size(); ++i) {
        if (solution[i]) {
            totalWeight += items[i].weight;
            totalValue += items[i].value;
        }
    }
    return {totalWeight, totalValue};
}

// Simulated Annealing function for Knapsack Problem
int knapsackSA(int maxWeight, const vector<Item>& items) {
    size_t n = items.size();
    vector<int> currentSolution(n, 0); // Initial solution (all items excluded)
    vector<int> bestSolution = currentSolution;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n - 1); // Random index
    uniform_real_distribution<> probDist(0, 1); // Random probability

    // Parameters for simulated annealing
    double temperature = 1000.0;
    double coolingRate = 0.99;
    int maxIterations = 1000;

    // Evaluate initial solution
    pair<int, int> currentEval = evaluateSolution(currentSolution, items);
    int currentWeight = currentEval.first;
    int currentValue = currentEval.second;

    pair<int, int> bestEval = evaluateSolution(bestSolution, items);
    int bestWeight = bestEval.first;
    int bestValue = bestEval.second;

    // Simulated Annealing Loop
    for (int iteration = 0; iteration < maxIterations && temperature > 1e-3; ++iteration) {
        // Generate a neighbor solution
        vector<int> neighborSolution = currentSolution;
        int index = dis(gen); // Pick a random item
        neighborSolution[index] = 1 - neighborSolution[index]; // Flip inclusion/exclusion

        // Evaluate neighbor solution
        pair<int, int> neighborEval = evaluateSolution(neighborSolution, items);
        int neighborWeight = neighborEval.first;
        int neighborValue = neighborEval.second;

        // Check feasibility of the neighbor solution
        if (neighborWeight <= maxWeight) {
            // Calculate change in value
            int deltaValue = neighborValue - currentValue;

            // Accept or reject the neighbor solution
            if (deltaValue > 0 || probDist(gen) < exp(deltaValue / temperature)) {
                currentSolution = neighborSolution;
                currentWeight = neighborWeight;
                currentValue = neighborValue;

                // Update the best solution if improved
                if (currentValue > bestValue) {
                    bestSolution = currentSolution;
                    bestWeight = currentWeight;
                    bestValue = currentValue;
                }
            }
        }

        // Cool down the temperature
        temperature *= coolingRate;
    }

    return bestValue; // Return the value of the best solution
}
