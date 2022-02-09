#include <stdio.h>
#include <stdlib.h>

void freeMemory(int **array, int n){
	for(int i = 0; i <= n; i++){
		free(array[i]);
	}
	free(array);
}

int numWays(int n){
	int **dp = malloc(sizeof(int *) * (n + 1));
	for(int i = 0; i <=n; i++){
		//store two color
		dp[i] = malloc(sizeof(int) * 2);
	}

	//define green: 1, blue: 0

	//Base Case
	dp[1][0] = 1; //0
	dp[1][1] = 1; //1
	dp[2][0] = 2; //00 10
	dp[2][1] = 2; //01 11

	for(int i = 3; i <= n; i++){
		for(int j = 0; j <= 1; j++){
			dp[i][j] = dp[i - 1][1 - j] + dp[i - 2][1 - j];
		}
	}
	int result = dp[n][0] + dp[n][1];
	freeMemory(dp,n);
	return result;
}

int main(){
	printf("%d\n", numWays(3));
	printf("%d\n", numWays(4));
	printf("%d\n", numWays(5));
	return 0;
}