---
title: Kőnig's theorem
tags:
    - bipartite_matching
    - graphs
    - ~ algorithm
---

# Kőnig's theorem

## Definition

!!! definition "Definition 1"
    **Graph** $G=(V, E)$에서 **matching**은 간선의 부분집합 $E' \subseteq E$로, 모든 선택된 간선들은 서로 정점을 공유하지 않는다.

    **Maximum matching**은 최대 크기의 **matching**이다.

!!! definition "Definition 2"
    **Graph** $G=(V, E)$에서 **vertex cover**은 정점의 부분집합 $V' \subseteq V$로, 모든 간선이 적어도 하나의 선택된 정점과 연결되어 있어야 한다.

    **Minimum vertex cover**은 최소 크기의 **vertex cover**이다.

$\phi \subseteq E$도 유효한 matching이고, $V \subseteq V$도 유효한 vertex cover이니, minimum matching이나 maximum vertex cover을 구하는 것은 의미가 없음에 유의하자.

## Kőnig's theorem

!!! property "Property 1"
    **Bipartite graph** $G=(A \cup B, E)$에서 **maximum matching**의 간선의 개수와 **minimum vertex cover**의 정점의 개수는 일치한다.

## Proof

임의의 vertex cover의 크기는 임의의 matching의 크기보다 크거나 같다.
임의의 matching을 잡았을 때, 이 그래프에서 임의의 vertex cover은 matching에 포함되는 각 간선에 대하여 연결하는 두 정점 중 적어도 하나는 선택해야 하기 때문이다.

!!! property "Property 2"
    임의의 vertex cover의 크기는 임의의 matching의 크기보다 크거나 같다.

    $\forall$ $|$**matching**$|$ $\le$ $\forall$ $|$**vertex cover**$|$

!!! proof
    임의의 matching을 잡았을 때, 이 그래프에서 임의의 vertex cover은 matching에 포함되는 각 간선에 대하여 연결하는 두 정점 중 적어도 하나는 선택해야 하기 때문이다.

Bipartite graph $G=(A \cup B, E)$에서 이분매칭을 구하기 위하여 다음과 같은 flow network를 정의하자.

- Source $s$에서 $A$의 모든 정점으로 가는 capacity $1$의 간선이 있다.
- $B$의 모든 정점에서 sink $t$로 가는 capacity $1$의 간선이 있다.
- $A$와 $B$ 사이에는 $E$의 각 간선 $(a, b)$에 대하여 capcity $\infty$의 간선이 있다.

위 flow network에서 maximum flow를 구하면 선택되는 간선들은 $A$의 각 정점이 최대 한번, $B$의 각 정점이 최대 한번 등장하니 maximum matching이다.

여기서 **max flow min cut theorem**을 사용하면 maximum flow를 구한 후 residual flow network $G_f$에서 source $s$에서 도달 가능한 정점들을 집합 $S$($s \in S$), 도달 불가능한 정점들을 집합 $T$($t \in T$)로 나누면 $(S, T)$는 minimum cut이다.

또한, 임의의 minimum cut $(S, T)$에 대해 $A$에서 $S$에 속하는 정점들의 집합을 $A_S$, $T$에 속하는 정점들의 집합을 $A_T$, $B$에서 $S$에 속하는 정점들의 집합을 $B_S$, $T$에 속하는 정점들의 집합을 $B_T$로 표현하자.
정의에 의해 $|A_T|+|B_S|$가 minimum cut의 크기이다.

$$A_S = S \cap A, A_T = T \cap A, B_S = B \cap S, B_T = B \cap T$$

!!! definition "Definition 3"
    Bipartite graph $G=(A \cup B, E)$에서 이분매칭을 구하기 위하여 다음과 같은 flow network를 정의하자.

    - Source $s$에서 $A$의 모든 정점으로 가는 capacity $1$의 간선이 있다.
    - $B$의 모든 정점에서 sink $t$로 가는 capacity $1$의 간선이 있다.
    - $A$와 $B$ 사이에는 $E$의 각 간선 $(a, b)$에 대하여 capcity $\infty$의 간선이 있다.
    
    위 flow network의 임의의 minimum cut $(S, T)$에 대해 $A$에서 $S$에 속하는 정점들의 집합을 $A_S$, $T$에 속하는 정점들의 집합을 $A_T$, $B$에서 $S$에 속하는 정점들의 집합을 $B_S$, $T$에 속하는 정점들의 집합을 $B_T$로 표현하자.

    $$A_S = S \cap A, A_T = T \cap A, B_S = B \cap S, B_T = B \cap T$$

!!! property "Property 3"
    Bipartite graph $G=(A \cup B, E)$에서 maximum matching의 크기는 **Definition 1**과 같이 정의된 flow network에서의 maximum flow의 값과 같다.
    **max flow min cut theorem**에 의해 이는 같은 flow network에서의 mininum cut의 크기와 같으며, 이는 $|A_T|+|B_S|$이다.

![image 1](./1.svg){: .center}

$A_S$와 $B_T$ 사이에는 간선이 없음을 확인할 수 있다.
만약 간선이 존재한다면 capcity가 $\infty$이니 cut의 크기도 $\infty$가 된다.

!!! property "Property 4"
    $A_S$와 $B_T$ 사이에는 간선이 없다.
    모든 간선들은 $(A_S, B_S)$, $(A_T, B_S)$, $(A_T, B_T)$ 사이에만 존재한다.

!!! proof
    만약 $A_S$와 $B_T$ 사이에 간선이 존재한다면 capcity가 $\infty$이니 cut의 크기도 $\infty$가 된다.
    이는 $(S, T)$가 임의의 minimum cut임에 모순이다.

위 **Property 4**로부터 $A_T \cup B_S$는 vertex cover임을 알 수 있다.
만약 $A_T \cup B_S$의 정점들과 인접하지 않은 간선이 있다면 이 간선은 $A_S$와 $B_T$를 연결하는 간선이어야 하는데, **Property 4**에 의하여 이러한 간선은 존재할 수 없다.

!!! property "Property 5"
    $A_T \cup B_S$는 vertex cover이다.

!!! proof
    $A_T \cup B_S$가 vertex cover가 아니라고 가정하면, $A_T \cup B_S$의 정점들과 인접하지 않은 간선이 있어야 한다.
    그렇다면 이 간선은 $A_S$와 $B_T$를 연결하는 간선이어야 하는데, **Property 4**에 의하여 이러한 간선은 존재할 수 없다.

위 사실들을 종합하면, **Property 3**에 의해 maximum matching의 크기는 $|A_T|+|B_S|$와 같고, **Property 5**에 의해 실제 $|A_T|+|B_S|$의 크기의 vertex cover $A_T \cup B_S$이 존재한다.
**Property 2**에 의해 임의의 vertex cover의 크기는 임의의 matching의 크기보다 크거나 같은데, maximum matching의 크기와 같은 vertex cover $A_T \cup B_S$을 찾았으니, 이것이 minimum vertex cover이고, maximum matching의 크기는 minimum vertex cover의 크기와 같다는 결론을 얻을 수 있다.

또한, 실제 minimum vertex cover의 집합을 구하기 위해서는 maximum flow를 먼저 구해, minimum cut $S$, $T$를 실제로 구한 후, $A_T \cup B_S$를 구하면 된다는 것도 알 수 있다.

## Reference

- [https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_%28graph_theory%29](https://en.wikipedia.org/wiki/K%C5%91nig%27s_theorem_%28graph_theory%29)
- [https://codeforces.com/blog/entry/105697](https://codeforces.com/blog/entry/105697)