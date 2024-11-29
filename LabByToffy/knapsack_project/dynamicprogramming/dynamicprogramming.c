#include "dynamicprogramming.h"

int dynamic_programming(int n, int maxWeight, Product* products) {
    int dynamic[maxWeight + 1]; 

    for (int w = 0; w <= maxWeight; w++) {
        dynamic[w] = 0;
    }

    for (int i = 0; i < n; i++) {
        for (int w = maxWeight; w >= products[i].weight; w--) {
            dynamic[w] = (dynamic[w] > products[i].cost + dynamic[w - products[i].weight]) ? dynamic[w] : products[i].cost + dynamic[w - products[i].weight];
        }
    }

    return dynamic[maxWeight];
}
