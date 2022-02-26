int max(int a, int b){
	return a > b ? a : b;
}


//solution ignore the first or the end apartment, dp twice

int rob(int* nums, int numsSize){
	if(numsSize == 1) return nums[0];
	if(numsSize == 2) return(max(nums[0], nums[1]));

	int *dp = malloc(sizeof(int ) * numsSize - 1);

	//ignore the end house
	//Base case:
	dp[0] = nums[0];
	dp[1] = max(nums[0], nums[1]);


	//ignore the end of the apartment
	for(int i = 2; i < numsSize - 1; i++){
		dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
	}
	int result1 = dp[numsSize - 2];


	//ignore the first house
	//Base case:
	dp[0] = nums[1];
	dp[1] = max(nums[1], nums[2]);

	for(int i = 3; i < numsSize; i++){
		dp[i - 1] = max(dp[i - 2], dp[i - 3] + nums[i]);
	}
	int result2 = dp[numsSize - 2];
	free(dp);
	return max(result1, result2);
}