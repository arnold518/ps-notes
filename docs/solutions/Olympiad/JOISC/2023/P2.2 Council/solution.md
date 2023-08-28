---
title: JOISC 2023 P2.2 Council
tags:
    - ~ solution
    - bitmask
    - dp
    - dp_sum_over_subsets
---

# JOISC 2023 P2.2 Council

## Problem

### Problem Link
[https://www.acmicpc.net/problem/27996](https://www.acmicpc.net/problem/27996)  
[https://oj.uz/problem/view/JOI23_council](https://oj.uz/problem/view/JOI23_council)

### Summary
$1, 2, ..., N$의 $N$명의 사람들이 있고, $1, 2, ..., M$의 $M$개의 정책이 있다.  
$A_{i, j}$는 $i$번 사람이 $j$번 정책에 대하여 찬성표를 던진다면 $1$, 아니면 $0$이다.  
$N$명의 사람들 중 회장 한명을 정하고, 회장을 제외한 사람들 중 부회장 한명을 정한 후, 남은 사람들에 대하여 모든 정책에 대한 투표를 진행한다.
각 정책에 대하여, 회장과 부회장을 제외한 나머지 사람들 중 찬성표의 수가 $\lfloor \frac{N}{2} \rfloor$표 이상이라면, 이 정책을 승인한다.  
$i$번 사람이 회장일 때, 부회장을 적당히 정했을 때 승인되는 정책의 수의 최댓값을 모든 $i$에 대해 구하여라. $(1 \le i \le N)$

### Constraints

- $3 \le N \le 300,000$
- $1 \le M \le 20$
- $0 \le A_{i, j} \le 1$ $(1 \le i \le N, 1 \le j \le M)$

## Solution

$N$에 비하여 $M$이 매우 작으니, $2^M$과 비슷한 시간복잡도에 문제를 해결할 수 있음에 유의하자.

각 정책에 대하여, 회장과 부회장을 제외한 후 사람들의 표를 셌을 때 $\lfloor \frac{N}{2} \rfloor$표 이상이어야지 정책이 승인된다.
회장과 부회장을 제외하지 않았을 때 정책 $j$의 전체 표의 수를 $C_j$라 하자.
만약, $C_j<\lfloor \frac{N}{2} \rfloor$ 이거나, $C_j \ge \lfloor \frac{N}{2} \rfloor+2$라면 여기서 $0, 1, 2$표를 제외한다고 해서 정책의 승인 여부가 바뀌지 않는다는 것을 알 수 있다.
따라서, 각 정책 $j$를 다음과 같은 $3$가지 상태로 요약할 수 있다.

- State $0$ : $C_j<\lfloor \frac{N}{2} \rfloor$이거나 $C_j \ge \lfloor \frac{N}{2} \rfloor+2$
- State $1$ : $C_j = \lfloor \frac{N}{2} \rfloor$
- State $2$ : $C_j = \lfloor \frac{N}{2} \rfloor + 1$

!!! observation "Observation 1"
    회장과 부회장을 제외하지 않았을 때 정책 $j$의 전체 표의 수를 $C_j$라 하자.  
    만약, $C_j<\lfloor \frac{N}{2} \rfloor$ 이거나, $C_j \ge \lfloor \frac{N}{2} \rfloor+2$라면 회장, 부회장의 선택과 무관하게 정책의 승인 여부가 바뀌지 않는다.  
    따라서 각 정책 $j$를 다음과 같은 $3$가지 상태로 요약할 수 있다.

    - State $0$ : $C_j<\lfloor \frac{N}{2} \rfloor$이거나 $C_j \ge \lfloor \frac{N}{2} \rfloor+2$
    - State $1$ : $C_j = \lfloor \frac{N}{2} \rfloor$
    - State $2$ : $C_j = \lfloor \frac{N}{2} \rfloor + 1$

만약 회장을 $i$번 사람으로 정했다고 생각하자.
이제, **Observation 1**에서 State $1$과 $2$에 속하는 정책들 중, $C_j - A_{i, j} = \lfloor \frac{N}{2} \rfloor$인 정책들만 부회장의 선택에 영향을 받고, 다른 정책들은 승인 여부가 바로 정해진다는 것을 알 수 있다.
각 정책에 대하여, $C_j - A_{i, j} = \lfloor \frac{N}{2} \rfloor$이면 $1$, 아니면 $0$으로 표현한 bitmask $mask$를 생각하자.
부회장을 $k$로 골랐다고 할 때, bitmask $A_k$와 $mask$를 bitwise and 하였을 때 $1$인 칸들은 승인되지 않는 정책들이니, $A_k \ \& \ mask$에 켜져 있는 칸들의 수를 최소화해야한다.

!!! observation "Observation 2"
    회장을 $i$번 사람으로 정했을 때, 각 정책에 대하여 $C_j - A_{i, j} = \lfloor \frac{N}{2} \rfloor$이면 $1$, 아니면 $0$으로 표현한 bitmask $mask$를 생각하자.
    부회장을 $k$로 골랐다고 할 때, 최적해에서는 $A_k \ \& \ mask$에 켜져 있는 칸들의 수를 최소화해야한다.

여러 개의 $mask$에 대하여 $A_k \ \& \ mask$에 켜져 있는 칸들의 수의 최솟값을 구하고 싶으니, SOS(Sum of Subset) DP를 이용하여 문제를 해결하자.
SOS DP를 그대로 적용할 수는 없고, $A_k$에서 시작하여 앞쪽부터 bit 몇 개를 바꾸며 $mask$로 바꾸어 나간다고 생각하자.
$A_k$의 비트를 $0 \rightarrow 0$, $0 \rightarrow 1$, $1 \rightarrow 0$, $1 \rightarrow 1$로 바꾸는 것이 모두 가능한데, 우리가 세고 싶은 것은 $A_k \ \& \ mask$에 켜져 있는 칸이니, $1 \rightarrow 1$의 변환이 발생할 때에만 값을 $1$ 증가시켜 세주면 된다.

단, 회장과 부회장의 번호는 달라야 하기 때문에 단순 최솟값을 구하면 안되고, 최솟값을 구한 후, 최솟값과 다른 번호의 두 번째 최솟값을 한번 더 구해주어야 한다.

따라서, 최솟값과 두 번째 최솟값을 SOS DP를 이용하여 한번 구해준 후, $N$명의 회장 후보에 대하여 답을 구해주면 되고, 전체 시간복잡도는 $O(2^MM+N)$이다.

!!! checkpoint "CheckPoint"
    **Observation 2**에 의하여 각 회장 $i$에 대하여 모든 가능한 부회장 $k$ 중 $A_k \ \& \ mask$에 켜져 있는 칸들의 수를 최소화해야한다.
    이는 SOS DP를 응용하여 구할 수 있고, $A_k$에서 시작하여 앞쪽부터 bit 몇 개를 바꾸며 $mask$로 바꾸어 나간다고 생각하면 된다.
    단, 회장과 부회장의 번호는 달라야 하기 때문에 최솟값과 다른 번호의 두 번째 최솟값을 한번 더 구해주어야 한다.
    따라서, 최솟값과 두 번째 최솟값을 SOS DP를 이용하여 한번 구해준 후, 모든 $N$명의 회장 후보에 대하여 답을 구해주면 되고, 전체 시간복잡도는 $O(2^MM+N)$이다.

!!! complexity "Complexity"
    Time Complexity : $O(2^MM+N)$

## Code
``` cpp linenums="1"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<pii, pii> ppp;

const int MAXN = 3e5;
const int MAXM = 20;
const int INF = 1e9;

int N, M, A[MAXN+10][MAXM+10];
int P[MAXM+10];
int B[MAXN+10];

ppp dp[(1<<MAXM)+10][MAXM+10];

pii operator + (pii &p, int q)
{
	return {p.first+q, p.second};
}

ppp operator + (ppp &p, int q)
{
	return {p.first+q, p.second+q};
}

void f(ppp &p, ppp q)
{
	if(p.first<q.first)
	{
		if(q.first.second==p.first.second) q.first=q.second;
		p={p.first, min(q.first, p.second)};
	}
	else
	{
		if(p.first.second==q.first.second) p.first=p.second;
		p={q.first, min(p.first, q.second)};
	}
}

int main()
{
	scanf("%d%d", &N, &M);
	for(int i=1; i<=N; i++) for(int j=0; j<M; j++) scanf("%d", &A[i][j]);
	for(int j=0; j<M; j++)
	{
		int cnt=0;
		for(int i=1; i<=N; i++) cnt+=A[i][j];
		if(cnt<N/2) P[j]=0;
		else if(cnt>N/2+1) P[j]=3;
		else if(cnt==N/2) P[j]=1;
		else if(cnt==N/2+1) P[j]=2;
	}

	for(int j=0; j<=M; j++) for(int i=0; i<(1<<M); i++) dp[i][j]={pii(INF, -1), pii(INF, -1)};
	for(int i=1; i<=N; i++)
	{
		for(int j=0; j<M; j++) B[i]|=(A[i][j]<<j);
		f(dp[B[i]][0], {pii(0, i), pii(INF, -1)});
	}

	for(int i=0; i<M; i++)
	{
		for(int j=0; j<(1<<M); j++)
		{
			if(P[i]==0)
			{
				f(dp[j][i+1], dp[j][i]+1);
				f(dp[j][i+1], dp[j^(1<<i)][i]+1);
			}
			if(P[i]==3)
			{
				f(dp[j][i+1], dp[j][i]);
				f(dp[j][i+1], dp[j^(1<<i)][i]);
			}	
			if(P[i]==1)
			{
				if(j&(1<<i))
				{
					f(dp[j][i+1], dp[j][i]+1);
					f(dp[j][i+1], dp[j^(1<<i)][i]+1);
				}
				else
				{
					f(dp[j][i+1], dp[j][i]);
					f(dp[j][i+1], dp[j^(1<<i)][i]+1);
				}
			}
			if(P[i]==2)
			{
				if(j&(1<<i))
				{
					f(dp[j][i+1], dp[j][i]+1);
					f(dp[j][i+1], dp[j^(1<<i)][i]);
				}
				else
				{
					f(dp[j][i+1], dp[j][i]);
					f(dp[j][i+1], dp[j^(1<<i)][i]);
				}
			}
		}
	}
	for(int i=1; i<=N; i++)
	{
		if(dp[B[i]][M].first.second!=i) printf("%d\n", M-dp[B[i]][M].first.first);
		else printf("%d\n", M-dp[B[i]][M].second.first);
	}
}

```