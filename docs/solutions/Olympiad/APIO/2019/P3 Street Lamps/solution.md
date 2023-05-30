---
title: APIO 19 P3 Street Lamps
tags:
    - ~ solution
---

# APIO 19 P3 Street Lamps

## 문제

### 문제 링크
[https://www.acmicpc.net/problem/17636](https://www.acmicpc.net/problem/17636)  
[https://oj.uz/problem/view/APIO19_street_lamps](https://oj.uz/problem/view/APIO19_street_lamps)

### 문제 요약
$1, 2, \cdots, N+1$번의 $N+1$개의 정류장이 있고, $i$번 정류장과 $i+1$번 정류장을 잇는 도로에는 가로등 $i$가 있다.  
$a$번 정류장에서 $b$번 정류장 $(1 \leq a < b \leq N+1)$로 이동할 수 있기 위해서는 두 정류장 사이의 모든 가로등들이 다 켜져 있어야 한다.  
시점 $0$에서의 초기 가로등들의 상태 $S$가 모두 주어지고, $1, 2, \cdots, Q$시간이 지날 때, 다음의 업데이트나 쿼리가 하나씩 주어진다.

+ $toggle \ i$ : $i$번 가로등을 toggle 한다.
+ $query \ a \ b$ : 시점 $0$에서 지금까지 $a$번 정류장에서 $b$번 정류장까지 이동할 수 있던 총 시간을 구하여라.

### 제한
+ $1 \leq N \leq 300,000$
+ $1 \leq Q \leq 300,000$

### 입력 / 출력
!!! Quote "Input"
    $N$ $Q$  
    $s_1 s_2 \cdots s_n$  
    ($Query \ 1$)  
    ($Query \ 2$)  
    $\vdots$  
    ($Query \ Q$)  
    ---
    + 시점 $0$에 $i$번째 가로등이 켜져 있으면 $s_i=1$, 꺼져 있으면 $s_i=0$
    + ($Query \ k$) : $toggle \ i$ or $query \ a \ b$

!!! Quote "Output"
    `answer for each Query`  
    $ans_i$

## 풀이

!!! note "Observation 1"    
    

!!! example "CheckPoint"
    

!!! tip "Complexity"
    <center>
    Time Complexity : $O()$
    </center>

## 코드
``` cpp linenums="1"

```
