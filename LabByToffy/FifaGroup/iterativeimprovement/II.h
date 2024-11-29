#ifndef II_H
#define II_H

#include <stdio.h>
#include <stdlib.h>
#include "../structure.h"
#include "../transformandconquer/transformandconquer.h"

int knapsackValue(Product products[], int n, int capacity);
int iterativeImprovementKnapsack(int n, int capacity,Product items[]);

#endif //II_H
