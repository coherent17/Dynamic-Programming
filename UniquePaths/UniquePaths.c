#include <stdio.h>
#include <stdlib.h>

void freeMemory(int **array, int m){
	for(int i = 0; i < m; i++){
		free(array[i]);
	}
	free(array);
}

int UniquePaths(int m, int n){

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
	printf("%d \n", UniquePaths(1,1));
	printf("%d \n", UniquePaths(3,4));
	printf("%d \n", UniquePaths(3,7));
	return 0;
}