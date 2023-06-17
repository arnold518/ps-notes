---
title: APIO 19 P1 Strange Device
tags:
    - math
    - number theory
    - ~ solution
---

# APIO 19 P1 Strange Device

## Problem

### Problem Link
[https://www.acmicpc.net/problem/17634](https://www.acmicpc.net/problem/17634)  
[https://oj.uz/problem/view/APIO19_strange_device](https://oj.uz/problem/view/APIO19_strange_device)

### Summary
$x=(t+\lfloor{\frac{t}{B}}\rfloor) \ (mod \ A)$, $y=t \ (mod \ B)$ 일 때, $t$에 대한 순서쌍 $(x, y)$를 생각하자.  
$t$의 구간들 $[l_i, r_i]$이 $N$개 주어질 때, 적어도 하나의 구간에 포함되는 모든 $t$들에 대하여 가능한 서로 다른 순서쌍 $(x, y)$의 개수를 구하여라.

### Constraints
+ $N \leq 10^6$  
+ $1 \leq A, B \leq 10^{18}$  
+ $0 \leq l_i \leq r_i \leq 10^{18}$, $r_i < l_{i+1}$

### Input / Output
!!! inout "Input"
    $N$ $A$ $B$  
    $l_1$ $r_1$  
	$l_2$ $r_2$  
	$\vdots$  
	$l_N$ $r_N$  


!!! inout "Output"
    $ans$

## Solution

우선, $y$의 주기가 $B$임에 착안하여 $t$가 $B$씩 증가함에 따라 순서쌍 $(x, y)$가 어떻게 변하는지 관찰하자.
$0 \leq k < B$에 대하여, $t=k, k+B, k+2B, \cdots, k+nB$일 때 $x$는 다음과 같이 변한다.

<center>

|    $t$   | $x\ (mod \ A)$ |
|:--------:|:--------------:|
|    $k$   |       $k$      |
|   $k+B$  |     $k+B+1$    |
|  $k+2B$  |    $k+2B+2$    |
| $\vdots$ |    $\vdots$    |
|  $k+nB$  |    $k+nB+n$    |

</center>

$t$가 $B$ 증가할 때마다 $x$는 $(mod \ A)$ 속에서 $B+1$씩 증가한다는 사실을 관찰할 수 있다.
주기를 구하기 위해 $x_k \equiv x_{k+nB} \ (mod \ A)$인 최소 $n$을 구하자.

$$
A \mid n(B+1) \ , \ n=\frac{A}{gcd(A, B+1)}
$$

위 결과를 통해 고정된 $y$에 대하여 주기가 $n=\frac{A}{gcd(A, B+1)}$이니, 가능한 $B$개의 모든 $y$에 대해서는 전체 $T=\frac{AB}{gcd(A, B+1)}$임을 알 수 있다.

!!! observation "Observation 1"
    $(x, y)$의 주기는 $T=\frac{AB}{gcd(A, B+1)}$이다.

이제 $(x, y)$ 대신, $t \ (mod \ T)$로 대체하여 생각해도 된다.
만약 어떤 구간의 길이가 $T$ 이상이면, 이 구간 하나만으로도 $0 \sim T-1$의 모든 수들을 다 포함하니, 답은 $T$이다.
모든 구간의 길이가 $T$ 미만이면, 각 구간은 $0 \sim T-1$의 수들을 원형으로 배열한 모양에서 하나의 구간으로 대응된다.
$0$을 기준으로 원형 구간들을 모두 쪼개고, 전체 구간들을 정렬한 후 sweeping을 통해 $O(NlogN)$에 합집합의 크기를 구할 수 있다.

!!! checkpoint "CheckPoint"
    **Observation 1**에서 $(x, y)$의 주기가 $T$이니 순서쌍 $(x, y)$ 대신 $t \ (mod \ T)$로 대체할 수 있다.  
	구간 $[l_i, r_i]$는 $0 \sim T-1$의 수들을 원형으로 배열한 모양에서 하나의 구간으로 대응시킬 수 있으니, $0$을 기준으로 원형 구간들을 선형 구간들로 쪼개고, 정렬한 후 sweeping을 통해 $O(NlogN)$에 합집합의 크기를 구할 수 있다.

마지막으로, $1 \leq A, B \leq 10^{18}$이니 $T=\frac{AB}{gcd(A, B+1)}$가 `long long` 자료형의 범위를 벗어날 수 있으므로, $min(T, 10^{18})$의 값을 사용하여 overflow를 방지할 수 있다.

!!! complexity "Complexity"
    <center>
    Time Complexity : $O(NlogN)$
    </center>

## Code
``` cpp linenums="1"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 1e6;
 
int N;
ll A, B, L;
pll P[MAXN+10];
 
map<ll, ll> M;
 
void addrange(ll l, ll r)
{
	M[l]++;
	M[r+1]--;
}
 
int main()
{
	scanf("%d%lld%lld", &N, &A, &B);
	for(int i=1; i<=N; i++) scanf("%lld%lld", &P[i].first, &P[i].second);
 
	L=__gcd(A, B+1);
 
	if(A/L>=(ll)1e18/B) L=1e18;
	else L=A/L*B;
 
	for(int i=1; i<=N; i++)
	{
		ll l=P[i].first, r=P[i].second;
		if(r-l+1>=L) return !printf("%lld\n", L);
		if(l%L<=r%L) addrange(l%L, r%L);
		else
		{
			addrange(l%L, L-1);
			addrange(0, r%L);
		}
	}
 
	M[L];
	ll t=0, ans=0;
	for(auto it=M.begin(); it!=M.end(); it++)
	{
		if(it->first==L) break;
		t+=it->second;
		if(t) ans+=next(it)->first-it->first;
	}
	printf("%lld\n", ans);
}
```
