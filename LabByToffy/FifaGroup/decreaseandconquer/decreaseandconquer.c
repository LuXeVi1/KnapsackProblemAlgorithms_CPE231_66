#include "decreaseandconquer.h"

int decreaseAndConquerKnapsack(int n, int maxWeight, Product* products) {
    if (n == 0 || maxWeight == 0) {
        return 0;
    }

    Product currentProduct = products[n - 1];

    int exclude = decreaseAndConquerKnapsack(n - 1, maxWeight, products);

    int include = 0;
    if (currentProduct.weight <= maxWeight) {
        include = currentProduct.cost + decreaseAndConquerKnapsack(n - 1, maxWeight - currentProduct.weight, products);
    }

    return max(include, exclude);
}
