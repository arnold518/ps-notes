---
title: BOJ 28304 다섯 용사의 검
tags:
    - ~ solution
---

# BOJ 28304 다섯 용사의 검

## Problem

### Problem Link
[https://www.acmicpc.net/problem/28304](https://www.acmicpc.net/problem/28304)

### Summary
서로 다른 수들로 구성된 $5$개의 수열 $A_1, A_2, A_3, A_4, A_5$이 주어진다.
우리는 모르게 $5$개의 수열 각각에서 하나의 수 $B_i$가 선택되어 있고, 우리는 그 중에 가장 큰 수가 몇 번째 수열에 포함되어 있는지를 알아맞춰야 한다.
우리가 할 수 있는 질문은 특정 숫자 $X$에 대하여 $B_1, B_2, B_3, B_4, B_5$가 각각 $X$보다 큰지, 작거나 같은지를 알 수 있다.
$B_i$가 어떻게 선택되어 있는지에 무관하게 답을 맞출 수 있는 질문의 최소 횟수를 구하여라.

### Constraints
- $N=|A_1|+|A_2|+|A_3|+|A_4|+|A_5| \le 50, 000$
- $1 \le A_{i, j} \le 10^9$

## Solution

임의의 $X$에 대하여 질문을 했다고 가정하고, 이 질문을 통해 얻을 수 있는 정보가 무엇인지 생각하자.

만약 $X$보다 큰 수가 하나라도 존재하면, $X$보다 작거나 같은 수들은 모두 답의 후보에서 제거된다.
또한, 남은 수들이 $X$보다 크거나 같다는 정보도 알 수 있다.
만약 모든 수들이 $X$보다 작거나 같다면, 남은 모든 수들이 $X$ 이하라는 정보를 알 수 있다.

따라서, 질문들을 하는 과정에서 얻는 정보는 다음과 같이 요약할 수 있다.  
현재 답의 후보는 $mask$이며, $mask$의 수들은 $L$ 이상 $R$이하이고, $mask$에 포함되지 않는 수들은 모두 $L$ 미만이다.

!!! observation "Observation 1"    
    질문을 통해 임의의 시점에서 얻을 수 있는 정보는 다음과 같다.  
    현재 답의 후보는 $mask$이며, $mask$의 수들은 $L$ 이상 $R$이하이고, $mask$에 포함되지 않는 수들은 모두 $L$ 미만이다.

따라서, $mask$, $L$, $R$을 인자로 하는 dp를 생각하면 전체 상태의 개수가 $O(2^5N^2)$개가 되고, 각 상태마다 $N$개의 질문을 할 수 있으니 전체 시간복잡도는 $O(2^5N^3)$이 된다.

!!! definition "Definition 1"
    $dp[mask][L][R]=$현재 답의 후보는 $mask$이며, $mask$의 수들은 $L$ 이상 $R$이하라는 사실을 알 때 답을 맞추기 위한 최소 질문 횟수  

!!! checkpoint "CheckPoint"
    **Definition 1**과 같이 dp를 구성하면 상태의 개수 $O(2^5N^2)$, 질문의 개수 $O(N)$으로 $O(2^5N^3)$에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    Time Complexity : $O(2^5N^3)$

---

답의 상한을 생각하기 위하여, $X$에 대한 이분탐색을 실시하면 $X$보다 큰 것이 존재하면 증가시키고, 모든 수가 $X$보다 작으면 감소시켜 $O(logN)$번의 질문으로 답을 구할 수 있다.

!!! observation "Observation 2"    
    답의 상한은 $O(logN)$이다.

dp의 상태는 많지만 값으로 가능한 범위는 작으니, 인자와 값을 교환하여 시간복잡도를 줄이자.

!!! definition "Definition 2"
    $dp[mask][L][k]=$현재 답의 후보는 $mask$이며, $mask$의 수들은 $L$ 이상 $R$이하라는 사실을 알 때 답을 $k$번의 질문 이내로 맞출 수 있기 위하여 가능한 최대 $R$  

과 같이 정의하면 상태의 개수를 $O(2^5NlogN)$까지 줄일 수 있다.  



!!! checkpoint "CheckPoint"
    

!!! complexity "Complexity"
    Time Complexity : $O()$

## Code
``` cpp linenums="1"

```