---
title: Tree Optimization
tags:
    - dp
    - dp_tree
    - hld
    - segtree
    - smaller_to_larger
    - trees
    - ~idea
---

# Tree Optimization

많은 Tree DP 문제들의 경우, 각 노드에서 특정 시간복잡도로 노드들을 합치는 작업을 한다.  
일반성을 잃지 않고, 노드의 자식이 3개 이상이라면, 더미 노드를 부모 쪽으로 계속 만들어 주며, 모든 트리를 이진 트리 형태로 변형시킬 수 있다.
따라서, 이진 트리에서 자식 노드 두개의 값만을 합쳐주는 문제로 생각한다.  
아래 글에서 $A, B$는 왼쪽, 오른쪽 정점을 의미하며, $sz(A)$는 정점 $A$의 서브트리의 크기, $h(A)$는 정점 $A$의 서브트리의 높이로 정의한다.

<center>

|                             |    Time needed to merge $A$, $B$    | Time Complexity |
|:---------------------------:|:-----------------------------------:|:---------------:|
| [Property 1](./#property-1) |         $sz(A) \cdot sz(B)$         |     $O(N^2)$    |
| [Property 2](./#property-2) | $min(K, sz(A)) \cdot min(K, sz(B))$ |     $O(NK)$     |
| [Property 3](./#property-3) |         $min(sz(A), sz(B))$         |    $O(NlogN)$   |
| [Property 4](./#property-4) |          $min(h(A), h(B))$          |      $O(N)$     |
| [Property 5](./#property-5) |            $sz(A)+sz(B)$            |   $O(Nlog^2N)$  |

</center>

## Property 1

!!! property "Property 1"
    $A, B$를 합치기 위해서 $sz(A) \cdot sz(B)$의 시간이 필요할 때, 전체 시간복잡도 $O(N^2)$에 합칠 수 있다.
    **(KOI18 검은돌)**

!!! proof
    $sz(A) \cdot sz(B)$의 값은 왼쪽 자식의 서브트리의 모든 노드와 오른쪽 자식의 모든 서브트리의 노드를 연결했을 때 간선의 수와 같다.
    이 때 어떠한 두 정점 $u$, $v$가 합쳐지는 위치는 바로 그 노드의 LCA $w$에서 합쳐지게 된다.
    즉, 전체 각 노드별 $sz(A) \cdot sz(B)$의 합은 트리에서 임의의 두 노드를 선택하는 경우의 수와 같으니 $O(N^2)$이다.

트리의 각 정점 $u$에 대해 $dp[u][i]$ $(0 \le i \le sz(u))$와 같이 서브트리의 크기에 해당하는 dp 테이블을 관리해야 하고, dp의 전이가 $(max, +)$ convolution과 같이 $sz(A) \cdot sz(B)$의 시간이 걸리는 형태의 시간복잡도가 $O(N^2)$임을 알려준다.

## Property 2

!!! property "Property 2"
    $A$, $B$를 합치기 위해서 $min(K, sz(A)) \cdot min(K, sz(B))$의 시간이 필요할 때, 전체 시간복잡도 $O(NK)$에 합칠 수 있다.

!!! proof
    **Property 1**과 같은 논리로 두 노드 $u$, $v$가 합쳐지는 LCA $w$를 생각하자.
    $min(K, sz(A))$으로 인해 왼쪽 서브트리에서는 dfs ordering 순으로 큰 순서대로 $K$개, $min(K, sz(B))$으로 인해 오른쪽 서브트리에서는 dfs ordering 순으로 작은 순서대로 $K$개를 선택해 이어주는 경우의 수와 같다.
    이는 전체 정점들을 dfs ordering 순으로 나열한 후 거리가 $2K$이하인 두 정점의 경우의 수와 같으니 $O(NK)$이다.

**Property 1**과 같은 상황인데, dp 테이블의 크기가 $K$로 제한이 걸려 있는 상황에서 시간복잡도가 $O(NK)$임을 알려준다.

## Property 3

!!! property "Property 3"
    $A$, $B$를 합치기 위해서 $min(sz(A), sz(B))$의 시간이 필요할 때, 전체 시간복잡도 $O(NlogN)$에 합칠 수 있다.
    **(Small to Large)**

!!! proof
    집합에서 더 크기가 작은 집합을 큰 집합쪽에 합쳐주는 과정을 반복할 때 어떤 원소 $u$가 다른 집합으로 옮겨가기 위해서는 집합의 크기가 2배 이상으로 커져야 한다.
    즉, 모든 원소가 새로운 집합으로 옮겨가는 횟수가 $O(logN)$이니, 전체 시간복잡도는 $O(NlogN)$이다.

**Property 1**과 같은 상황인데, dp의 전이가 특수한 형태여서 $min(sz(A), sz(B))$의 시간이 필요하다면 시간복잡도가 $O(NlogN)$임을 알려준다.
예를 들어, 각 정점에서 크기 $sz(A)$의 자료구조를 관리해야 하며, 두 정점을 합칠 때 작은 자료구조의 모든 원소를 큰 자료구조에 넣어줄 수 있다면 이를 적용할 수 있다.

## Property 4

!!! property "Property 4"
    $A$, $B$를 합치기 위해서 $min(h(A), h(B))$의 시간이 필요할 때, 전체 시간복잡도 $O(N)$에 합칠 수 있다.
    **(Small to Large in Height)**

!!! proof
    $A$와 $B$의 서브트리에서 루트부터 시작하는 가장 길이가 긴 경로, 즉 길이 $h(A), h(B)$의 경로의 정점들을 색칠하자.
    일반성을 잃지 않고 $h(A) \le h(B)$라 한다면 $A$와 $B$를 합칠 때 $A$에서 색칠된 정점의 수만큼 시간을 소모한다.
    그리고 합친 후에는 $B$의 정점들만 색이 남고 $A$의 색칠된 정점들은 더 이상 가장 긴 경로가 아니기 때문에 색이 없어진다.
    즉, $A$의 색칠된 정점들은 정확히 $1$번 시간복잡도에 영향을 준 후 색이 없어진다.
    따라서, 각 정점은 시간복잡도에 최대 $1$번 영향을 미칠 수 있고, 전체 시간복잡도는 $O(N)$이다.

## Property 5

!!! property "Property 5"
    $A$, $B$를 합치기 위해서 $sz(A)+sz(B)$의 시간이 필요할 때, 전체 시간복잡도 $O(Nlog^2N)$에 합칠 수 있다.
    **(JOIOC18 Cats or Dogs)**

    트리에서 HLD를 하여, 모든 간선을 heavy edge와 light edge로 구분한다.
    그 후, heavy edge로 구성된 chain에 대한 segment tree를 구성한다.
    이제, 전체 문제를 풀기 위해서는 루트를 포함하는 체인에서 각 노드마다 heavy edge를 제외한 light edge로 쪼개지는 서브트리에 대해서 재귀적으로 먼저 문제를 해결한다.
    이제, 이 체인에 대한 문제는 다음 과정으로 해결한다.

    1. 각 노드의 light edge의 값들을 Divide & Conquer을 이용하여 합쳐준다.
    2. Light edge들이 모두 합쳐진 각 노드에 대하여 체인의 값들을 segment tree와 같이 Divide & Conquer을 이용하여 합쳐준다.

!!! proof
    트리의 한 정점 $u$의 입장에서 루트까지 올라가며 시간복잡도를 계산하자.  
    HLD의 논리에 의해 $u$가 루트까지 올라갈 때 통과하는 light edge의 수는 $O(logN)$개이다.
    Light edge를 한번 타고 올라갈 때마다 Divide & Conquer으로 값들이 한 노드로 합쳐지고, 이후 체인의 값들 또한 Divide & Conquer으로 합쳐진다.
    이렇게 light edge를 한번 통과하고 heavy chain들의 값을 하나로 합치는데 Divide & Conquer에서 정점당 $O(logN)$의 시간이 걸리니, 정점 하나당 전체 $O(log^2N)$의 시간이 걸린다.
    따라서, 전체 시간복잡도는 $O(Nlog^2N)$이다.
    
위 내용을 응용하여, tree dp문제에서 update를 해야 할 때, 각 업데이트를 $O(log^2N)$에 해결할 수 있다.
각 chain을 합치는 과정을 segment tree에 저장하여 persistent 하게 Divide & Conquer을 관리할 수 있다면, 같은 논리로 한 정점이 루트까지 올라가며 자료구조를 업데이트하는 시간이 $O(log^2N)$이다.
