#include"divideandconquer.h"

int max(int a, int b) { return (a > b) ? a : b; }

int divideAndConquerKnapSack(int n ,int W, Product *products)
{
    if (n == 0 || W == 0)
        return 0;

    if (products[n - 1].weight > W)
        return divideAndConquerKnapSack(n - 1, W, products);

    else
        return max(
            products[n - 1].cost
            + divideAndConquerKnapSack(n - 1, W - products[n - 1].weight, products),
            divideAndConquerKnapSack(n-1 ,W, products));
}