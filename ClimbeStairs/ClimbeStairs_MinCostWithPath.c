#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

int min(int a, int b){
	return (a > b) ? b : a;
}


int *getPath(int *previous, int n, int *returnSize){
	//count the length of the path
	(*returnSize) = 0;
	for(int i = n; i >= 0; i = previous[i]){
		(*returnSize)++;
	}

	//allocate memory space for path array
	int *path = malloc(sizeof(int) * (*returnSize));
	
	//put the each stage in path array in reverse order
	int path_index = (*returnSize)-1;
	for(int i = n; i >= 0; i = previous[i]){
		path[path_index] = i;
		path_index--;
	} 
	return path;
}


int *ClimbStairs_MinCost(int n, int *cost, int *returnSize){
	int *dp = malloc(sizeof(int) * (n + 1));

	//allocate previous array and initialize it
	int *previous = malloc(sizeof(int) * (n + 1));
	for(int i = 0; i <= n; i++){
		previous[i] = -1;
	}

	//Base case:
	dp[0] = cost[0];
	dp[1] = cost[1];

	//since the first stair must come from the ground
	previous[1] = 0;

	for(int i = 2; i <= n; i++){
		//calculate the min cost for each stairs
		dp[i] = cost[i] + min(dp[i-1], dp[i-2]);

		//update the previous array
		previous[i] = (dp[i-1] < dp[i-2]) ? (i - 1) : (i - 2); 
	}

	printf("dp array: ");
	printArray(dp, n + 1);

	printf("previous array: ");
	printArray(previous, n + 1);

	//print the min cost
	int result = dp[n];
	printf("MinCost = %d\n", result);

	//get the path by previous array
	int *path = getPath(previous, n, returnSize);

	free(dp);
	free(previous);
	return path;
}

int main(){
	int returnSize;
	int cost[9] = {0,3,2,4,6,1,1,5,3};
	int *path = ClimbStairs_MinCost(8,cost, &returnSize);
	printf("path: ");
	printArray(path, returnSize);
	free(path);
	return 0;
}