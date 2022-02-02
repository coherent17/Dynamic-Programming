#include <stdio.h>
#include <stdlib.h>

//time complexity: O(nk), space complexity: O(n) [can be optimized to O(k)]
//return the number of distinct ways to reach the n-th stair by using 1 to k steps
int climbStairs(int n, int k){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;
    dp[1] = 1;

    //inductive to find answer
    for (int i = 2; i <= n;i++){
    	//calculate dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - k]
    	dp[i] = 0;
    	for(int j = 1; j<= k; j++){

    		//edge case: if i < j -> dp[negative number]
    		if(i < j){
    			continue;
    		}
    		dp[i] += dp[i - j];
    	}

    }
    int result = dp[n];
    free(dp);
    return result;
}

int main(){
    printf("%d \n", climbStairs(3,2));
    printf("%d \n", climbStairs(5,2));
    printf("%d \n", climbStairs(3,3));
    printf("%d \n", climbStairs(5,3));
    printf("%d \n", climbStairs(10,3));
    return 0;
}