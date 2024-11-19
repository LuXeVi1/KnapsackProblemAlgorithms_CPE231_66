#include <iostream>
#include <chrono> 
#include "DP/DP.h"

using namespace std;
using namespace chrono; 

int main() {
    int n;
    cin >> n; // Input the number of items
    vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        cin >> items[i].weight >> items[i].value;
    }

    int maxWeight;
    cin >> maxWeight; // Input the maximum weight capacity of the knapsack

    // Start measuring time
    auto start = high_resolution_clock::now();

    // Call the knapsackDP function
    int maxValue = knapsackDP(maxWeight, items);

    // Stop measuring time
    auto stop = high_resolution_clock::now();

    // Calculate the duration
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Dynamic Programming: Value = " << maxValue << endl;
    cout << "Execution Time: " << duration.count() << " ms" << endl;

    return 0;
}