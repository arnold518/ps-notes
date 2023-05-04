---
title: JOISC 2023 P1.1 Two Currencies
tags:
    - ~ solution
---

# JOISC 2023 P1.1 Two Currencies

## 문제

### 문제 링크
[https://www.acmicpc.net/problem/27992](https://www.acmicpc.net/problem/27992)  
[https://oj.uz/problem/view/JOI23_currencies](https://oj.uz/problem/view/JOI23_currencies)

### 문제 요약
정점 $N$개의 트리가 주어지고, 몇 개의 간선은 지나려면 통행료를 내야 한다.  
$P_i$번째 간선을 통과하기 위해서는 $1$개의 금화를 내거나, $C_i$개의 은화를 내야 한다. $(1 \leq i \leq M)$  
$Q$개의 쿼리가 주어지며, $i$번 쿼리에서는 $S_i$번 정점에서 $T_i$번 정점으로 금화 $X_i$개, 은화 $Y_i$개를 갖고 이동하려 한다. $(1 \leq i \leq Q)$  
이 때, 이동이 가능한지 판별하고, 가능하다면 남는 금화의 개수의 최댓값을 구하여라.

### 제한
+ $2 \leq N \leq 100,000$
+ $1 \leq M \leq 100,000$
+ $1 \leq Q \leq 100,000$
+ $1 \leq A_i, B_i \leq N$ $(1 \leq i \leq N-1)$
+ $1 \leq P_j \leq N-1$, $1 \leq C_j \leq 10^9$ $(1 \leq j \leq M)$
+ $1 \leq S_k, T_k \leq N$, $0 \leq X_k \leq 10^9$, $0 \leq Y_k \leq 10^{18}$ $(1 \leq i \leq Q)$

### 입력 / 출력
!!! Quote "Input"
    $N$ $M$ $Q$  
    $A_1$ $B_1$  
    $A_2$ $B_2$  
    $\vdots$  
    $A_{N-1}$ $B_{N-1}$  
    $P_1$ $C_1$  
    $P_2$ $C_2$  
    $\vdots$  
    $P_M$ $C_M$  
    $S_1$ $T_1$ $X_1$ $Y_1$   
    $S_2$ $T_2$ $X_2$ $Y_2$  
    $\vdots$  
    $S_Q$ $T_Q$ $X_Q$ $Y_Q$  
    ---
    + $A_i$, $B_i$는 트리의 인접 리스트
    + $P_i$는 간선 번호

!!! Quote "Output"
    $ans_1$  
    $ans_2$  
    $\vdots$  
    $ans_Q$
    ---
    + $ans_i$는 $i$번째 쿼리에 대하여 불가능하면 $-1$, 가능하다면 남는 금화의 개수의 최댓값

## 풀이

### Subtask 1
+ $N \leq 2000$, $M \leq 2000$, $Q \leq 2000$

한 쿼리에서 이동하는 경로에 있는 모든 통행료들을 모아서 생각하자.
통행료들의 배열 $C_i$는 금화 $1$개를 내거나, 은화 $C_i$개를 내야 함을 의미한다.
사용할 수 있는 은화의 총 개수가 정해진 상태에서, 금화를 최대한 적게 사용하는 것이 목적이니, $C_i$가 작은 통행료부터 예산이 바닥날 때까지 은화로 지불하고, 나머지를 금화로 지불하는 것이 최선이다.

!!! note "Observation 1"
    한 쿼리 $k$에서 경로에 있는 모든 통행료들을 $C_i$의 순서대로 정렬한 후, $C_i$가 작은 통행료부터 순서대로 합이 $Y_k$이하일 때까지 최대한 더하고 남은 통행료들을 금화로 지불하는 것이 최적해이다.

**Observation 1**을 이용하여 Naive하게 각 쿼리마다 경로를 따라 모든 통행료들의 배열을 얻고, 정렬하여 답을 계산하면 $O(Q(N+M))$에 문제를 해결할 수 있다.

!!! example "CheckPoint"
    **Observation 1**을 이용하여 Naive하게 구현하면 $O(Q(N+M))$에 문제를 해결할 수 있다.

!!! tip "Complexity"
    <center>
    Time Complexity : $O(Q(N+M))$
    </center>

### Subtask 4 (Full)

$N$, $Q$, $M$이 클 때에는 직접 $C_i$들을 정렬하여 답을 구할 수 없다.

!!! note "Observation 1"    
    

!!! example "CheckPoint"
    

!!! tip "Complexity"
    <center>
    Time Complexity : $O()$
    </center>

## 코드
``` cpp linenums="1"

```