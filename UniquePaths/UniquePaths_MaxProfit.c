#include <stdio.h>
#include <stdlib.h>

int max(int a, int b){
	return a > b ? a : b;
}

void freeMemory(int **array, int m){
	for(int i = 0; i < m; i++){
		free(array[i]);
	}
	free(array);
}

int **constructGrid(int m, int n){
	int **grid = malloc(sizeof(int *) * m);
	for(int i = 0; i < m; i++){
		grid[i] = malloc(sizeof(int) * n);
	}
	return grid;
}

int uniquePathsMaxProfit(int** grid, int m, int n){
	//allocate 2D array
	int **dp = malloc(sizeof(int *) * m);
	for(int i = 0; i < m; i++){
		dp[i] = malloc(sizeof(int) * n);
	}

	dp[0][0] = 0;

	//Inductive
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){

			//skip the base case
			if(i==0 && j==0) continue;

			//edge case if i > 0, j = 0, only top block can go to (i,j)
			else if(i > 0 && j==0) dp[i][j] = grid[i][j] +  dp[i-1][j];

			//edge case if i = 0, j > 0, only left block can go to (i,j)
			else if(i==0 && j > 0) dp[i][j] = grid[i][j] + dp[i][j-1];

			//F(i,j) = grid[i][j] + max(F(i-1,j) , F(i,j-1)) 
			else dp[i][j] = grid[i][j] + max(dp[i-1][j] , dp[i][j-1]);

		}
	}
	int result = dp[m-1][n-1];
	freeMemory(dp,m);
	return result;
}


int main(){

	int **grid = constructGrid(3,4);

	//set the profit
	grid[0][0] = 0, grid[0][1] = 2, grid[0][2] = 2, grid[0][3] = 1;
	grid[1][0] = 3, grid[1][1] = 1, grid[1][2] = 1, grid[1][3] = 1;
	grid[2][0] = 4, grid[2][1] = 4, grid[2][2] = 2, grid[2][3] = 0;

    printf("%d\n", uniquePathsMaxProfit(grid, 3, 4));

    //reset the grid
    grid[0][0] = 0, grid[0][1] = 2, grid[0][2] = 2, grid[0][3] = 50;
	grid[1][0] = 3, grid[1][1] = 1, grid[1][2] = 1, grid[1][3] = 100;
	grid[2][0] = 4, grid[2][1] = 4, grid[2][2] = 2, grid[2][3] = 0;

	printf("%d\n", uniquePathsMaxProfit(grid, 3, 4));

    freeMemory(grid,3);
	return 0;
}