#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size){
	for(int i = 0; i <= size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int min(int a, int b){
	return (a > b) ? b : a;
}


//time complexity: O(n), Space complexity: O(n)
int ClimbStairs_MinCost(int n, int *cost){
	int *dp = malloc(sizeof(int) * (n + 1));

	//allocate previous array and initialize it
	int *previous = malloc(sizeof(int) * (n + 1));
	for(int i = 0; i <= n; i++){
		previous[i] = -1;
	}

	//Base case:
	dp[0] = cost[0];
	dp[1] = cost[1];

	previous[1] = 0;

	for(int i = 2; i <= n; i++){
		dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
		//update the previous array:
		previous[i] = (dp[i-1] < dp[i-2]) ? (i - 1) : (i - 2); 
	}
	printArray(dp, n);
	printArray(previous, n);
	int result = dp[n];
	free(dp);
	free(previous);
	return result;
}

int main(){
	int cost[9] = {0,3,2,4,6,1,1,5,3};
	printf("MinCost = %d\n", ClimbStairs_MinCost(8,cost));
	return 0;
}