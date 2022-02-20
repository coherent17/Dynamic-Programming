//F(n) = F(n - 1) + F(n - 2)

//recursive
int climbStairs(int n){
	if(n==0 || n==1) return 1;

	else{
		return climbStairs(n - 1) + climbStairs(n - 2);
	}
}

//dynamic programming
int climbStairs(int n){

	//Base Case
	if(n==0 || n==1) return 1;
	int dp_0 = 1;
	int dp_1 = 1;

	int result = 0;
	for(int i = 2; i <= n; i++){
		result = dp_0 + dp_1;
		dp_0 = dp_1;
		dp_1 = result;
	}
	return result;
}