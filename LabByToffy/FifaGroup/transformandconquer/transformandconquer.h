#ifndef TRANSFORMANDCONQUER_H
#define TRANSFORMANDCONQUER_H

#include <stdio.h>
#include <stdlib.h>
#include "../structure.h"

void swapTaC(Product *a, Product *b);
void swapRatioTaC(double *a, double *b);
int partitionTaC(Product products[], double ratio[], int low, int high);
void quickSortTaC(Product products[], double ratio[], int low, int high);
int fractionalKnapsack(int n, int capacity, Product products[]);

#endif //TRANSFORMANDCONQUER_H
