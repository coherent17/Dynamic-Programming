//T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

//recursive - TLE
int tribonacci(int n){
	if(n==0 || n==1) return n;
	else if(n==2) return 1;
	else return tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
}

//dynamic programming
int tribonacci(int n){

	//Base Case
	if(n==0 || n==1) return n;
	else if(n==2) return 1;
	int dp_0 = 0;
	int dp_1 = 1;
	int dp_2 = 1;

	int result = 0;
	for(int i = 3; i <= n; i++){
		result = dp_0 + dp_1 + dp_2;
		dp_0 = dp_1;
		dp_1 = dp_2;
		dp_2 = result;
	}
	return result;
}