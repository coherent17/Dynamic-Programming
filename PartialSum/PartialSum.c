#include <stdio.h>
#include <stdlib.h>

int n_Sum(int n){
    int *dp = malloc(sizeof(int) *(n + 1));
    
    //base case:
    dp[0] = 0;
    for (int i = 1; i <= n;i++){
        dp[i] = dp[i - 1] + i;
    }
    return dp[n];
}

//using math formula
int n_SumTest(int n){
    return n * (n + 1) / 2;
}

int main(){
    printf("%d %d\n", n_Sum(0), n_SumTest(0));
    printf("%d %d\n", n_Sum(1), n_SumTest(1));
    printf("%d %d\n", n_Sum(2), n_SumTest(2));
    printf("%d %d\n", n_Sum(3), n_SumTest(3));
    printf("%d %d\n", n_Sum(4), n_SumTest(4));
    printf("%d %d\n", n_Sum(5), n_SumTest(5));
    printf("%d %d\n", n_Sum(100), n_SumTest(100));
    return 0;
}