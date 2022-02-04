#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define printDPMode 1


void print_dp(int *dp, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", dp[i]);
    }
    printf("\n");
}

int climbStairs(int n, int k, bool *skipStair){
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

            if(skipStair[i - 1]) dp[i % k] = 0;
            else dp[i % k] += dp[(i - j)%k];
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
    bool skipStair[8] = {false, true, false, true, true, false, false, false};
    printf("%d \n", climbStairs(7,3,skipStair));
    return 0;
}