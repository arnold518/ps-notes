---
title: JOISC 2023 P1.3 Passport
tags:
    - ~ solution
---

# JOISC 2023 P1.3 Passport

## 문제

### 문제 링크
[https://www.acmicpc.net/problem/27994](https://www.acmicpc.net/problem/27994)  
[https://oj.uz/problem/view/JOI23_passport](https://oj.uz/problem/view/JOI23_passport)

### 문제 요약
$1, 2, \cdots, N$번의 $N$개의 도시가 있고, 도시 $i$에서는 구간 $[L_i, R_i]$ 내의 임의의 도시로 자유롭게 이동할 수 있는 여권을 발급받을 수 있다. $(1 \leq i \leq N)$  
$Q$개의 쿼리가 주어질 때, 각 쿼리별로 $X_k$번 도시에서 출발하였을 때, 모든 도시를 방문하기 위하여 필요한 여권의 최소 개수를 구하여라. $(1 \leq k \leq Q)$

### 제한
+ $2 \leq N \leq 200,000$
+ $1 \leq L_i \leq i \leq R_i \leq N$ $(1 \leq i \leq N)$
+ $1 \leq Q \leq N$
+ $1 \leq X_k \leq N$ $(1 \leq k \leq Q)$, 모든 $X_k$는 서로 다르다.

### 입력 / 출력
!!! Quote "Input"
    $N$  
    $L_1$ $R_1$  
    $L_2$ $R_2$  
    $\vdots$  
    $L_N$ $R_N$  
    $Q$  
    $X_1$  
    $X_2$  
    $\vdots$  
    $X_Q$  

!!! Quote "Output"
    $ans_1$  
    $ans_2$  
    $\vdots$  
    $ans_Q$  

## 풀이

### Subtask 4
+ $N \leq 2500$

현재 갖고 있는 여권들만 사용해서 이동할 수 있는 도시의 범위는 항상 구간이다. $(\because L_i \leq i \leq R_i)$  
따라서, 방문 가능한 도시의 범위가 $[1, N]$임과, $L_i=1$인 여권과 $R_i=N$인 여권을 각각 발급받는것은 동치이다.

!!! note "Observation 1"    
    모든 도시를 방문하기 위하여 발급받아야 하는 여권의 최소 개수는 $X_k$번 도시에서 시작해서 $L_i=1$인 여권과 $R_i=N$인 여권을 각각 발급받기 위하여 발급받아야 하는 여권의 최소 개수와 동치이다.

여권을 발급받아 다음 장소로 이동하는 것을 그래프에서 간선을 따라 이동하는 것으로 생각하자.
$i$번 도시에서 여권을 받아 다음 여권 발금 장소이


!!! note "Observation 1"    
    

!!! example "CheckPoint"
    

!!! tip "Complexity"
    <center>
    Time Complexity : $O()$
    </center>

## 코드
``` cpp linenums="1"

```