#include <iostream>
#include "DP/DP.h" 

using namespace std;

int main() {
    int n;
    cin >> n; // Input the number of items
    vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    int maxWeight;
    cin >> maxWeight; // Input the maximum weight capacity of the knapsack

    // knapsackDP
    int maxValue = knapsackDP(maxWeight, items); 
    cout << "Dynamic Programming: Value = " << maxValue << endl;

    return 0;
}
