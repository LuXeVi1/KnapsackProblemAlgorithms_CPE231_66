#include "greedytechnique.h"

void swap(Product* a, Product* b) {
    Product temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Product* products[], int low, int high) {
    int pivot = products[high]->cost;
    int i = low - 1;
    
    for (int j = low; j <= high - 1; j++) {
        if (products[j]->cost > pivot) {
            i++;
            swap(products[i], products[j]);
        }
    }
    swap(products[i + 1], products[high]);
    return i + 1;
}

void quickSort(Product* products[], int low, int high) {
    if (low < high) {
        int pi = partition(products, low, high);
        quickSort(products, low, pi - 1);
        quickSort(products, pi + 1, high);
    }
}

int greedy(int n, int maxWeight, Product* products[]) {
    quickSort(products, 0, n - 1);
    
    int curWeight = 0, maxCost = 0;
    for (int i = 0; i < n; i++) {
        if (curWeight + products[i]->weight <= maxWeight) {
            curWeight += products[i]->weight;
            maxCost += products[i]->cost;
        } else {
            break;
        }
    }
    
    return maxCost;
}