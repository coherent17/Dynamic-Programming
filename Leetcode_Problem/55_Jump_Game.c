bool canJump(int* nums, int numsSize){
	int LastGoodIndex = numsSize - 1;
	for(int i = numsSize - 1; i >=0 i--){
		if(i + nums[i] >= LastGoodIndex){
			LastGoodIndex = i;
		}
	}
	return LastGoodIndex==0;
}

int max(int a, int b){
	return a > b ? a : b;
}

//dp[i] = store the remaining jump ability
//transistion function: dp[i] = max(dp[i - 1], nums[i - 1]) - 1
//                                  (remaining jump ability in last position)
//                                             (the new jump ability in last position)											

bool canJump(int* nums, int numsSize){
	
	//dp array record the remaining step can jump
	int *dp = malloc(sizeof(int) * numsSize);

	for(int i = 1; i < numsSize; i++){
		dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
		if(dp[i] < 0) return false;
	} 
	return true;
}
