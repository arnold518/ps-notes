---
title: Tree Optimization 2 (with HLD)
tags:
    - dp
    - dp_tree
    - hld
    - trees
    - ~idea
---

# Tree Optimization 2 (with HLD)

많은 Tree DP 문제들의 경우, 트리의 각 정점 $u$에 대해 $dp[u][i]$ $(0 \le i \le sz(u))$와 같이 서브트리의 크기에 해당하는 dp 테이블을 관리해야 한다.
이 때, 정점 $A$와 $B$를 합쳐 새로운 dp 테이블의 정보를 구할 때 드는 시간복잡도 ($sz(A) \cdot sz(B)$, $min(sz(A), sz(B))$, ...) 등에 따라 전체 시간복잡도가 달라지게 된다.
이와 같이 두 서브트리를 합칠 때의 다양한 시간복잡도에 대한 자세한 설명은 [Tree Optimization](../../Tree Optimization/idea/)에서 정리하였다.

$sz(A) \cdot sz(B)$의 시간복잡도에 두 서브트리를 합칠 때는, $O(N^2)$ 크기의 dp 테이블을 global하게 선언하여 관리할 수 있는데, HLD를 활용하여 더 작은 크기의 dp 테이블을 효율적으로 관리할 수 있는 방법에 대하여 다룬다.  
또한, $min(sz(A), sz(B))$의 시간복잡도에 두 서브트리를 합칠 때는, 재귀적으로 자료구조를 주고받지 않고, 하나의 global한 자료구조를 관리하여 문제를 해결할 수 있는 방법에 대하여 다룬다.

## Algorithm 1

$A, B$를 합치기 위해서 $sz(A) \cdot sz(B)$의 시간이 필요할 때, 전체 시간복잡도 $O(N^2)$에 합칠 수 있다.
이 때, $O(N^2)$ 크기의 dp 테이블을 global하게 선언하여 관리하지 말고, HLD를 이용하여 다음과 같이 무조건 heavy edge를 우선적으로 타고 내려가며 dfs를 돌며 답을 계산하자.

!!! algorithm "Algorithm 1"
    Dfs를 하며 순서대로 