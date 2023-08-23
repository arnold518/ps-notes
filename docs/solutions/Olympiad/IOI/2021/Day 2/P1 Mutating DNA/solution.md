---
title: IOI 2021 Day 2 P1 Mutating DNA
tags:
    - ~ solution
---

# IOI 2021 Day 2 P1 Mutating DNA

## Problem

### Problem Link
[https://www.acmicpc.net/problem/22046](https://www.acmicpc.net/problem/22046)  
[https://oj.uz/problem/view/IOI21_dna](https://oj.uz/problem/view/IOI21_dna)

### Summary
"A", "T", "C"로 구성된 길이 $N$의 문자열 $A$와 $B$가 주어진다.  
$Q$개의 쿼리가 주어지며, $i$번 쿼리에서는 $A[L_i ... R_i]$의 두 문자를 swap하여 $B[L_i ... R_i]$와 같게 만들기 위하여 필요한 swap의 최소 횟수 (불가능하면 $-1$)을 구해야 한다. $(1 \le i \le Q)$

### Constraints

- $1 \le N \le 100,000$
- $1 \le Q \le 100,000$
- $1 \le L_i \le R_i \le N$ $(1 \le i \le Q)$


## Solution

우선, $A[L_i ... R_i]$, $B[L_i ... R_i]$에 있는 각 문자 "A", "T", "C"의 개수가 다르면 답은 $-1$이고, 같다면 $-1$이 아니다.

이제, $L_i \le j \le R_i$인 $j$에 대하여 순서쌍 $(A[j], B[j])$를 생각하자.
총 $9$가지의 가능한 순서쌍에 대하여, 각 순서쌍이 구간 내 몇 번 등장했는지를 구해 놓았다면, 이제 문자열 대신 $3 \times 3$ 크기의 각 순서쌍들의 개수를 나타내는 배열 $P$만 생각해도 된다.

우선, (A, A), (T, T), (C, C)와 같이 $A$의 문자와 $B$의 문자가 같은 칸들에 대해서는, 굳이 swap할 필요 없이 가만히 놔두어도 된다.
다음으로, 만약 (A, T), (T, A)의 두 순서쌍이 각각 $1$개 이상 존재한다고 생각하자.
이 두 순서쌍을 서로 swap해주면, 한 번의 swap으로 두 개의 칸에 조건을 만족시켰으며, 한 번의 swap으로는 최대 두 개의 칸 밖에 조건을 만족시키지 못한다는 것을 생각하면 이것이 최선의 선택임을 알 수 있다.
따라서, (A, T)와 (T, A), (A, C)와 (C, A), (T, C)와 (C, T)와 같이 서로 바뀌는 문자 쌍이 존재한다면, 이를 서로 swap하여 제거해준다.

이제 위 연산을 모두 실행하고 나면 남은 것은 정확히 같은 개수의 (A, T), (T, C), (C, A)와 같이 서로 순환하는 순서쌍들이다.
이 이유는 처음에 문자열 내 각 문자의 개수가 같다고 강제하였기 때문이다.
(A, T), (T, C), (C, A) 순서쌍을 해결하기 위해서는 2번의 연산으로 앞에서부터 하나씩 사이클을 해소해줄 수 있다.
따라서, 두 번의 swap으로 세 개의 칸에 조건을 만족시키게 되며, 이것이 현재 상황에서는 최적이다.
따라서, 남은 (A, T), (T, C), (C, A)와 같이 서로 순환하는 순서쌍들이 각각 $X$개 있었다고 하면, $2X$번의 swap으로 남은 문제를 해결할 수 있다.

!!! observation "Observation 1"  
    우선, $A[L_i ... R_i]$, $B[L_i ... R_i]$에 있는 각 문자 "A", "T", "C"의 개수가 다르면 답은 $-1$이고, 같다면 $-1$이 아니다.

    만약 답이 $-1$이 아니라면 최적해는 다음과 같다.  
    우선, (A, A), (T, T), (C, C)와 같이 $A$의 문자와 $B$의 문자가 같은 칸들에 대해서는, 굳이 swap할 필요 없이 가만히 놔두어도 된다.  
    다음으로, (A, T)와 (T, A), (A, C)와 (C, A), (T, C)와 (C, T)와 같이 서로 바뀌는 문자 쌍이 존재한다면, 이를 먼저 서로 swap하여 제거해준다.  
    마지막으로 남은 것은 정확히 같은 개수 $X$개의 (A, T), (T, C), (C, A)와 같이 서로 순환하는 순서쌍들이고, 이들을 앞에서부터 하나씩 사이클을 처리하여 $2X$번의 swap으로 남은 문제를 해결할 수 있다.


전체 풀이에서 각 쿼리별로 우리가 필요했던 것은 구간 안의 각 문자의 개수와, $3 \times 3$ 크기의 각 순서쌍들의 개수를 나타내는 배열 $P$이다.
이는 배열 $P$를 전체 문자열에 대하여 누적합 배열을 만들어 쿼리당 $O(1)$안에 구할 수 있고, 완성된 배열 $P$를 이용하여 문제를 해결하는 것 또한 $O(1)$이니, 전체 $O(N+Q)$에 문제를 해결할 수 있다.
  
    

!!! checkpoint "CheckPoint"
    **Observation 1**과 같이 최적해를 구할 수 있으며, 이 과정에서 필요한 것은 구간 안의 각 문자의 개수와, $3 \times 3$ 크기의 각 순서쌍들의 개수를 나타내는 배열 $P$이다.
    이는 배열 $P$를 전체 문자열에 대하여 누적합 배열을 만들어 쿼리당 $O(1)$안에 구할 수 있고, 완성된 배열 $P$를 이용하여 문제를 해결하는 것 또한 $O(1)$이니, 전체 $O(N+Q)$에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    Time Complexity : $O(N+Q)$

## Code
``` cpp linenums="1"
#include "dna.h"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 1e5;
 
int N, P[MAXN+10][3][3];
 
int f(char x)
{
	if(x=='A') return 0;
	if(x=='C') return 1;
	if(x=='T') return 2;
}
 
void init(string a, string b)
{
	N=a.size();
	for(int i=1; i<=N; i++)
	{
		for(int p=0; p<3; p++) for(int q=0; q<3; q++) P[i][p][q]=P[i-1][p][q];
		P[i][f(a[i-1])][f(b[i-1])]++;
	}
}
 
int get_distance(int l, int r) {
	l++; r++;
	int A[3][3]={{0}};
	for(int p=0; p<3; p++) for(int q=0; q<3; q++) A[p][q]=P[r][p][q]-P[l-1][p][q];
	for(int p=0; p<3; p++)
	{
		int t=0;
		for(int q=0; q<3; q++) t+=A[p][q]-A[q][p];
		if(t) return -1;
	}
 
	int ans=0;
	ans+=min(A[0][1], A[1][0]);
	ans+=min(A[0][2], A[2][0]);
	ans+=min(A[2][1], A[1][2]);
	ans+=abs(A[0][1]-A[1][0])*2;
	return ans;
}
```