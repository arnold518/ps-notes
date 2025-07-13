---
title: JOISC 2023 D1P1 Two Currencies
tags:
    - binary_search
    - data_structures
    - euler_tour_technique
    - lca
    - offline_queries
    - pbs
    - pst
    - segtree
    - trees
    - ~ solution
---

# JOISC 2023 D1P1 Two Currencies

## Problem

### Problem Link
[https://www.acmicpc.net/problem/27992](https://www.acmicpc.net/problem/27992)  
[https://oj.uz/problem/view/JOI23_currencies](https://oj.uz/problem/view/JOI23_currencies)

### Summary
정점 $N$개의 트리가 주어지고, $M$개의 간선은 지나려면 통행료를 내야 한다.  
$P_i$번째 간선을 통과하기 위해서는 $1$개의 금화를 내거나, $C_i$개의 은화를 내야 한다. $(1 \leq i \leq M)$  
$Q$개의 쿼리가 주어지며, $i$번 쿼리에서는 $S_i$번 정점에서 $T_i$번 정점으로 금화 $X_i$개, 은화 $Y_i$개를 갖고 이동하려 한다. $(1 \leq i \leq Q)$  
이 때, 이동이 가능한지 판별하고, 가능하다면 남는 금화의 개수의 최댓값을 구하여라.

### Constraints
+ $2 \leq N \leq 100,000$
+ $1 \leq M \leq 100,000$
+ $1 \leq Q \leq 100,000$
+ $1 \leq P_j \leq N-1$, $1 \leq C_j \leq 10^9$ $(1 \leq j \leq M)$
+ $1 \leq S_k, T_k \leq N$, $0 \leq X_k \leq 10^9$, $0 \leq Y_k \leq 10^{18}$ $(1 \leq k \leq Q)$

## Solution

### Subtask 1
+ $N \leq 2000$, $M \leq 2000$, $Q \leq 2000$

한 쿼리에서 이동하는 경로에 있는 모든 통행료들을 모아서 생각하자.
통행료들의 배열 $C_i$는 금화 $1$개를 내거나, 은화 $C_i$개를 내야 함을 의미한다.
사용할 수 있는 은화의 총 개수가 정해진 상태에서, 금화를 최대한 적게 사용하는 것이 목적이니, $C_i$가 작은 통행료부터 예산이 바닥날 때까지 은화로 지불하고, 나머지를 금화로 지불하는 것이 최선이다.

!!! observation "Observation 1"
    한 쿼리 $k$에서 경로에 있는 모든 통행료들을 $C_i$의 순서대로 정렬한 후, $C_i$가 작은 통행료부터 순서대로 합이 $Y_k$이하일 때까지 최대한 더하고 남은 통행료들을 금화로 지불하는 것이 최적해이다.

**Observation 1**을 이용하여 Naive하게 각 쿼리마다 경로를 따라 모든 통행료들의 배열을 얻고, 정렬하여 답을 계산하면 $O(Q(N+M))$에 문제를 해결할 수 있다.

!!! checkpoint "CheckPoint"
    **Observation 1**을 이용하여 Naive하게 구현하면 $O(Q(N+M))$에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    Time Complexity : $O(Q(N+M))$

### Subtask 4 (Full)

$N$, $Q$, $M$이 클 때에는 직접 $C_i$들을 정렬하여 답을 구할 수 없다.
직접 정렬하지 않고, **Observation 1**의, $C_i$가 작은 값들부터 이용해야 한다는 조건을 어떻게 활용하면 좋을까?

**이분탐색**을 통해 해결할 수 있다.
우선, 편의를 위하여 모든 $C_i$가 서로 다르다고 가정한다.  
$C_i \leq T$인 통행료들의 합을 구하여 통행료들의 합이 $Y_k$보다 작거나 같은 $T$의 최댓값을 구하면, $C_i \leq T$인 통행료들의 개수가 곧 은화로 지불할 수 있는 통행료들의 수를 의미한다.
이제 경로 $(S_k, T_k)$ 에 있는 통행료들 중 $T$ 이하인 것들의 합, 혹은 개수에 대한 쿼리에 빠른 시간 안에 답할 수 있다면, 이 결과를 이용하여 이분탐색을 통해 답을 구할 수 있다.

!!! checkpoint "CheckPoint"
    경로 $(S_k, T_k)$ 에 있는 통행료들 중 $T$ 이하인 것들의 합, 혹은 개수에 대한 쿼리에 빠른 시간 안에 답할 수 있다고 가정하자.
    $C_i \leq T$인 통행료들의 합이 $Y_k$보다 작거나 같은 $T$의 최댓값을 이분탐색으로 구하여 문제를 해결할 수 있다.

루트에서 임의의 정점까지의 경로에서 $T$이하인 수들의 개수나 합은 Persistent Segment Tree를 활용하여 구할 수 있다.
트리에서 DFS를 돌며, 자식의 PST는 부모의 PST에 간선이 지나는 $C_i$를 추가한 형태로 PST를 구성한 후, 경로 $(S_k, T_k)$의 쿼리는 $S_k$, $T_k$, $lca$ 에서의 $T$에 대한 쿼리를 날려 구할 수 있다.
이분탐색에 $O(\log Y)$, PST 쿼리에서 $O(\log M)$의 시간이 걸리니, 전체 $O(N\log N+M+Q\log Y\log M)$에 문제를 해결할 수 있다.

!!! checkpoint "CheckPoint"
    필요한 쿼리는 트리에서의 Persistent Segment Tree를 이용하여 구할 수 있다.  
    전체 시간복잡도는 $O(N\log N+M+Q\log Y\log M)$이다.

!!! complexity "Complexity"
    Time Complexity : $O(N\log N+M+Q\log Y\log M)$

---

모든 쿼리가 오프라인임을 이용하면 상수가 큰 PST를 사용하지 않고도 문제를 해결할 수 있다.
$Q$번의 이분탐색을 해야 하니, Parallel Binary Search를 사용하자.

모든 쿼리에 대하여 동시에 이분탐색을 하고, 한 번 이분탐색을 할 때 $T$와 $C_i$들을 정렬한다.
정렬된 순서대로 트리에 간선 가중치 업데이트, 경로의 가중치 합을 구할 수 있어야 한다.
이는 Euler Tree Trick을 사용해서 트리를 일직선으로 핀 후, 구간 업데이트, 점 쿼리로 해결할 수 있으니 Segment Tree (Lazy Propagation 필요 없음)으로 구한다.
이분탐색에 총 $O(\log Y)$, 정렬 및 Segment Tree 쿼리에 $O(\log N)$의 시간이 걸리니, 전체 $O(N\log N+M+Q\log Y\log N)$에 문제를 해결할 수 있다.

!!! checkpoint "CheckPoint"
    오프라인 쿼리이니, Parallel Binary Search를 사용하면 간선 가중치 업데이트와 경로 가중치 합 쿼리 문제로 환원할 수 있다.
    이는 Euler Tree Trick으로 트리를 일직선으로 피고, Segment Tree를 활용하여 해결할 수 있다.  
    전체 시간복잡도는 $O(N\log N+M+Q\log Y\log N)$이다.

!!! complexity "Complexity"
    Time Complexity : $O(N\log N+M+Q\log Y\log N)$

마지막으로, 모든 $C_i$가 다르다고 가정하였는데, $C_i$가 같을 수 있다면 같은 $C_i$중 일부만 사용하는 경우를 고려할 수 없다.
이는 단순히 임의로 tie-breaking rule을 적용한 후, 이분탐색을 정렬된 $C_i$들의 배열에 대해서 시행함으로서 해결할 수 있다.

## Code
``` cpp linenums="1"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 1e5;
 
int N, M, Q;
vector<pii> adj[MAXN+10];
pii A[MAXN+10];
 
struct SEG
{
	ll tree[MAXN*4+10];
	void init()
	{
		fill(tree, tree+MAXN*4+10, 0);
	}
	void update(int node, int tl, int tr, int l, int r, ll k)
	{
		if(l<=tl && tr<=r)
		{
			tree[node]+=k;
			return;
		}
		if(r<tl || tr<l) return;
		int mid=tl+tr>>1;
		update(node*2, tl, mid, l, r, k);
		update(node*2+1, mid+1, tr, l, r, k);
	}
	ll query(int node, int tl, int tr, int k)
	{
		if(tl==tr) return tree[node];
		int mid=tl+tr>>1;
		if(k<=mid) return tree[node]+query(node*2, tl, mid ,k);
		else return tree[node]+query(node*2+1, mid+1, tr, k);
	}
}seg;
 
int L[MAXN+10], R[MAXN+10], dep[MAXN+10], par[MAXN+10][30], cnt, P[MAXN+10];
void dfs(int now, int bef, int d)
{
	L[now]=++cnt;
	par[now][0]=bef;
	dep[now]=d;
	for(auto [nxt, e] : adj[now])
	{
		if(nxt==bef) continue;
		P[e]=nxt;
		dfs(nxt, now, d+1);
	}
	R[now]=cnt;
}
 
int lca(int u, int v)
{
	if(dep[u]>dep[v]) swap(u, v);
	for(int i=20; i>=0; i--) if(dep[par[v][i]]>=dep[u]) v=par[v][i];
	if(u==v) return u;
	for(int i=20; i>=0; i--) if(par[u][i]!=par[v][i]) u=par[u][i], v=par[v][i];
	return par[u][0];
}
 
int C[MAXN+10];
pii B[MAXN+10];
pll D[MAXN+10];
int lo[MAXN+10], hi[MAXN+10];
int E[MAXN+10];
 
ll f(int p)
{
	int u=B[p].first, v=B[p].second, w=C[p];
	return seg.query(1, 1, N, L[u])+seg.query(1, 1, N, L[v])-2*seg.query(1, 1, N, L[w]);
}
 
int main()
{
	scanf("%d%d%d", &N, &M, &Q);
	for(int i=1; i<N; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		adj[u].push_back({v, i});
		adj[v].push_back({u, i});
	}
	for(int i=1; i<=M; i++) scanf("%d%d", &A[i].second, &A[i].first);
 
	dfs(1, 1, 1);
	for(int i=1; i<=20; i++) for(int j=1; j<=N; j++) par[j][i]=par[par[j][i-1]][i-1];
 
	for(int i=1; i<=Q; i++) scanf("%d%d%lld%lld", &B[i].first, &B[i].second, &D[i].first, &D[i].second), C[i]=lca(B[i].first, B[i].second);
 
	sort(A+1, A+M+1);
 
	for(int i=1; i<=Q; i++) lo[i]=0, hi[i]=M+1;
	while(1)
	{
		vector<pii> V;
		for(int i=1; i<=Q; i++)
		{
			if(lo[i]+1<hi[i])
			{
				V.push_back({lo[i]+hi[i]>>1, i});
			}
		}
		if(V.empty()) break;
		sort(V.begin(), V.end());
 
		seg.init();
		int pt=1;
		for(auto it : V)
		{
			for(; pt<=M && pt<=it.first; pt++)
			{
				seg.update(1, 1, N, L[P[A[pt].second]], R[P[A[pt].second]], A[pt].first);
			}
			//printf("??%d %d %lld %d\n", it.first, it.second, f(it.second), D[it.second].second);
			if(f(it.second)>D[it.second].second) hi[it.second]=it.first;
			else lo[it.second]=it.first; 
		}
	}
 
	seg.init();
	int pt=1;
	vector<pii> V;
	for(int i=1; i<=Q; i++) V.push_back({lo[i], i});
	sort(V.begin(), V.end());
	for(auto it : V)
	{
		for(; pt<=M && pt<=it.first; pt++)
		{
			seg.update(1, 1, N, L[P[A[pt].second]], R[P[A[pt].second]], 1);
		}
		E[it.second]=f(it.second);
	}
	for(; pt<=M; pt++) seg.update(1, 1, N, L[P[A[pt].second]], R[P[A[pt].second]], 1);
 
	for(int i=1; i<=Q; i++)
	{
		//printf("%d %d %d\n", lo[i], f(i), E[i]);
		printf("%lld\n", max(-1ll, D[i].first-f(i)+E[i]));
	}
}
```
