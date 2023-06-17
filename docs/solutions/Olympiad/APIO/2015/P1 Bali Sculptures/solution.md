---
title: APIO 15 P1 Bali Sculptures
tags:
    - dp
    - greedy
    - ~ solution
---

# APIO 15 P1 Bali Sculptures

## Problem

### Problem Link
[https://www.acmicpc.net/problem/10846](https://www.acmicpc.net/problem/10846)  
[https://oj.uz/problem/view/APIO15_sculpture](https://oj.uz/problem/view/APIO15_sculpture)

### Summary
길이 $N$의 수열 $Y$가 주어질 때, 이 수열을 $X$ $(A \leq X \leq B)$개의 구간으로 쪼개어 각 구간별 $Y_i$의 합들의 bitwise OR을 최소화하여라.

### Constraints
+ $1 \leq N \leq 2,000$  
+ $1 \leq A \leq B \leq N$  
+ $0 \leq Y_i \leq 10^9$  
  
**Subtask 4 : ** $1 \leq N \leq 100$, $1 \leq A \leq B \leq N$  
**Subtask 5 : ** $1 \leq N \leq 2,000$, $1 = A \leq B \leq N$

### Input / Output
!!! inout "Input"
    $N$ $A$ $B$  
    $Y_1$ $Y_2$ $\cdots$ $Y_N$

!!! inout "Output"
    $ans$

## Solution

**Subtask 4**와 **Subtask 5**가 서로를 포함하지 않는, 두 개의 문제로 구성되어 있음에 유의하자.  
**Subtask 4**의 경우, $1 \leq N \leq 100$이고, **Subtask 5**의 경우 $1 \leq N \leq 2,000$인 대신 $A=1$로, 가능한 구간의 개수를 최소화 시켜야 한다.

"$P[i]:=Y[i]$의 누적합 배열" 으로 정의한다.

### Subtask 4

+ $1 \leq N \leq 100$, $1 \leq A \leq B \leq N$

생각할 수 있는 가장 직관적인 풀이는 다음과 같다.

!!! failure "Wrong Solution"
    $dp[i][k]:=$$1 \sim i$까지의 수들을 $k$개의 구간으로 쪼갤 때 각 구간합들의 bitwise OR 값의 최솟값  
    $dp[i][k]=min_{j<i} (dp[j][k-1] \ | \ (P[i]-P[j]))$  
    위 정의와 점화식의 DP를 통해 $O(N^3)$에 답을 구한다.

하지만, 위 풀이는 올바른 답을 보장하지 않는다.  
DP가 최적해를 보장하기 위해서는 전체 문제를 최적으로 풀기 위해서 부분문제 또한 최적으로 풀어야 한다는 **최적 부분 구조**가 성립해야 한다.
만약 작은 부분문제에서 가능한 답이 `10(2)`와 `01(2)`였고, 큰 전체문제로 가기 위해서는 이 답에 `10(2)`를 추가해야 된다고 가정하자.
그렇다면 전체문제에서의 값은 각각 `10(2)`, `11(2)`가 되며, 전체 문제에서의 최적해는 `10(2)`이다.
하지만 부분문제에서의 최적해는 `01(2)`로, 이 최적해로 전체문제를 풀면 `11(2)`로, 최적해를 얻을 수 없다.
따라서 문제의 구조는 최적 부분 구조가 성립하지 않음을 알 수 있다.
특히, 많은 경우에 bitwise 연산을 할 때 최적 부분 구조가 성립하지 않는다.

---

문제의 답을 최고 비트부터 하나씩 결정해가는 풀이를 생각하자.  
최적해의 $T+1$이상의 비트를 다 결정했다고 가정하고 $T$번째 비트를 결정하기 위하여 다음의 DP를 생각하자.

!!! definition "Definition 1"
    $T$를 최상위 비트에서부터 감소시키며, 최적해의 $T+1$이상의 비트를 다 결정했다고 가정하고, $T$번째 비트가 $0$이 될 수 있는지 확인하자.  
    $dp[i][k]:=$$1 \sim i$까지의 수들을 $k$개의 구간으로 쪼갤 때 각 구간합들을 bitwise OR한 값들 중, $T+1$이상의 비트는 지금까지 구한 최적해와 똑같으며, $T$번째 비트는 $0$이 되도록 할 수 있는가? (`True` / `False`)

위와 같이 정의한 후, $dp[j][k-1] (j < i)$ 에서 DP값을 받아올 때, $P[i]-P[j]$ 구간합을 bitwise OR함으로 인해 지금까지 구한 최적해의 상위 비트에 문제가 발생하지 않는지 확인하고, $T$번째 비트가 0이 될 수 있는지를 확인하여 transition을 한다.

위 DP의 경우, 가능/불가능을 따지고 있기 때문에 최적 부분 구조에 대한 문제가 발생하지 않는다.
또한, 최상위 비트부터 아래쪽으로, 최적해의 비트를 결정해 나가고 있는 방식으로 문제를 해결하니, 최적해를 무조건 찾을 수 있다.
$T$번째 비트가 $0$이 될 수 있는지 확인하기 위해서는 $dp[N][A], dp[N][A+1], \cdots, dp[N][B]$ 중에 참인 것이 있는지 확인하면 된다.

$logX$개의 비트 각각을 $O(N^2)$개의 상태 하나를 $O(N)$번의 transition으로 문제를 해결하니, 전체 $O(N^3logX)$에 문제를 해결할 수 있다.

!!! checkpoint "CheckPoint"
    **Definition 1**과 같이 DP를 정의하면 최고 비트부터 하나씩 최적해를 결정할 수 있고, $O(N^3logX)$에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    <center>
    Time Complexity : $O(N^3logX)$
    </center>

### Subtask 5

+ $1 \leq N \leq 2,000$, $1 = A \leq B \leq N$

**Subtask 5**의 경우 가능한 구간의 개수를 최소화 시켜야 하는 대신 $N$의 크기가 늘어났다.
이제, $dp[i][k]$의 `True` / `False` DP 대신, $k$항을 DP값으로 변환하여 조건을 만족하기 위한 구간의 개수의 최솟값을 저장하자.

!!! definition "Definition 2"
    $T$를 최상위 비트에서부터 감소시키며, 최적해의 $T+1$이상의 비트를 다 결정했다고 가정하고, $T$번째 비트가 $0$이 될 수 있는지 확인하자.  
    $dp[i]:=$$1 \sim i$까지의 수들을 여러 구간으로 쪼갤 때 각 구간합들을 bitwise OR한 값들 중, $T+1$이상의 비트는 지금까지 구한 최적해와 똑같으며, $T$번째 비트는 $0$이 되도록 할 수 있는 구간의 최소 개수

transition은 **Subtask 4**의 경우와 거의 유사하다.
조건을 만족시키기 불가능하거나 필요한 구간의 개수가 $B$를 넘어가는 경우, $dp[i]$에 무한히 큰 값을 넣어 해결할 수 있다.
$T$번째 비트가 $0$이 될 수 있는지 확인하기 위해서는 $dp[N]$이 $B$보다 작거나 같은지 확인하면 된다.

!!! checkpoint "CheckPoint"
    구간의 개수를 최소화시키면 된다는 점을 이용하면 **Definition 2**와 같이 DP를 수정하면 최고 비트부터 하나씩 최적해를 결정할 수 있고, $O(N^2logX)$에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    <center>
    Time Complexity : $O(N^2logX)$
    </center>

## Code
``` cpp linenums="1"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 2000;

int N, A, B;
ll Y[MAXN+10], ans=0, dp1[MAXN+10], dp2[MAXN+10][MAXN+10];

int main()
{
    scanf("%d%d%d", &N, &A, &B);
    for(int i=1; i<=N; i++) scanf("%lld", &Y[i]), Y[i]+=Y[i-1];

    ans=(1ll<<46)-1;
    if(A==1)
    {
        for(int i=45; i>=0; i--)
        {
            ll now=1ll<<i;
            ans^=now;
            for(int j=1; j<=N; j++) dp1[j]=987654321; dp1[0]=0;
            for(int j=1; j<=N; j++) for(int k=0; k<j; k++) if((ans|(Y[j]-Y[k]))==ans) dp1[j]=min(dp1[j], dp1[k]+1);
            if(dp1[N]>B) ans|=now;
        }
    }
    else
    {
        for(int i=45; i>=0; i--)
        {
            ll now=1ll<<i;
            ans^=now;
            memset(dp2, 0, sizeof(dp2)); dp2[0][0]=1;
            for(int j=1; j<=N; j++) for(int k=1; k<=N; k++) for(int p=0; p<j; p++) if((ans|(Y[j]-Y[p]))==ans) dp2[j][k]|=dp2[p][k-1];
            bool flag=false;
            for(int j=A; j<=B; j++) flag|=dp2[N][j];
            if(!flag) ans|=now;
        }
    }
    printf("%lld", ans);
}
```
