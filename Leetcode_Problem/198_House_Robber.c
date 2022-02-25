int max(int a, int b){
	return a > b ? a : b;
}

//two options to rob (define dp[i] = the maximum number to rob to the i-th)

//1. if we rob i, then we can't rob i - 1: dp[i] = nums[i] + dp[i - 2]; 

//2. if we don't rob i, rob[i] = rob[i - 1]


//transition function
// dp [i] = max(dp[i -1], dp[i - 2]) + nums[i]

int rob(int* nums, int numsSize){

	//edge case
	if(numsSize==1) return nums[0];

	int *dp = malloc(sizeof(int) * (numsSize));

	//Base case
	dp[0] = nums[0]; //rob the first apartment
	dp[1] = max(nums[0], nums[1]); //rob either the first or the second apartment

	for(int i = 2; i < numsSize; i++){
		dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
	}
	int result = dp[numsSize - 1];
	free(dp);
	return result;
}

//space complexity optimized: O(n) -> O(1)
int rob(int *nums, int numsSize){

	//edge case
	if(numsSize==1) return nums[0];
	else if(numsSize==2) return max(nums[0], nums[1]);

	int result;
	int dp_0 = nums[0];
	int dp_1 = max(nums[0], nums[1]);

	for(int i = 2; i < numsSize; i++){
		result = max(dp_1, dp_0 + nums[i]);
		dp_0 = dp_1;
		dp_1 = result;
	}
	return result;
}