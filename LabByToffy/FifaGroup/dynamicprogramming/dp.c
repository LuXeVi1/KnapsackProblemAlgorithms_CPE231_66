#include "dp.h"

int dynamic_programming(int n, int maxWeight, Product products[]) {
  int dp[n + 1][maxWeight + 1];

  for (int i = 0; i <= n; i++) {
    for (int w = 0; w <= maxWeight; w++) {
      dp[i][w] = 0;
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int w = 1; w <= maxWeight; w++) {
      if (products[i - 1].weight <= w) {
        dp[i][w] = (dp[i - 1][w] > products[i - 1].cost + dp[i - 1][w - products[i - 1].weight]) ? dp[i - 1][w] : products[i - 1].cost + dp[i - 1][w - products[i - 1].weight];
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }
  return dp[n][maxWeight];
}

// void solve_dynamic_programming(int n, int maxWeight, Product products[]) {
//   int max_value = dynamic_programming(n, maxWeight, products);
//   printf("Maximum value in Knapsack: %d\n", max_value);
// }
