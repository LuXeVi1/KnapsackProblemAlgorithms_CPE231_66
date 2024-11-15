// main.cpp
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "common.h"
#include "algorithmA/algorithmA.h"

using namespace std;
using namespace std::chrono;

// Structure to store algorithm results
struct Result {
    int value;
    double time;
};

// Function to generate random test cases
vector<Item> generateItems(int n, int maxValue = 1000, int maxWeight = 1000) {
    vector<Item> items;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> valueDist(1, maxValue);
    uniform_int_distribution<> weightDist(1, maxWeight);
    
    for(int i = 0; i < n; i++) {
        items.push_back({valueDist(gen), weightDist(gen)});
    }
    return items;
}

// Function to measure execution time
template<typename Func>
Result measureTime(Func f) {
    auto start = high_resolution_clock::now();
    int result = f();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    return Result{result, duration.count() / 1000000.0}; // Convert to seconds
}

int main() {
    vector<int> testSizes = {25, 50, 100, 500, 1000};
    
    for(int size : testSizes) {
        cout << "\nTesting with " << size << " items:" << endl;
        vector<Item> items = generateItems(size);
        int capacity = size * 50; // Adjust capacity based on problem size
        
        // Test Dynamic Programming approach
        Result dpResult = measureTime([&]() {
            return solveDynamicProgramming(items, capacity);
        });
        
        // Test Greedy approach
        Result greedyResult = measureTime([&]() {
            return solveGreedy(items, capacity);
        });
        
        // Test Branch and Bound approach
        Result bbResult = measureTime([&]() {
            return solveBranchAndBound(items, capacity);
        });
        
        cout << "Results for n=" << size << ":" << endl;
        cout << "Dynamic Programming: Value = " << dpResult.value 
             << ", Time = " << dpResult.time << "s" << endl;
        cout << "Greedy: Value = " << greedyResult.value 
             << ", Time = " << greedyResult.time << "s" << endl;
        cout << "Branch and Bound: Value = " << bbResult.value 
             << ", Time = " << bbResult.time << "s" << endl;
    }
    
    return 0;
}