#pragma once

// A Naive recursive implementation of 0-1 Knapsack problem

#include <iostream>
using namespace std;

// Return the maximum value that
// can be put in a knapsack of capacity W
// n from n to 0, f(0) = 0
int knapsack(int W, int wt[], int val[], int n);

// idx from 0 to n, f(n) = 0
int knapsack2(int W, int wt[], int val[], int idx, int n); 

// Build table K[][] in bottom up manner
int knapsack3(const int W, int wt[], int val[], const int n);

// Test func
void dynamicProgramingTest();
