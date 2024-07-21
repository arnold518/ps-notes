---
title: Biconnected Component
tags:
    - ~ algorithm
---

# Biconnected Component

## Definition

!!! definition "Definition 1"
    **Biconnected graph**는 2개 이상의 정점을 갖고 있으며, 1개의 정점을 제거하여도 연결되어 있는 무방향 그래프이다.  
    즉, 2개 이상의 정점을 갖고 있는 단절점이 없는 무방향 그래프이다.

!!! definition "Definition 2"
    **Biconnected component**는 maximal biconnected subgraph이다.  
    즉, 주어진 그래프의 biconnected subgraph 중, 포함되지 않은 어떤 정점 혹은 간선을 하나라도 추가하면 biconnected subgraph가 아니게 되는 subgraph를 의미한다.

일반적으로 그래프 $G(V, E)$의 subgraph는 정점 집합의 부분집합, 간선 집합의 부분집합으로 구성된 $G'(V', E')$ $(V' \subseteq V, E' \subseteq E)$을 의미하며, 특히 $E'$에 속하는 간선의 양 끝 정점들은 모두 $V'$에 속해 있어야 한다.
정의에 의해 $E'$에 속하는 어떤 간선의 양 끝점에도 포함되지 않는 정점들 또한 $V'$에 속할 수 있지만, biconnected subgraph는 연결되어 있어야 하니, $V'$은 모두 $E'$에 속하는 간선의 양 끝 정점들로 구성된 집합이다.
따라서 $V'$는 $E'$에 의하여 정의되고, 앞으로 biconnected component는 간선들의 집합이라고 생각한다.

## Equivalence Relation

같은 biconnected component에 포함되는 간선들의 성질을 확인하기 위하여 다음과 같은 equivalence relation을 정의한다.

!!! definition "Definition 3"
    간선 집합 $E$에 대하여, 다음과 같은 **equivalence relation** $\sim$을 정의하자.

    $e_1, e_2 \in E$ 일 때, $e_1 \sim e_2$일 필요충분조건은 "$e_1=e_2$이거나, $e_1$과 $e_2$를 동시에 포함하는 단순 사이클이 존재한다."이다.

!!! proof
    **Definition 3**의 relation $\sim$이 equivalence relation임을 증명하자.

    1. (Reflexivity) 정의에 의해 $e \sim e$가 성립한다.
    2. (Symmetricity) $e_1 \sim e_2$라면, $e_2 \sim e_1$ 또한 자명하게 성립한다.
    3. (Transitiviy) 서로 다른 $e_1, e_2, e_3 \in E$에 대하여 $e_1 \sim e_2$, $e_2 \sim e_3$라면, $e_1 \sim e_3$가 성립함을 보이자.  
      즉, $e_1$, $e_2$를 동시에 포함하는 단순 사이클 $C_1$가 존재하고, $e_2$, $e_3$를 동시에 포함하는 단순 사이클 $C_2$가 존재할 때, $e_1$과 $e_3$를 포함하는 단순 사이클 $C$가 존재함을 보이면 된다.  
      만약 $C_1$에 $e_3$가 포함된다면, $C=C_1$에 $e_1$, $e_2$, $e_3$가 모두 존재하니 성립한다.
      포함되지 않는 경우, 아래 그림처럼 $C_1$에 속하는 정점들을 일렬로 나열하면, 수열 상의 어떤 정점 $u$, $v$를 끝 정점으로 하며 $e_3$를 포함하는, $C_1$과는 간선을 공유하지 않는 경로가 존재한다.
      이제, $C_1$과 $P$의 간선들만을 이용하여 $e_1$, $e_3$의 간선을 모두 포함하는 단순 사이클 $C$를 생성할 수 있다.

이제, **Definition 2**로 정의된 biconnected component와 **Definition 3**의 equivalence relation에서 정의된 equivalence class가 사실 같음을 보인다.

!!! property "Property 1"
    **Definition 2**로 정의된 biconnected component들로 쪼개진 간선 집합들과, **Definition 3**의 equivalence relation에서 정의된 equivalence class로 쪼개진 간선 집합들은 같다.

    모든 간선 $e$에 대하여, $E_1$을 $e$를 포함하는 equivalence class, $E_2$를 $e$를 포함하는 biconnected component라 하면 $E_1 = E_2$이다.

!!! proof
    (equivalence class $\Rightarrow$ biconnected component)  
    Equivalence class $E_1$에 단절점 $v$가 존재한다고 가정하자.
    $v$를 제거하였을 때 2개 이상의 컴포넌트로 쪼개지는데, 이 때 $v$와 인접한 정점들 중 서로 다른 컴포넌트에 속하게 되는 정점을 2개 잡아 $a$, $b$라 하자.
    간선 $(v, a)$, $(v, b)$를 동시에 포함하는 단순 사이클이 존재한다면, $v$를 제거하였을 때 $a$와 $b$가 같은 컴포넌트에 속해야 한다.
    모순이 발생하였으니, $E_1$에는 단절점이 존재하지 않고, 따라서 이는 biconnected component이다. $(E_1 \subseteq E_2)$

    (equivalence class $\Leftarrow$ biconnected component)  
    **Menger's theorem**에 의하면 biconnected component (2-vertex connected subgraph)의 인접하지 않은 임의의 두 정점 $x$, $y$에 대하여, $x$와 $y$를 연결하는 2개의 internally disjoint path가 존재한다.  
    Biconnected component $E_2$의 임의의 두 간선 $e_1$, $e_2$에 대하여, 각각 $x$, $y$를 사이에 삽입하여 쪼갠 새로운 그래프를 생각하자.
    이 그래프 또한 단절점이 존재하지 않으니 biconnected component이고, menger's theorem에 따라 $x$와 $y$를 연결하는 2개의 internally disjoint path가 존재한다.
    이 두 path를 합하고, $x$와 $y$에 인접한 간선들을 제거한 후 $e_1$, $e_2$를 추가하면 $e_1$과 $e_2$를 동시에 포함하는 단순 사이클을 생성할 수 있다.
    따라서, $E_2$는 equivalence relation의 조건을 만족한다. $(E_2 \subseteq E_1)$

**Property 1**에 의하여, biconnected component를 정의할 때, maximal biconnected subgraph로 정의하기보다는 위와 같이 정의된 equivalence class로 정의하는 것이 편리할 때가 많다.

## Property

!!! property "Property 2"
    Biconnected graph에는 단절점이 존재하지 않는다.

    Biconnected graph에는 단절선이 존재하지 않는다.  
    단, 정점이 2개인 연결된 그래프는 예외이다.

!!! proof
    Biconnected graph에 단절점이 없음은 정의에 의해 자명하다.

    Biconnected graph에 단절선 $(u, v)$가 있다고 가정하자.
    정점의 개수가 3개 이상이라면, $u$, $v$중 적어도 한 정점 ($u$라 하자.)은 다른 정점 $w$와 연결되어 있다.
    $u$를 제거하면 $v$와 $w$는 연결이 끊기니 $u$는 단절점이다.
    모순이 발생하고, 따라서 정점의 개수가 3 이상이라면 단절선이 존재하지 않는다.    

!!! property "Property 3"
    같은 biconnected component에 포함되는 두 정점 $v_1, v_2 \in V$를 동시에 포함하는 단순 사이클이 존재한다.  
    단, 정점이 2개인 연결된 그래프는 예외이다.
    
    같은 biconnected component에 포함되는 두 간선 $e_1, e_2 \in E$를 동시에 포함하는 단순 사이클이 존재한다.  
    단, 정점이 2개인 연결된 그래프는 예외이다.

!!! proof
    만약 $v_1$, $v_2$를 연결하는 간선이 존재하지 않는다면, **menger's theorem**에 의해 $v_1$, $v_2$를 연결하는 2개의 internally disjoint path가 존재하고, 이 자체가 $v_1$, $v_2$를 포함하는 단순 사이클이다.
    만약 $v_1$, $v_2$를 연결하는 간선 $e$가 존재한다면, $e$는 단절선이 아니니, $e$를 제거했을 때 $v_1$, $v_2$를 연결하는 경로가 존재하고, 이 경로와 $e$를 합치면 $v_1$, $v_2$를 포함하는 단순 사이클이다.

    두 간선 $e_1, e_2 \in E$를 동시에 포함하는 단순 사이클이 존재함은 **Property 1**에 의하여 성립한다.

---

!!! property "Property 4"
    원래 그래프에서 단절점이 아닌 정점 $v$가 존재한다 하자.  
    $v$에 인접한 간선들 $e_1, e_2, \cdots$는 모두 같은 biconnected component에 포함된다.  

!!! proof
    $v$와 인접한 두 간선 $e_i (v, u_i)$, $e_j (v, u_j)$에 대하여 생각하자.
    $v$가 단절점이 아니니, $v$를 제거했을 때 $u_i$, $u_j$를 연결하는 경로가 존재하고, 이 경로에 $e_i$와 $e_j$를 합치면 $e_i$, $e_j$를 포함하는 단순 사이클을 만들 수 있다.
    $e_i$와 $e_j$를 동시에 포함하는 단순 사이클이 존재하니, $e_i$와 $e_j$는 같은 biconnected component에 포함된다.

!!! property "Property 5"
    원래 그래프에서 단절점 $v$가 존재한다 하자.  
    $v$에 인접한 정점들을 $v$를 삭제했을 때 같은 컴포넌트에 속하는 정점들끼리 묶어, $i$번째 컴포넌트에 속하는 정점들을 $u_{i, 1}, u_{i, 2}, \cdots$라 하고, $v$와 $u_{i, j}$를 연결하는 간선을 $e_{i, j}$라 하자.  
    같은 컴포넌트에 속하는 정점과 연결된 간선들은 모두 같은 biconnected component에 포함되고, 다른 컴포넌트에 속하는 정점과 연결된 간선들은 모두 다른 biconnected component에 포함된다.

!!! proof
    같은 $i$번째 컴포넌트에 속하는 두 간선 $e_{i, p}$, $e_{i, q}$는 **Property 4**와 같은 논리로 같은 biconnected component에 포함된다.

    다른 $i$, $j$번째 컴포넌트에 속하는 두 간선 $e_{i, p}$, $e_{j, q}$가 같은 biconnected component에 속한다면, 이를 동시에 포함하는 사이클이 존재해야 하는데, 이는 $v$를 제거했을 때 $u_{i, p}$와 $u_{j, q}$가 다른 컴포넌트에 포함됨에 모순이다.
    따라서 $e_{i, p}$, $e_{j, q}$는 다른 biconnected component에 포함된다.

