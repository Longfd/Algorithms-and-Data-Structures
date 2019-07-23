#include "dynamicPrograming.h"

// A utility function returns maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

/*
In the following recursion tree, K() refers to knapSack().  
The two parameters indicated in the following recursion tree are n and W.  
The recursion tree is for following sample inputs.
wt[] = {1, 1, 1}, W = 2, val[] = {10, 20, 30}

                       K(3, 2)         ---------> K(n, W)
                   /            \ 
                 /                \               
            K(2,2)                  K(2,1)
          /       \                  /    \ 
        /           \              /        \
       K(1,2)      K(1,1)        K(1,1)     K(1,0)
       /  \         /   \          /   \
     /      \     /       \      /       \
K(0,2)  K(0,1)  K(0,1)  K(0,0)  K(0,1)   K(0,0)
Recursion tree for Knapsack capacity 2 units and 3 items of 1 unit weight.
*/
int knapsack(int W, int wt[], int val[], int n)
{
	// Base Case
	if (n == 0 || W == 0)
		return 0;

	// If weight of the nth item is more than Knapsack capacity W,
	// then this item cannot be included in the optimal solution
	if (wt[n - 1] > W)
		return knapsack(W, wt, val, n - 1);

	// Return the maximum of two cases:
	// (1) nth item included
	// (2) nth item not included
	else return max(val[n - 1] + knapsack(W - wt[n - 1], wt, val, n - 1),
		knapsack(W, wt, val, n - 1));
}

int knapsack2(int W, int wt[], int val[], int idx, int n) // idx from 0 to n - 1
{
	// return condition
	if (idx == n || W == 0)
		return 0;

	if (wt[idx] > W)
		return knapsack2(W, wt, val, idx + 1, n);
	else
		return max(val[idx] + knapsack2(W - wt[idx], wt, val, idx + 1, n),
			knapsack2(W, wt, val, idx + 1, n));
}

// Build table K[][] in bottom up manner
int knapsack3(const int W, int wt[], int val[], const int n)
{
	// construct K[n+1][W+1]
	int** K = (int**)calloc(sizeof(int*), n+1);
	for(int i = 0; i < n + 1; i++)
		K[i] = (int*)calloc(sizeof(int), W + 1);

	for (int i = 0; i < n + 1; i++)
	{
		for (int w = 0; w < W + 1; w++)
		{// logic the same as recursion func: knapsack(); use space exchange for time
			if (i == 0 || w == 0)
				K[i][w] = 0;
			else if (wt[i - 1] > w)
				K[i][w] = K[i - 1][w];
			else // wt[i - 1] <= w
				K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
		}
	}

	// free
	int max = K[n][W];
	for (int i = 0; i < n + 1; i++)
		free(K[i]);
	free(K);

	return max;
}

// use recursion O(2^n)
#define ROW 4
#define COLUMN 4
int shortestPath(int w[][COLUMN], int i, int j)
{
	if (i == 0 && j == 0) return w[0][0];

	if (i == 0)
		return shortestPath(w, i, j - 1) + w[i][j];
	else if (j == 0)
		return shortestPath(w, i - 1, j) + w[i][j];
	else
		return w[i][j] + min(shortestPath(w, i, j - 1), shortestPath(w, i - 1, j));
}

// use recursion with duplicate array, < O(2^n)
int K1[ROW][COLUMN] = { 0 };
int shortestPath2(int w[][COLUMN], int i, int j)
{
	if (i == 0 && j == 0) return w[0][0];

	if (K1[i][j] != 0) return K1[i][j];

	if (i == 0)
		K1[i][j] = w[i][j] + shortestPath2(w, i, j - 1);
	else if (j == 0)
		K1[i][j] = w[i][j] + shortestPath2(w, i - 1, j);
	else
		K1[i][j] = w[i][j] + min(shortestPath2(w, i, j - 1), shortestPath2(w, i - 1, j));

	return K1[i][j];
}

// use formula with table O(n*m)
/*
  j	0	1	2	3
i_________________		if i == 0 && j == 0  k[i][j] = matrix[0][0]
0|  1	4	9	18		if i == 0 && j != 0  k[i][j] = k[i][j-1] + matrix[i][j]
1|	3	4	7	11		if j == 0 && i != 0  k[i][j] = k[i-1][j] + matrix[i][j]
2|	8	6	12	18		if j != 0 && i != 0  k[i][j] = min(k[i][j-1], k[i-1][j])
3|	14	14	16	19
*/
int K[ROW][COLUMN] = { 0 };
int shortestPath3(int w[][COLUMN], int n, int m)
{
	for (int i = 0; i <= n; i++) 
	{
		for (int j = 0; j <= m; j++)
		{
			if (i == 0 && j == 0)
				K[i][j] = w[i][j];
			else if (i == 0)
				K[i][j] = w[i][j] + K[i][j - 1];
			else if (j == 0)
				K[i][j] = w[i][j] + K[i - 1][j];
			else
				K[i][j] = w[i][j] + min(K[i][j - 1], K[i - 1][j]);
		}
	}

	return K[n][m];
}

void dynamicProgramingTest()
{
	int val[] = { 60,100,120 };
	int wt[] = { 10,20,30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);

	cout << "knapsack():" << knapsack(W, wt, val, n) << endl;
	cout << "knapsack2():" << knapsack2(W, wt, val, 0, n) << endl;
	cout << "knapsack3():" << knapsack3(W, wt, val, n) << endl;

	int w[ROW][COLUMN] = { {1,3,5,9},
						 {2,1,3,4},
						 {5,2,6,7},
						 {6,8,4,3} };
	cout << "shortestPath():" << shortestPath(w, ROW - 1, COLUMN - 1) << endl;
	cout << "shortestPath2():" << shortestPath2(w, ROW - 1, COLUMN - 1) << endl;
	cout << "shortestPath3():" << shortestPath3(w, ROW - 1, COLUMN - 1) << endl;
}
