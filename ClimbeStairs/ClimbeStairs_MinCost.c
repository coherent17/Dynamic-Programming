#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
	return (a > b) ? b : a;
}

int ClimbStairs_MinCost(int n, int *cost){
	int *dp = malloc(sizeof(int) * (n + 1));

	//Base case:
	dp[0] = cost[0];
	dp[1] = cost[1];

	for(int i = 2; i <= n; i++){
		dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
	}
	int result = dp[n];
	free(dp);
	return result;
}

int main(){
	int cost[4] = {0,3,2,4};
	printf("MinCost = %d\n", ClimbStairs_MinCost(3,cost));
	return 0;
}