#include "DP.h"

// knapsackDP
int knapsackDP(int maxWeight, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    // Dynamic Programming
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= maxWeight; ++w) {
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = max(dp[i - 1][w],
                               dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }
    return dp[n][maxWeight];
}
