int min(int a, int b){
	return (a > b) ? b : a;
}

//without space optimize
int minCostClimbingStairs(int* cost, int costSize){
	int *dp = malloc(sizeof(int) * (costSize + 1));

	//Base case:
	dp[0] = cost[0];
	dp[1] = cost[1];

	for(int i = 2; i < costSize; i++){
		dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
	}
	int result = min(dp[costSize - 1], dp[costSize - 2]);
	free(dp);
	return result;
}

//space optimize
int minCostClimbingStairs(int* cost, int costSize){

	//edge case:
	if(costSize==2) return min(cost[0], cost[1]);

	//Base case:
	int dp_0 = cost[0];
	int dp_1 = cost[1];
	int result = 0;

	for(int i = 2; i < costSize; i++){
		result = cost[i] + min(dp_0, dp_1);
		dp_0 = dp_1;
		dp_1 = result;
	}
	return min(result, dp_0);
}