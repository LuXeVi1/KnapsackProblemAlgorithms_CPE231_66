#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdbool.h>

typedef struct product {
    int weight;
    int cost;
    int productID;
    bool isPick;
    struct Product* next;
    int value;
} Product;

#endif // STRUCTURE_H
