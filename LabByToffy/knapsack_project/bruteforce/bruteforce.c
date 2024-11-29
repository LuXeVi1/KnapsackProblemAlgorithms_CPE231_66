#include "bruteforce.h"

int bruteforceKnapsack(int n, int maxWeight, Product* products) {
    if (n <= 0) return 0;
    
    int maxCost = 0;
    unsigned long long possibility = (1ULL << n) - 1;

    for (unsigned long long subset = 0; subset <= possibility; ++subset) {
        int currentWeight = 0;
        int currentCost = 0;

        for (int item = 0; item < n; ++item) {
            if (subset & (1ULL << item)) {
                currentWeight += products[item].weight;
                currentCost += products[item].cost;
            }
        }

        if (currentWeight <= maxWeight && currentCost > maxCost) {
            maxCost = currentCost;
            for (int item = 0; item < n; ++item) {
                products[item].isPick = (subset & (1ULL << item)) != 0;
            }
        }
    }

    return maxCost;
}