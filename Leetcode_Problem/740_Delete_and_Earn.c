#define SIZE 10001

int max(int a, int b){
	return a > b ? a : b;
}

//1. we can safely take all of its copies
//2. we can't take any of copies of nums[i-1] and nums[i+1]
//Can be reduces to House Robber


int deleteAndEarn(int* nums, int numsSize){
	//calculate how many times does each number appear in the list
	int count[SIZE] = {0};
	for(int i = 0; i < numsSize; i++){
		count[nums[i]]++;
	}

	int *dp = malloc(sizeof(int ) * SIZE);

	//Base case
	dp[0] = count[0];
	dp[1] = max(count[0], count[1]);

	for(int i = 2; i < SIZE; i++){
		dp[i] = max(dp[i - 1], dp[i - 2] + i * count[i]);
	}
	int result = dp[SIZE - 1];
	free(dp);
	return result;
}

int deleteAndEarn(int* nums, int numsSize){
	//calculate how many times does each number appear in the list
	int count[SIZE] = {0};
	for(int i = 0; i < numsSize; i++){
		count[nums[i]]++;
	}


	//Base case
	int dp0 = count[0];
	int dp1 = max(count[0], count[1]);

	int result;
	for(int i = 2; i < SIZE; i++){
		result = max(dp1, dp0 + i * count[i]);
		dp0 = dp1;
		dp1 = result;
	}
	return result;
}