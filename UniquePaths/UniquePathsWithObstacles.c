#include <stdio.h>
#include <stdlib.h>

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


	//initialize to zero
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			grid[i][j] = 0;
		}
	}
	return grid;
}

int uniquePathsWithObstacles(int** grid, int m, int n){
	//allocate 2D array
	int **dp = malloc(sizeof(int *) * m);
	for(int i = 0; i < m; i++){
		dp[i] = malloc(sizeof(int) * n);
	}

	//Base cases:
	dp[0][0] = 1;

	//Inductive
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){

			//if there exist a obstacle in grid[i][j]
			if(grid[i][j] == 1){
				dp[i][j] = 0;
				continue;
			}

			//skip the base case
			if(i==0 && j==0) continue;

			//edge case if i > 0, j = 0, only top block can go to (i,j)
			else if(i > 0 && j==0) dp[i][j] = dp[i-1][j];

			//edge case if i = 0, j > 0, only left block can go to (i,j)
			else if(i==0 && j > 0) dp[i][j] = dp[i][j-1];

			//F(i,j) = F(i-1,j) + F(i,j-1)
			else dp[i][j] = dp[i-1][j] + dp[i][j-1];

		}
	}
	int result = dp[m-1][n-1];
	freeMemory(dp,m);
	return result;
}


int main(){

	int **grid1 = constructGrid(3,3);
	int **grid2 = constructGrid(2,2);
	int **grid3 = constructGrid(1,1);
	int **grid4 = constructGrid(3,4);

	//set the obstacle
	grid1[1][1] = 1;

	grid2[0][1] = 1;

	grid3[0][0] = 1;
	
	grid4[1][2] = 1;
	grid4[1][3] = 1;

    printf("%d\n", uniquePathsWithObstacles(grid1, 3, 3));
    printf("%d\n", uniquePathsWithObstacles(grid2, 2, 2));
    printf("%d\n", uniquePathsWithObstacles(grid3, 1, 1));
    printf("%d\n", uniquePathsWithObstacles(grid4, 3, 4));
    freeMemory(grid1,3);
    freeMemory(grid2,2);
    freeMemory(grid3,1);
    freeMemory(grid4,3);
	return 0;
}