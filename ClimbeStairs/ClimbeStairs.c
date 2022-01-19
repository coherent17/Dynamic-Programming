#include <stdio.h>
#include <stdlib.h>

int climbStairs(int n){
    int *dp = malloc(sizeof(int) * (n + 1));
    dp[0] = 1;
    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n;i++){
        dp[i] = dp[i - 1] + dp[i - 2];
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
    printf("%d \n", climbStairs(4));
    printf("%d \n", climbStairs(10));
    return 0;
}