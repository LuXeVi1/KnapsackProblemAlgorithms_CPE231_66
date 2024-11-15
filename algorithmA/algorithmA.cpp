#include "algorithmA.h"
#include <algorithm>

struct Item {
    int value, weight;
    double ratio;
};

bool compare(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

double knapsackGreedy(int capacity, const std::vector<int>& values, const std::vector<int>& weights) {
    int n = values.size();
    std::vector<Item> items(n);

    for (int i = 0; i < n; ++i) {
        items[i] = {values[i], weights[i], (double)values[i] / weights[i]};
    }

    std::sort(items.begin(), items.end(), compare);

    double maxValue = 0.0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            maxValue += item.value;
        } else {
            maxValue += item.ratio * capacity;
            break;
        }
    }

    return maxValue;
}
