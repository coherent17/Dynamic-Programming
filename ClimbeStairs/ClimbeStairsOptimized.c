#include <stdio.h>

//time complexity: O(n), space complexity: O(1)

int climbStairs(int n){

    int result = 0;

    //base case
    if(n==0 || n==1){
    	result = 1;
    	return result;
    }
    
    int front = 1;
    int tail = 1;

    //inductive to find answer
    for (int i = 2; i <= n;i++){
        result = front + tail;
        front = tail;
        tail = result;
    }
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