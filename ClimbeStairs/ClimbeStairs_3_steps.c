#include <stdio.h>
#include <stdlib.h>

//time complexity: O(n), space complexity: O(n)

int climbStairs(int n){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;

    //inductive to find answer
    for (int i = 3; i <= n;i++){
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    int result = dp[n];
    free(dp);
    return result;
}

int main(){
    printf("%d \n", climbStairs(0));
    printf("%d \n", climbStairs(1));
    printf("%d \n", climbStairs(2));
    printf("%d \n", climbStairs(3));
    printf("%d \n", climbStairs(5));
    printf("%d \n", climbStairs(10));
    return 0;
}