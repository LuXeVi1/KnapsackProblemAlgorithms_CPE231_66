// algorithmA/algorithmA.h
#ifndef ALGORITHM_A_H
#define ALGORITHM_A_H

#include "../common.h"
#include <vector>

// Dynamic Programming approach
int solveDynamicProgramming(const std::vector<Item>& items, int capacity);

// Greedy approach
int solveGreedy(const std::vector<Item>& items, int capacity);

// Branch and Bound approach
int solveBranchAndBound(const std::vector<Item>& items, int capacity);

#endif