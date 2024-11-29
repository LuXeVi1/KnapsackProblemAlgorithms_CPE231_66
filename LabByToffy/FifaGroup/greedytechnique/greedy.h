#ifndef GREEDY_H
#define GREEDY_H

#include <stdio.h>
#include <stdlib.h>
#include "../structure.h"

void swap(Product* a, Product* b);
int partition(Product products[], int low, int high);
void quickSort(Product products[], int low, int high);
int greedy( int n,int maxWeight , Product* products);

#endif //GREEDY_H
