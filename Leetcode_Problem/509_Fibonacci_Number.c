//F(n) = F(n - 1) + F(n - 2)

//recursive
int fib(int n){
	if(n==0 || n==1) return n;

	else{
		return fib(n - 1) + fib(n - 2);
	}
}

//dynamic programming
int fib(int n){

	//Base Case
	if(n==0 || n==1) return n;
	int dp_0 = 0;
	int dp_1 = 1;

	int result = 0;
	for(int i = 2; i <= n; i++){
		result = dp_0 + dp_1;
		dp_0 = dp_1;
		dp_1 = result;
	}
	return result;
}