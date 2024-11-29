#include <iostream>
#include <vector>
#include <chrono>
#include "algorithmA/algorithmA.h"
#include "algorithmB/algorithmB.h"
#include "algorithmC/algorithmC.h"

int main() {
    int capacity, n;
    std::vector<int> values, weights;

    std::cout << "Enter the capacity of the knapsack: ";
    std::cin >> capacity;
    std::cout << "Enter the number of items: ";
    std::cin >> n;

    values.resize(n);
    weights.resize(n);

    std::cout << "Enter the values and weights of the items:\n";
    for (int i = 0; i < n; ++i) {
        std::cin >> values[i] >> weights[i];
    }

    // Greedy
    auto startA = std::chrono::high_resolution_clock::now();
    double resultA = knapsackGreedy(capacity, values, weights);
    auto endA = std::chrono::high_resolution_clock::now();
    std::cout << "Algorithm A (Greedy): Max Value = " << resultA
              << " (Execution Time: "
              << std::chrono::duration<double>(endA - startA).count() << "s)" << std::endl;

    // Dynamic Programming
    auto startB = std::chrono::high_resolution_clock::now();
    int resultB = knapsackDP(capacity, values, weights);
    auto endB = std::chrono::high_resolution_clock::now();
    std::cout << "Algorithm B (DP): Max Value = " << resultB
              << " (Execution Time: "
              << std::chrono::duration<double>(endB - startB).count() << "s)" << std::endl;

    // Branch and Bound
    auto startC = std::chrono::high_resolution_clock::now();
    int resultC = knapsackBranchAndBound(capacity, values, weights);
    auto endC = std::chrono::high_resolution_clock::now();
    std::cout << "Algorithm C (Branch and Bound): Max Value = " << resultC
              << " (Execution Time: "
              << std::chrono::duration<double>(endC - startC).count() << "s)" << std::endl;

    return 0;
}