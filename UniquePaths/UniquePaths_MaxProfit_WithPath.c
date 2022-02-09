#include <stdio.h>
#include <stdlib.h>

#define MAX_PATH_LENGTH 6
#define PRINTDPMODE 0

typedef struct _position{
	int x;
	int y;
}position;

//global variable
int path_index = 0;
position path[MAX_PATH_LENGTH];

int max(int a, int b){
	return a > b ? a : b;
}

void freeMemory(int **array, int m){
	for(int i = 0; i < m; i++){
		free(array[i]);
	}
	free(array);
}

int **constructGrid(int m, int n){
	int **grid = malloc(sizeof(int *) * m);
	for(int i = 0; i < m; i++){
		grid[i] = malloc(sizeof(int) * n);
	}
	return grid;
}

int **initArray(int **array, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			array[i][j] = 0;
		}
	}
	return array;
}

void print2DArray(int **array, int row, int col){
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			printf("%3d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void initPath(position *path){
	for(int i = 0; i < MAX_PATH_LENGTH; i++){
		path[i].x = 0;
		path[i].y = 0;
	}
}

void printPath(position *path){
	for(int i = 0; i < path_index; i++){
		printf("(%d,%d) -> ", (path[i]).x, (path[i]).y);
	}
	printf("\n");
}

void append(position *path, int i, int j){
	(path[path_index]).x = i;
	(path[path_index]).y = j;
	path_index++;
}

//back trace the path recursively by dp array
void getPath(int **dp, int i, int j, position *path){

	//Base Case
	if(i==0 && j==0){
		return append(path, i, j);
	}

	//can only come from left
	else if(i==0) getPath(dp, i, j-1, path); 

	//can only come from top
	else if(j==0) getPath(dp, i-1, j, path);

	else{
		if(dp[i-1][j] > dp[i][j-1]){
			getPath(dp, i - 1, j, path);
		}
		else{
			getPath(dp, i, j - 1, path);
		}
	}
	return append(path, i, j);;
}


int uniquePathsMaxProfit(int** grid, int m, int n){
	//allocate 2D array
	int **dp = malloc(sizeof(int *) * m);
	for(int i = 0; i < m; i++){
		dp[i] = malloc(sizeof(int) * n);
	}
	dp = initArray(dp, m, n);

	dp[0][0] = 0;

	//Inductive
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){

			//skip the base case
			if(i==0 && j==0) continue;

			//edge case if i > 0, j = 0, only top block can go to (i,j)
			else if(i > 0 && j==0) dp[i][j] = grid[i][j] +  dp[i-1][j]; 

			//edge case if i = 0, j > 0, only left block can go to (i,j)
			else if(i==0 && j > 0) dp[i][j] = grid[i][j] + dp[i][j-1];

			//F(i,j) = grid[i][j] + max(F(i-1,j) , F(i,j-1)) 
			else dp[i][j] = grid[i][j] + max(dp[i-1][j] , dp[i][j-1]);

			if(PRINTDPMODE){
				print2DArray(dp, m, n);
			}
		}
	}
	int result = dp[m-1][n-1];

	//find the path
	path_index = 0;
	initPath(path);
	getPath(dp, m-1, n-1, path);
	printPath(path);
	freeMemory(dp,m);
	return result;
}


int main(){

	int **grid = constructGrid(3,4);

	//set the profit
	grid[0][0] = 0, grid[0][1] = 2, grid[0][2] = 2, grid[0][3] = 1;
	grid[1][0] = 3, grid[1][1] = 1, grid[1][2] = 1, grid[1][3] = 1;
	grid[2][0] = 4, grid[2][1] = 4, grid[2][2] = 2, grid[2][3] = 0;

	printf("max profit = %d\n", uniquePathsMaxProfit(grid, 3, 4));

	//reset the grid
	grid[0][0] = 0, grid[0][1] = 2, grid[0][2] = 2, grid[0][3] = 50;
	grid[1][0] = 3, grid[1][1] = 1, grid[1][2] = 1, grid[1][3] = 100;
	grid[2][0] = 4, grid[2][1] = 4, grid[2][2] = 2, grid[2][3] = 0;

	printf("max profit = %d\n", uniquePathsMaxProfit(grid, 3, 4));
	
	freeMemory(grid,3);
	return 0;
}