#ifndef DP_H
#define DP_H

#include <vector>
using namespace std;

struct Item {
    int weight;
    int value;
};

// function knapsackDP
int knapsackDP(int maxWeight, const vector<Item>& items);

#endif 
