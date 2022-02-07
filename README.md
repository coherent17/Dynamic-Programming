# Dynamic Programming
[TOC]
## Introduction
為一種解題方法，可以將時間複雜度為exponential time$O(c^n)$優化成polynomial time$O(n^c)$甚至是linear time$O(n)$。那是甚麼樣的問題可以使用dynamic programming呢?要有以下兩種特性的題目才能夠使用dynamic programming的方法來加速。
*    1. Optimal Substructure(最佳子結構性質)
        We can get optimal solution to the problem by combining the optimal solution by the subproblem.
*    2. Overlapping Subproblems(子問題重疊性質)
        If you solve the same subproblems many times, then the overlapping property also present.

## How to recognize the DP problem
*    Combinatorial(Count something)
        *    How many ways to make a change?
        *    How many ways to traverse a graph?
        *    How many steps needed to get from point A to point B?
*    Optimization(Minimize or maximize the function)
        *    What is the minimum numbers of steps needed to get from point A to point B?
        *    What is the maximum profit gained by buying and selling a stock?


## Partial Sum problem
Find the sum of the first n number in nature number.
\begin{gather*}1 + 2 + 3 + 4 +...+ n =  \displaystyle\sum_{n=1}^{n} n\end{gather*}
假設我們沒有學過累加的數學運算，不知道可以透過下式來計算
\begin{gather*}\frac{n \cdot (n+1)}{2}\end{gather*}

推導關係式:
定義$F(n)$為從$1+2+...+n$的結果
可以得知:
\begin{gather*} F(1) = 1\end{gather*}
\begin{gather*} F(2) = F(1) + 2 = 3\end{gather*}
\begin{gather*} F(3) = F(2) + 3 = 6\end{gather*}
\begin{gather*} F(n) = F(n-1) + n\end{gather*}

$F(2)$可以經由$F(1)$獲得，$F(3)$可以經由$F(2)$獲得，而$F(n)$則是從$F(n-1)$獲得。這就是dynamic programming的核心概念，不讓過去已經算出來的東西白算，而是透過之前已知的結果再往下延伸。使用額外的記憶體去儲存這些結果以換來較少的預算時間。

 code 如下:
```c=
#include <stdio.h>
#include <stdlib.h>

int n_Sum(int n){
    int *dp = malloc(sizeof(int) *(n + 1));
    
    //base case:
    dp[0] = 0;
    for (int i = 1; i <= n;i++){
        dp[i] = dp[i - 1] + i;
    }
    int result = dp[n];
    free(dp);
    return result;
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
```

## Climbing Stair Problem(Combinatorial Problem)
You are climbing a staircase. It takes n steps to reach the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

推導關係式:
定義$F(i)$為爬到第$i$層樓梯所有可能的方法數。
接著，將問題分成許多個小問題，一一擊破，並且考慮base case的邊界條件問題。

*    0 stair
        *    doing nothing(it still count for a method)
    $\rightarrow F(0) = 1$ 

*    1 stair
        *    1
    $\rightarrow F(1) = 1$

*    2 stairs
        *    1,1
        *    2
    $\rightarrow F(2) = 2$

假如我現在要到第$n$階的樓梯，因為一次只能爬一階或是兩階，所以我所在的前一個
位置可能是在第$n-1$階的樓梯或是第$n-2$階的樓梯，並沒有其他的可能性。如此一來，爬到第$n$階的樓梯的方法數為:爬到第$n-1$階及第$n-2$階樓梯的方法數的總和，因此可以列出下式:
\begin{gather*} F(n) = F(n-1) + F(n-2)\end{gather*}
剛好列出來的式子就是大名鼎鼎的費氏數列(Fibonacci sequence)。

 code 如下:
```c=
#include <stdio.h>
#include <stdlib.h>

//time complexity: O(n), space complexity: O(n)

int climbStairs(int n){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;
    dp[1] = 1;

    //inductive to find answer
    for (int i = 2; i <= n;i++){
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
```

這種寫法，會有一個很致命的缺點，當input的$n$很大時，將會需要allocate很大的記憶體空間來存這些結果，但是事實上，在每次計算時，僅需要取得前一個及前兩個的結果即可，因此只需要兩個變數來記錄就好，不需要花費那麼多的記憶體空間。

因此可以將上面的climbStairs優化如下:
```c=
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
```
僅需要去紀錄前兩個結果即可，不需要把所有中間的結果都記下來。

### Advanced Discussion

#### <font size=5>一次可以爬1,2,3,...k階樓梯</font>
原題:
You are climbing a staircase. It takes n steps to reach the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

倘若一次可以一次走1 2 3階的話，那要如何解呢?
一樣定義$F(i)$為走到第$i$階的所有方法數，在能夠走三階的情況下可以跟前面使用一樣的方法推得:
\begin{gather*} F(n) = F(n-1) + F(n-2) + F(n-3)\end{gather*}
從上式中，我們可以知道，若要求得$F(3)$的話，會需要3個base case。

Base Case:
*    $F(0) = 1$
*    $F(1) = 1$
*    $F(2) = 2$

有了上述的條件，就可以解出問題了。

code如下:
```c=
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
```

那假如想要更進一步去計算走到第$n$階樓梯且一次可以選擇走$1,2,3,...,k$步的話，則可以用將其更進一步推廣為:
\begin{gather*} F(n) = F(n-1) + F(n-2) + F(n-3) + ... + F(n-k)\end{gather*}
也就是說最少會需要$k$個base cases。

code如下:
```c=
#include <stdio.h>
#include <stdlib.h>

//time complexity: O(nk), space complexity: O(n) [can be optimized to O(k)]
//return the number of distinct ways to reach the n-th stair by using 1 to k steps
int climbStairs(int n, int k){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;
    dp[1] = 1;

    //inductive to find answer
    for (int i = 2; i <= n;i++){
    	//calculate dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - k]
    	dp[i] = 0;
    	for(int j = 1; j<= k; j++){

    		//edge case: if i < j -> dp[negative number]
    		if(i < j){
    			continue;
    		}
    		dp[i] += dp[i - j];
    	}

    }
    int result = dp[n];
    free(dp);
    return result;
}

int main(){
    printf("%d \n", climbStairs(3,2));
    printf("%d \n", climbStairs(5,2));
    printf("%d \n", climbStairs(3,3));
    printf("%d \n", climbStairs(5,3));
    printf("%d \n", climbStairs(10,3));
    return 0;
}
```
#### <font size=5>優化Space complexity</font>
但是這邊其實也不需要使用到$n$個空間的array來存，可以用前面一樣對space complexity的優化方法，其實只需要$k$個空間的array來存即可，所以再來改造一下吧!由上面推得的關係式，可以得知其實僅需要$k$個位置來存放即可。示意如下:

假設$n = 5, k = 3$(共有五階樓梯，而一次可以選擇要走一步或是兩步或是三步):

一開始的Base Case:
|   $i$   | 0        |    1     |    2     |
|:-------:| -------- |:--------:|:--------:|
| $dp[i]$ | $F(0)=1$ | $F(1)=1$ | $F(2)=2$ |

而接下來要計算踏到第三階的方法數$F(3)=F(2)+F(1)+F(0)$，而在這邊可以發現在之後的運算，已經不會再使用到$F(0)$了，因此將$dp[0]$的位置改為存放$F(3)=2+1+1=4$

|   $i$   |    0     |    1     |    2     |
|:-------:|:--------:|:--------:|:--------:|
| $dp[i]$ | $F(3)=4$ | $F(1)=1$ | $F(2)=2$ |

而接下來要計算踏到第四階的方法數$F(4)=F(3)+F(2)+F(1)$，而在這邊可以發現在之後的運算，已經不會再使用到$F(1)$了，因此將$dp[1]$的位置改為存放$F(4)=4+2+1=7$

|   $i$   |    0     |    1     |    2     |
|:-------:|:--------:|:--------:|:--------:|
| $dp[i]$ | $F(3)=4$ | $F(4)=7$ | $F(2)=2$ |

而接下來要計算踏到第五階的方法數$F(5)=F(4)+F(3)+F(2)$，而在這邊可以發現在之後的運算，已經不會再使用到$F(2)$了，因此將$dp[2]$的位置改為存放$F(5)=7+4+2=13$

|   $i$   |    0     |    1     |     2     |
|:-------:|:--------:|:--------:|:---------:|
| $dp[i]$ | $F(3)=4$ | $F(4)=7$ | $F(5)=13$ |

所以究竟要如何決定要把算出來的$F(i)$放在哪呢?其實將$i\%k$就可以得知要將算出來的結果放在哪邊了，如此一來便可以將Space complexity從$O(n)$降為$O(k)$。

code如下:
```c=
#include <stdio.h>
#include <stdlib.h>

#define printDPMode 1
//time complexity: O(nk), space complexity: O(k)
//return the number of distinct ways to reach the n-th stair by using 1 to k steps

void print_dp(int *dp, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", dp[i]);
    }
    printf("\n");
}

int climbStairs(int n, int k){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;

    //inductive to find answer
    for (int i = 1; i <= n;i++){
    	//calculate dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - k]
    	dp[i] = 0; //initialize the partial sum to zero
    	for(int j = 1; j< k; j++){

    		//edge case: if i < j -> dp[negative number]
    		if(i < j){
    			continue;
    		}
    		dp[i % k] += dp[(i - j)%k];
    	}

        //show the dp array at each round if debug mode is true
        if(printDPMode){
            printf("i = %d: ", i);
            print_dp(dp, k);
        }
    }
    int result = dp[n % k];
    free(dp);
    return result;
}

int main(){
    printf("%d \n", climbStairs(3,2));
    printf("%d \n", climbStairs(5,2));
    printf("%d \n", climbStairs(3,3));
    printf("%d \n", climbStairs(5,3));
    printf("%d \n", climbStairs(10,3));
    return 0;
}
```

#### <font size=5>跳過特定的樓梯不能走</font>

假設$n = 7, k = 3$(共有五階樓梯，而一次可以選擇要走一步或是兩步或是三步)，而其中第$1,3,4$階階不能踏上去，否則腳會受傷。

由前面的推導可以得知公式為:

\begin{gather*} F(n) = F(n-1) + F(n-2) + F(n-3) + ... + F(n-k)\end{gather*}


*    而紅色的index標示的是不能經過的樓梯，因為沒有辦法到該層階梯上，所以$F(1)=F(3)=F(4)=0$。
*    而當$i=0$時，$F(0)=1$。

將目前已知的部分填進dp array中可以得到如下:

|  $i$   |                0                | <font color="red">1</font> |  2  | <font color="red">3</font> | <font color="red">4</font> |  5  | 6   |  7  |
|:------:|:-------------------------------:|:--------------------------:|:---:|:--------------------------:|:--------------------------:|:---:| --- |:---:|
| $F(i)$ | **<font color="blue">1</font>** |             0              |     |             0              |             0              |     |     |     |

*    計算$i=2$時，將其帶入公式可以得到$F(2)=F(1)+F(0)=0+1=1$

|  $i$   |  0  | <font color="red">1</font> |                2                | <font color="red">3</font> | <font color="red">4</font> |  5  | 6   |  7  |
|:------:|:---:|:--------------------------:|:-------------------------------:|:--------------------------:|:--------------------------:|:---:| --- |:---:|
| $F(i)$ |  1  |             0              | **<font color="blue">1</font>** |             0              |             0              |     |     |     |

*    計算$i=5$時，將其帶入公式可以得到$F(5)=F(4)+F(3)+F(2)=0+0+1+=1$

|  $i$   |  0  | <font color="red">1</font> |  2  | <font color="red">3</font> | <font color="red">4</font> |                5                | 6   |  7  |
|:------:|:---:|:--------------------------:|:---:|:--------------------------:|:--------------------------:|:-------------------------------:| --- |:---:|
| $F(i)$ |  1  |             0              |  1  |             0              |             0              | **<font color="blue">1</font>** |     |     |

*    計算$i=6$時，將其帶入公式可以得到$F(6)=F(5)+F(4)+F(3)=1+0+0+=1$

|  $i$   |  0  | <font color="red">1</font> |  2  | <font color="red">3</font> | <font color="red">4</font> |  5  |                6                |  7  |
|:------:|:---:|:--------------------------:|:---:|:--------------------------:|:--------------------------:|:---:|:-------------------------------:|:---:|
| $F(i)$ |  1  |             0              |  1  |             0              |             0              |  1  | **<font color="blue">1</font>** |     |

*    計算$i=7$時，將其帶入公式可以得到$F(7)=F(6)+F(5)+(4)=1+1+0=2$

|  $i$   |  0  | <font color="red">1</font> |  2  | <font color="red">3</font> | <font color="red">4</font> |  5  |  6  |                7                |
|:------:|:---:|:--------------------------:|:---:|:--------------------------:|:--------------------------:|:---:|:---:|:-------------------------------:|
| $F(i)$ |  1  |             0              |  1  |             0              |             0              |  1  |  1  | **<font color="blue">2</font>** |

如此一來便可以計算出答案了。

code如下:
```c=
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define printDPMode 1

void print_dp(int *dp, int size){
    for(int i = 0; i < size; i++){
        printf("%d ", dp[i]);
    }
    printf("\n");
}

int climbStairs(int n, int k, bool *skipStair){
    int *dp = malloc(sizeof(int) * (n + 1));

    //base case
    dp[0] = 1;

    //inductive to find answer
    for (int i = 1; i <= n;i++){
    	//calculate dp[i] = dp[i - 1] + dp[i - 2] + ... + dp[i - k]
    	dp[i] = 0; //initialize the partial sum to zero
    	for(int j = 1; j< k; j++){

    		//edge case: if i < j -> dp[negative number]
    		if(i < j){
    			continue;
    		}

            if(skipStair[i - 1]) dp[i % k] = 0;
            else dp[i % k] += dp[(i - j)%k];
    	}

        //show the dp array at each round if debug mode is true
        if(printDPMode){
            printf("i = %d: ", i);
            print_dp(dp, k);
        }
    }
    int result = dp[n % k];
    free(dp);
    return result;
}

int main(){
    bool skipStair[8] = {false, true, false, true, true, false, false, false};
    printf("%d \n", climbStairs(7,3,skipStair));
    return 0;
}
```

## Climbing Stair Problem(Optimization Problem)
假設$n = 3, k = 2, cost=[0,3,2,4]$(共有三階樓梯，而一次可以選擇要走一步或是兩步，而走到第一階會被收3塊錢，第二階會被收2塊錢，到第三階會被收4塊錢，找到最少的花費走到第3階的走法。)

*    1. $F(i)$: the minimum cost to get to the i-th stair
*    2. Base Case:
        *    $F(0) = 0$
        *    $F(1) = 3$
        *    $F(2) = 2$ 
        
            有兩種走法，先到1再到2，而這樣的花費(5塊錢)是大於直接走兩步直接到第2的花費的(2塊錢)
        *    $F(3) = 6$

            直接跳到第2階，再走一步到第三階
*    3. $F(n)=cost[n]+min(F(n-1),F(n-2))$

code如下:
```c=
#include <stdio.h>
#include <stdlib.h>

int min(int a, int b){
	return (a > b) ? b : a;
}


//time complexity: O(n), Space complexity: O(n)
int ClimbStairs_MinCost(int n, int *cost){
	int *dp = malloc(sizeof(int) * (n + 1));

	//Base case:
	dp[0] = cost[0];
	dp[1] = cost[1];

	for(int i = 2; i <= n; i++){
		dp[i] = cost[i] + min(dp[i-1], dp[i-2]);
	}
	int result = dp[n];
	free(dp);
	return result;
}

int main(){
	int cost[4] = {0,3,2,4};
	printf("MinCost = %d\n", ClimbStairs_MinCost(3,cost));
	return 0;
}
```

### Advanced Discussion
到這邊已經可以算出最少要花費多少錢才可以走到樓梯的頂端了，但是仍然不知道實際上經過的路徑是什麼，接下來要想辦法紀錄所經過的路徑是什麼。

假設$n = 8, k = 2, cost=[0,3,2,4,6,1,1,5,3]$(共有8階樓梯，而一次可以選擇要走一步或是兩步，而走到不同階層上所要付的錢紀錄在cost array中。)

經由前面的分析可以推得計算的公式為:
\begin{gather*} F(n)=cost[n]+min(F(n-1),F(n-2))\end{gather*}

那接下來就可以將其一步一步計算得到結果，那這邊我們會需要使用到兩個array，一個用以計算$F(i)$的數值，而另一個用來記錄抵達該層階梯的前一層為哪一層。

*    紀錄走到該層所需的最少cost為多少。

|  $i$   |  0  |  1  | 2   | 3   | 4   | 5   | 6   |  7  |  8  |
|:------:|:---:|:---:| --- | --- | --- | --- | --- |:---:|:---:|
| $F(i)$ |     |     |     |     |     |     |     |     |     |


*    紀錄走第$i$階的前一個狀態是在哪一層，以方便追溯最終經過的路徑。(假設previous[2]=1，表示抵達第二層的前一個狀態為第一層，以此類推。)先將其全部初始化為-1，以知道哪些樓梯根本不會被經過。

|    $i$     |  0  |  1  | 2   |  3  | 4   | 5   | 6   |  7  |  8  |
|:----------:|:---:|:---:| --- |:---:| --- | --- | --- |:---:|:---:|
| $previous$ | -1  | -1  | -1  | -1  | -1  | -1  | -1  | -1  | -1  |

*    1. Base Case: 
        *    $F(0) = 0$
        *    $F(1) = 3$
        *    而這邊因為若要上到第一層樓梯的最少花費必定來自第零層樓梯，因此將$previous[1]$設為0，已表示在上到第一階樓梯前的狀態是在第零階樓梯。

|  $i$   |  0  |  1  | 2   | 3   | 4   | 5   | 6   |  7  |  8  |
|:------:|:---:|:---:| --- | --- | --- | --- | --- |:---:|:---:|
| $F(i)$ |  0  |  3  |     |     |     |     |     |     |     |


|    $i$     |  0  |             1              | 2   |  3  | 4   | 5   | 6   |  7  |  8  |
|:----------:|:---:|:--------------------------:| --- |:---:| --- | --- | --- |:---:|:---:|
| $previous$ | -1  | <font color="red">0</font> | -1  | -1  | -1  | -1  | -1  | -1  | -1  |

*    2.
        *    $F(2) = cost[2] + min(F(1), F(0)) = 2 + min(3,0) = 2 + 0 = 2$
        *    而造成第二層樓梯為min cost的狀態為從第零階跳兩層上來，因此將$previous[2]$設為0。

|  $i$   |  0  |  1  |  2  | 3   | 4   | 5   | 6   |  7  |  8  |
|:------:|:---:|:---:|:---:| --- | --- | --- | --- |:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |     |     |     |     |     |     |


|    $i$     |  0  |  1  |             2              |  3  | 4   | 5   | 6   |  7  |  8  |
|:----------:|:---:|:---:|:--------------------------:|:---:| --- | --- | --- |:---:|:---:|
| $previous$ | -1  |  0  | <font color="red">0</font> | -1  | -1  | -1  | -1  | -1  | -1  |

*    3.
        *    $F(3) = cost[3] + min(F(2), F(1)) = 4 + min(2,3) = 4 + 2 = 6$
        *    而造成第三層樓梯為min cost的狀態為從第二階跳一層上來，因此將$previous[3]$設為2。

|  $i$   |  0  |  1  |  2  |  3  | 4   | 5   | 6   |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:| --- | --- | --- |:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |     |     |     |     |     |


|    $i$     |  0  |  1  |  2  |             3              | 4   | 5   | 6   |  7  |  8  |
|:----------:|:---:|:---:|:---:|:--------------------------:| --- | --- | --- |:---:|:---:|
| $previous$ | -1  |  0  |  0  | <font color="red">2</font> | -1  | -1  | -1  | -1  | -1  |


*    4.
        *    $F(4) = cost[4] + min(F(3), F(2)) = 6 + min(6,2) = 6 + 2 = 8$
        *    而造成第四層樓梯為min cost的狀態為從第二階跳兩層上來，因此將$previous[4]$設為2。

|  $i$   |  0  |  1  |  2  |  3  |  4  | 5   | 6   |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:|:---:| --- | --- |:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |  8  |     |     |     |     |


|    $i$     |  0  |  1  |  2  |  3  |             4              | 5   | 6   |  7  |  8  |
|:----------:|:---:|:---:|:---:|:---:|:--------------------------:| --- | --- |:---:|:---:|
| $previous$ | -1  |  0  |  0  |  2  | <font color="red">2</font> | -1  | -1  | -1  | -1  |

*    5.
        *    $F(5) = cost[5] + min(F(4), F(3)) = 1 + min(8,6) = 1 + 6 = 7$
        *    而造成第五層樓梯為min cost的狀態為從第三階跳兩層上來，因此將$previous[5]$設為3。

|  $i$   |  0  |  1  |  2  |  3  |  4  |  5  | 6   |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:|:---:|:---:| --- |:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |  8  |  7  |     |     |     |


|    $i$     |  0  |  1  |  2  |  3  |  4  |             5              | 6   |  7  |  8  |
|:----------:|:---:|:---:|:---:|:---:|:---:|:--------------------------:| --- |:---:|:---:|
| $previous$ | -1  |  0  |  0  |  2  |  2  | <font color="red">3</font> | -1  | -1  | -1  |

*    6.
        *    $F(6) = cost[6] + min(F(5), F(4)) = 1 + min(7,8) = 1 + 7 = 8$
        *    而造成第六層樓梯為min cost的狀態為從第五階跳一層上來，因此將$previous[6]$設為5。

|  $i$   |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |  8  |  7  |  8  |     |     |


|    $i$     |  0  |  1  |  2  |  3  |  4  |  5  |             6              |  7  |  8  |
|:----------:|:---:|:---:|:---:|:---:|:---:|:---:|:--------------------------:|:---:|:---:|
| $previous$ | -1  |  0  |  0  |  2  |  2  |  3  | <font color="red">5</font> | -1  | -1  |

*    7.
        *    $F(7) = cost[7] + min(F(6), F(5)) = 5 + min(8,7) = 5 + 7 = 12$
        *    而造成第七層樓梯為min cost的狀態為從第五階跳兩層上來，因此將$previous[7]$設為5。

|  $i$   |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |  8  |  7  |  8  | 12  |     |


|    $i$     |  0  |  1  |  2  |  3  |  4  |  5  |  6  |             7              |  8  |
|:----------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:--------------------------:|:---:|
| $previous$ | -1  |  0  |  0  |  2  |  2  |  3  |  5  | <font color="red">5</font> | -1  |

*    8.
        *    $F(8) = cost[8] + min(F(7), F(6)) = 3 + min(12,8) = 3 + 8 = 11$
        *    而造成第八層樓梯為min cost的狀態為從第六階跳兩層上來，因此將$previous[8]$設為6。

|  $i$   |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |
|:------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| $F(i)$ |  0  |  3  |  2  |  6  |  8  |  7  |  8  | 12  | 11  |


|    $i$     |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |             8              |
|:----------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:--------------------------:|
| $previous$ | -1  |  0  |  0  |  2  |  2  |  3  |  5  |  5  | <font color="red">6</font> |

如次一來，有了previous這個array，便可以從任意的終點往回推經過的路徑為多少。假如終點為要抵達第八階的樓梯，可以往前推得8的前一個為6，6的前一個為5，5的前一個為3，3的前一個為2，2的前一個為0。便得到路徑為: $0 \rightarrow 2 \rightarrow 3 \rightarrow 5 \rightarrow 6 \rightarrow 8$

code 如下:
```c=
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
```