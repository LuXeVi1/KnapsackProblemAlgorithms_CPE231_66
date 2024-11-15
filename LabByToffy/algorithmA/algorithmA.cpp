// algorithmA/algorithmA.cpp
#include "algorithmA.h"
#include <algorithm>
#include <queue>

// Dynamic Programming Implementation
int solveDynamicProgramming(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    
    for(int i = 1; i <= n; i++) {
        for(int w = 0; w <= capacity; w++) {
            if(items[i-1].weight <= w) {
                dp[i][w] = std::max(dp[i-1][w], 
                                  items[i-1].value + dp[i-1][w - items[i-1].weight]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

// Greedy Implementation (using value/weight ratio)
int solveGreedy(const std::vector<Item>& items, int capacity) {
    std::vector<std::pair<double, int>> ratio;
    for(int i = 0; i < items.size(); i++) {
        ratio.push_back({(double)items[i].value / items[i].weight, i});
    }
    
    std::sort(ratio.begin(), ratio.end(), std::greater<>());
    
    int totalValue = 0;
    int remainingCapacity = capacity;
    
    for(const auto& r : ratio) {
        if(items[r.second].weight <= remainingCapacity) {
            totalValue += items[r.second].value;
            remainingCapacity -= items[r.second].weight;
        }
    }
    
    return totalValue;
}

// Branch and Bound Implementation
struct Node {
    int level;
    int value;
    int weight;
    double bound;
};

double calculateBound(const std::vector<Item>& items, Node u, int n, int capacity) {
    if(u.weight >= capacity) return 0;
    
    double bound = u.value;
    int j = u.level + 1;
    int totalWeight = u.weight;
    
    while(j < n && totalWeight + items[j].weight <= capacity) {
        totalWeight += items[j].weight;
        bound += items[j].value;
        j++;
    }
    
    if(j < n) {
        bound += (capacity - totalWeight) * 
                 ((double)items[j].value / items[j].weight);
    }
    
    return bound;
}

int solveBranchAndBound(const std::vector<Item>& items, int capacity) {
    int n = items.size();
    std::vector<std::pair<double, Item>> sortedItems;
    for(const auto& item : items) {
        sortedItems.push_back({(double)item.value / item.weight, item});
    }
    std::sort(sortedItems.begin(), sortedItems.end(), std::greater<>());
    
    std::vector<Item> sortedItemsOnly;
    for(const auto& p : sortedItems) {
        sortedItemsOnly.push_back(p.second);
    }
    
    Node u {-1, 0, 0, 0};
    std::queue<Node> Q;
    Q.push(u);
    
    int maxValue = 0;
    
    while(!Q.empty()) {
        u = Q.front();
        Q.pop();
        
        if(u.level == n-1) continue;
        
        // Include next item
        Node v {u.level + 1, 
               u.value + sortedItemsOnly[u.level + 1].value,
               u.weight + sortedItemsOnly[u.level + 1].weight,
               0};
               
        if(v.weight <= capacity && v.value > maxValue) {
            maxValue = v.value;
        }
        
        v.bound = calculateBound(sortedItemsOnly, v, n, capacity);
        if(v.bound > maxValue && v.weight <= capacity) {
            Q.push(v);
        }
        
        // Exclude next item
        v = {u.level + 1, u.value, u.weight, 0};
        v.bound = calculateBound(sortedItemsOnly, v, n, capacity);
        if(v.bound > maxValue) {
            Q.push(v);
        }
    }
    
    return maxValue;
}