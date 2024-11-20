#include <iostream>
#include <chrono> 
#include "DP/DP.h"   // Include Dynamic Programming header
#include "SA/SA.h"   // Include Simulated Annealing header

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

    // Solve using Dynamic Programming
    auto startDP = high_resolution_clock::now();
    int maxValueDP = knapsackDP(maxWeight, items);
    auto stopDP = high_resolution_clock::now();
    auto durationDP = duration_cast<milliseconds>(stopDP - startDP);

    cout << "Dynamic Programming: Value = " << maxValueDP << endl;
    cout << "Execution Time (DP): " << durationDP.count() << " ms" << endl;

    // Solve using Simulated Annealing
    auto startSA = high_resolution_clock::now();
    int maxValueSA = knapsackSA(maxWeight, items);
    auto stopSA = high_resolution_clock::now();
    auto durationSA = duration_cast<milliseconds>(stopSA - startSA);

    cout << "Simulated Annealing: Value = " << maxValueSA << endl;
    cout << "Execution Time (SA): " << durationSA.count() << " ms" << endl;

    return 0;
}
