#include "bruteforce.h"

int bruteforceKnapsack(int n, int maxWeight, Product* products) { if (n == 0) return -1;

long long int possibility = (1LL << n) - 1;
int maxCost = 0;

for (long long int i = possibility; i >= 0; i--) {
    int curWeight = 0, curCost = 0;

    for (int j = 0; j < n; j++) {
        if (i & (1LL << j)) {
            curWeight += products[j].weight;
            curCost += products[j].cost;
        }
    }

    if (curWeight <= maxWeight && curCost > maxCost) {
        maxCost = curCost;
        for (int j = 0; j < n; j++) {
            products[j].isPick = (i & (1LL << j)) != 0;
        }
    }
}

return maxCost;