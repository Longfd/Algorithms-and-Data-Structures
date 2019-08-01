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

// use table O(n*m) Dijkstra Algorithm
int shortestPath3(int w[][4], int n, int m);

/*****************************Shortest Path End*******************************/

/*****************************Edit Distance Begin*******************************/
/*
a[] = "abticlkafj" 
b[] = "atclaj"
Levenshtein Distance = 4
Longest Common Substring Length = 6

f(a[], b[], i, j)
if(a[i] != a[j])
	return 1 + min(f(a, b, i+1, j),   -> skip char a[i] 			 delete a[i]		distance + 1
				   f(a, b, i, j+1),	  -> skip char b[j]				 delete b[j]		distance + 1
				   f(a, b, i+1, j+1)) -> skip char a[i] and b[j]	 update a[i]/b[j]	distance + 1

Recursion Tree: f(10,6) -> f(i,j)  i=sizeof(a)-1, j=sizeof(b)-1; assume every level a[i] and b[j] is different
									
									f(10,6)
								/		|	    \
						/	    	    |		        \
				f(9,6)               f(10,5)               f(9,5)
			  /   |   \	            /   |   \	         /    |    \
		f(8,6) f(9,5) f(8,5)   f(9,5) f(10,4) f(9,4)  f(8,5) f(9,4) f(8,4) ...

		if (i == 0 || j == 0)
			return (a[0]/b[0] == b[j]/a[i]) ? 0 : 1 
		else
			return 1 + min(f(i-1, j), f(i, j-1), f(i-1, j-1))

状态转移方程:
	如果：a[i]!=b[j]，那么：min_edist(i, j) 就等于：
	min(min_edist(i-1,j)+1, min_edist(i,j-1)+1, min_edist(i-1,j-1)+1)
	
	如果：a[i]==b[j]，那么：min_edist(i, j) 就等于：
	min(min_edist(i-1,j)+1, min_edist(i,j-1)+1，min_edist(i-1,j-1))
	
	其中，min 表示求三数中的最小值。

*/
int minEditDistance(char a[], char b[], int n, int m);

/*****************************Edit Distance End*******************************/
