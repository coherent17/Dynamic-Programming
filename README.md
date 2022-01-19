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

$F(2)$可以經由$F(1)$獲得，$F(3)$可以經由$F(2)$獲得，而$F(n)$則是從$F(n-1)$獲得。這就是dynamic programming的殼新概念，不讓過去已經算出來的東西白算，而是透過之前已知的結果再往下延伸。使用額外的記憶體去儲存這些結果以換來較少的預算時間。

### Code
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
結果:
![](https://i.imgur.com/p8z2Lsk.png)

## Climbing Stair Problem
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

### Code
```c=
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
```
結果:
![](https://i.imgur.com/NBOCZjP.png)
