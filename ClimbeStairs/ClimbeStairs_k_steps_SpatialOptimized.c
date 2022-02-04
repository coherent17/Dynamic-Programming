#include <stdio.h>
#include <stdlib.h>

#define printDPMode 1
//time complexity: O(nk), space complexity: O(k)
//return the number of distinct ways to reach the n-th stair by using 1 to k steps

void print_dp(int *dp, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", dp[i]);
    }
    printf("\n");
}

int climbStairs(int n, int k){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;

    //inductive to find answer
    for (int i = 1; i <= n;i++){
    	//calculate dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - k]
    	dp[i] = 0; //initialize the partial sum to zero
    	for(int j = 1; j< k; j++){

    		//edge case: if i < j -> dp[negative number]
    		if(i < j){
    			continue;
    		}
    		dp[i % k] += dp[(i - j)%k];
    	}

        //show the dp array at each round if debug mode is true
        if(printDPMode){
            printf("i = %d: ", i);
            print_dp(dp, k);
        }
    }
    int result = dp[n % k];
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