#include "algorithmC.h"
#include <queue>
#include <vector>

struct Node {
    int level, profit, weight;
    double bound;
};

double bound(Node u, int n, int capacity, const std::vector<int>& values, const std::vector<int>& weights) {
    if (u.weight >= capacity) return 0;

    double result = u.profit;
    int j = u.level + 1;
    int totalWeight = u.weight;

    while (j < n && totalWeight + weights[j] <= capacity) {
        totalWeight += weights[j];
        result += values[j];
        j++;
    }

    if (j < n) result += (double)values[j] / weights[j] * (capacity - totalWeight);

    return result;
}

int knapsackBranchAndBound(int capacity, const std::vector<int>& values, const std::vector<int>& weights) {
    int n = values.size();
    std::priority_queue<Node> pq;

    Node u, v;
    u.level = -1, u.profit = 0, u.weight = 0;
    u.bound = bound(u, n, capacity, values, weights);
    pq.push(u);

    int maxProfit = 0;

    while (!pq.empty()) {
        u = pq.top();
        pq.pop();

        if (u.bound > maxProfit) {
            v.level = u.level + 1;

            v.weight = u.weight + weights[v.level];
            v.profit = u.profit + values[v.level];
            if (v.weight <= capacity && v.profit > maxProfit) {
                maxProfit = v.profit;
            }
            v.bound = bound(v, n, capacity, values, weights);
            if (v.bound > maxProfit) pq.push(v);

            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v, n, capacity, values, weights);
            if (v.bound > maxProfit) pq.push(v);
        }
    }

    return maxProfit;
}
