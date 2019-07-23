#pragma once

// A Naive recursive implementation of 0-1 Knapsack problem

#include <iostream>
using namespace std;

// Test func
void dynamicProgramingTest();

/*****************************Knapsack Problem Begin*****************************/
// Return the maximum value that
// can be put in a knapsack of capacity W
// n from n to 0, f(0) = 0
int knapsack(int W, int wt[], int val[], int n);

// idx from 0 to n, f(n) = 0
int knapsack2(int W, int wt[], int val[], int idx, int n); 

// Build table K[][] in bottom up manner
int knapsack3(const int W, int wt[], int val[], const int n);

/*****************************Knapsack Problem End*******************************/

/*****************************Shortest Path Begin*****************************/
/*
	0	1	2	3
_________________
0|  1	3	5	9
1|	2	1	3	4
2|	5	2	6	7
3|	6	8	4	3

From (0,0) to (3,3)
K(i,j) = min(K(i-1, j), K(i, j-1))

Recursion Tree:K(i,j)  
						K(3,3)
					/			\
	go up		/					 \ go left
			K(3,2)					   K(2,3)
		  /		   \				 / 	      \
	   K(3,1)      K(2,2)		  K(2,2)	   K(1,3)
	 /   \		   /    \		  /    \		 /    \
   K(3,0) K(2,1) K(2,1) K(1,2)  K(2,1) K(1,2)  K(1,2)  K(0,3)

*/

// use recursion O(2^n)
int shortestPath(int w[][4], int i, int j);

// use recursion with duplicate array, < O(2^n)
int shortestPath2(int w[][4], int i, int j);

// use table O(n*m)
int shortestPath3(int w[][4], int n, int m);

/*****************************Shortest Path End*******************************/

