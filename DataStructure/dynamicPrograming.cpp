#include "dynamicPrograming.h"


// A utility function returns maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

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

void dynamicProgramingTest()
{
	int val[] = { 60,100,120 };
	int wt[] = { 10,20,30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);

	cout << "knapsack():" << knapsack(W, wt, val, n) << endl;
	cout << "knapsack2():" << knapsack2(W, wt, val, 0, n) << endl;
	cout << "knapsack3():" << knapsack3(W, wt, val, n) << endl;
}

