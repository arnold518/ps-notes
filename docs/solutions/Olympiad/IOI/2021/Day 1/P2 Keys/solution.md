---
title: IOI 2021 Day 1 P2 Keys
tags:
    - ~ solution
    - data_structures
    - disjoint_set
    - graphs
    - graph_traversal
    - scc
    - smaller_to_larger
---

# IOI 2021 Day 1 P2 Keys

## Problem

### Problem Link
[https://www.acmicpc.net/problem/22024](https://www.acmicpc.net/problem/22024)  
[https://oj.uz/problem/view/IOI21_keys](https://oj.uz/problem/view/IOI21_keys)

### Summary
정점 $N$개, 간선 $M$개의 단순 양방향 그래프가 주어진다.  
각 정점에는 열쇠가 하나씩 있는데, $i$번 정점의 열쇠의 종류는 $R_i$이다. $(1 \le i \le N)$  
각 간선을 지나기 위해서는 열쇠가 있어야 하는데, $i$번째 간선을 지나기 위해 필요한 열쇠의 종류는 $C_i$이다. $(1 \le i \le M)$  
$v$번 정점에서 이동을 시작할 때, 정점들을 돌아다니며 얻을 수 있는 열쇠를 얻고, 자신이 갖고 있는 열쇠를 이용하여 이동이 가능한 간선을 따라 이동할 수 있다.
이와 같이 $v$번 정점에서 시작하였을 때 도달가능한 정점들의 개수가 최소가 되는 정점 $v$들의 집합을 구하여라.

### Constraints

- $2 \le N \le 300,000$
- $1 \le M \le 300,000$
- $1 \le R_i \le N$ $(1 \le i \le N)$
- $1 \le C_i \le N$ $(1 \le i \le M)$

## Solution

### Subtask 3

- $N, M \le 2,000$

각 정점에서 시작하여, 이 정점에서 도달할 수 있는 모든 정점들을 구하기 위하여 다음과 같은 BFS 알고리즘을 생각하자.  
그래프 탐색을 하며 "지금까지 방문한 정점들의 열쇠 $C$의 집합"과, "지금까지 방문한 정점들과 인접한 간선들 중 아직 열쇠를 발견하지 못한 간선들의 집합"을 종류별로 나누어 배열으로 관리하자.
만약 새로운 정점 $v$를 방문하였는데, $C_v$가 지금까지는 본 적 없는 종류의 열쇠라면, 이 열쇠를 이용하여 이전에는 사용하지 못했던, $C_v=R_e$를 만족하는 간선 $e$들을 queue에 삽입해주면 된다.
새로운 간선 $e$를 발견하였는데, $R_e$가 이미 발견한 종류의 열쇠라면 바로 queue에 삽입해주면 되고, 아니면 아직 열쇠를 발견하지 못한 간선들의 리스트에 추가해주면 된다.

위 알고리즘을 통하여 각 시작점에 대하여 $O(N+M)$의 시간에 BFS를 할 수 있으니, 전체 $O(N(N+M))$의 시간에 문제를 해결할 수 있다.

!!! checkpoint "Checkpoint"
    각 정점에서 시작하여, 이 정점에서 도달할 수 있는 모든 정점들을 구하기 위하여 다음과 같은 BFS 알고리즘을 생각하자.  
    그래프 탐색을 하며 "지금까지 방문한 정점들의 열쇠 $C$의 집합"과, "지금까지 방문한 정점들과 인접한 간선들 중 아직 열쇠를 발견하지 못한 간선들의 집합"을 종류별로 나누어 배열으로 관리하자.
    만약 새로운 정점 $v$를 방문하였는데, $C_v$가 지금까지는 본 적 없는 종류의 열쇠라면, 이 열쇠를 이용하여 이전에는 사용하지 못했던, $C_v=R_e$를 만족하는 간선 $e$들을 queue에 삽입해주면 된다.
    새로운 간선 $e$를 발견하였는데, $R_e$가 이미 발견한 종류의 열쇠라면 바로 queue에 삽입해주면 되고, 아니면 아직 열쇠를 발견하지 못한 간선들의 리스트에 추가해주면 된다.

    위 알고리즘을 통하여 각 시작점에 대하여 $O(N+M)$의 시간에 BFS를 할 수 있으니, 전체 $O(N(N+M))$의 시간에 문제를 해결할 수 있다.

!!! complexity "Complexity"
    Time Complexity : $O(N^2+NM)$


### Subtask 5 (Full)

문제를 해결하기 전에, 이 문제의 상황은 일반적인 방향그래프의 SCC의 상황과 매우 비슷하다.
정점 $v$에서 시작하여 도달 가능한 정점들의 집합을 $S_v$라 할 때, $u$와 $v$가 같은 SCC에 속한다는 것은 $S_u=S_v$라는 것과 필요충분이며, SCC는 $S_v$에 대한 equivalence class라고 생각할 수 있다.
또한, 방향 간선 $u \rightarrow v$가 존재한다면 $S_u \supseteq S_v$가 성립하고, $v \in S_u$라면 $S_u \supseteq S_v$가 성립한다.

$v$번 정점에서 시작하였을 때 도달가능한 정점들의 개수가 최소가 되는 정점 $v$들의 집합을 구해야 하는 이 문제의 상황을 SCC의 상황으로 생각해보면, 결국 condensation graph에서 outdegree가 없는 SCC들을 모두 구해야 하는 상황과 일치한다.
condensation graph에서 outdegree가 없는 SCC에 속하는 정점 $u$에 대해서는 $v \in S_u$인 다른 정점 $v$에 대해 $S_u=S_v$라는 것을 알 수 있다.

!!! observation "Observation 1"
    방향그래프의 SCC에는 다음과 같은 성질들이 성립한다.

    정점 $v$에서 시작하여 도달 가능한 정점들의 집합을 $S_v$라 하자.

    1. $u$와 $v$가 같은 SCC에 속한다는 것은 $S_u=S_v$라는 것과 필요충분이며, SCC는 $S_v$에 대한 equivalence class라고 생각할 수 있다.
    2. 방향 간선 $u \rightarrow v$가 존재한다면 $S_u \supseteq S_v$가 성립한다.
    3. $v \in S_u$라면, $S_u \supseteq S_v$가 성립한다.
    4. condensation graph에서 outdegree가 없는 SCC에 속하는 정점 $u$에 대해서는 $v \in S_u$인 다른 정점 $v$에 대해 $S_u=S_v$가 성립한다.

위 **Observation 1**의 성질은 SCC에서 성립하는 성질이지만, 이 문제에서도 성립하며 풀이의 결정적인 관찰을 제공한다.
따라서, 이 문제의 조건과 상황은 다르더라도 이와 같이 각 정점에서 $v$번 정점에서 시작하였을 때 도달가능한 정점들의 개수가 최소가 되는 정점 $v$들의 집합을 구해야 하는 문제에서 이 문제의 풀이를 적용할 수 있다.

---

$v$번 정점에서 시작하였을 때 도달가능한 정점들의 집합을 $S_v$라 하자.
간선 $(u, v, c)$에 대하여 만약 $S_u$의 정점들 중 열쇠 $c$를 얻을 수 있는 정점이 포함되어 있다면, $u$에서 시작하여 $v$로 이동할 수 있으며, 따라서 $S_u \supseteq S_v$가 성립한다.

!!! observation "Observation 2"
    $v$번 정점에서 시작하였을 때 도달가능한 정점들의 집합을 $S_v$라 하자.

    간선 $(u, v, c)$에 대하여 만약 $S_u$의 정점들 중 열쇠 $c$를 얻을 수 있는 정점이 포함되어 있다면, $u$에서 시작하여 $v$로 이동할 수 있으며, 따라서 $S_u \supseteq S_v$가 성립한다.

간선 $(u, v, c)$에 대하여 $R_u=c$이면, **Observation 2**에 의해 $S_u \supseteq S_v$가 성립한다.
각 $u$에 대하여 이와 같이 확실히 $S_u \supseteq S_v$라는 것을 아는 정점 $v$에 대하여 $par(u)=v$로 간선을 하나씩 이어 주면, 완성된 그래프에서 각 정점의 outdegree는 $0$ 아니면 $1$으로, functional graph나 트리들의 집합이 된다.
이 때, functional graph의 루트에 해당하는 사이클 $P=\{v_1, v_2, \cdots, v_k \}$에 대해 다음이 성립한다.

$$S_{v_1} \supseteq S_{v_2} \supseteq \cdots S_{v_k} \supseteq S_{v_1}$$

$$S_{v_1} = S_{v_2} = \cdots = S_{v_k}$$

즉, functional graph의 루트에 해당하는 사이클 $P=\{v_1, v_2, \cdots, v_k \}$에 해당하는 모든 정점들의 $S_v$가 같으니 이들을 하나의 정점으로 묶어서 취급할 수 있다.
(이는 방향 그래프에서 정점들을 $S_v$가 같은 정점들을 하나의 SCC로 묶는다고 생각해도 된다.)
이후, 묶인 새로운 정점들의 열쇠 집합과 간선 집합을 하나로 묶어준 후, 다시 간선 $(u, v, c)$에 대하여 $u \in P, v \notin P, R_u=c$인 $v$를 찾아 $par(u)=v$로 간선을 새롭게 이어주면 된다.

위 과정을 반복하다 보면, 완성된 그래프는 더이상 functional graph가 남아 있지 않고, 여러 트리들의 집합이 남는다.
$S_u$의 크기가 최소가 되는 정점 $u$는 **Observation 1**과 같이 $v \in S_u$인 다른 정점 $v$에 대해 $S_u=S_v$가 성립해야 한다.
트리의 루트에 속하는 정점들은 더 이상 밖으로 나가는 간선을 찾을 수 없다는 의미이니, 집합 밖으로 이동할 수 없고, 따라서 답으로 가능한 정점들은 오직 루트에 속한 정점들이다.

전체 알고리즘은 위와 같이 정점들의 집합을 관리하며, 각 집합에서 밖으로 나갈 수 있는 한 정점 $par(v)$를 이용하여 functional graph를 만들고, 루트에 해당하는 사이클을 묶어서 한 집합으로 만든 후 새로운 $par(v)$를 구해주어야 한다.
이를 효율적으로 관리하기 위하여 Union Find와 각 정점의 열쇠 집합과 나가는 간선들의 집합을 관리하기 위하여 Set과 Small to Large를 이용하면 된다.
전체 시간복잡도는 Set에서 Small to Large를 해야 하니, $O((N+M)log^2M)$이 된다.

!!! checkpoint "CheckPoint"
    간선 $(u, v, c)$에 대하여 $R_u=c$이면, **Observation 2**에 의해 $S_u \supseteq S_v$가 성립한다.
    각 $u$에 대하여 이와 같이 확실히 $S_u \supseteq S_v$라는 것을 아는 정점 $v$에 대하여 $par(u)=v$로 간선을 하나씩 이어 주면, 완성된 그래프에서 각 정점의 outdegree는 $0$ 아니면 $1$으로, functional graph나 트리들의 집합이 된다.
    이 때, functional graph의 루트에 해당하는 사이클 $P=\{v_1, v_2, \cdots, v_k \}$에 해당하는 모든 정점들의 $S_v$가 같으니 이들을 하나의 정점으로 묶어서 취급할 수 있다.
    이후, 묶인 새로운 정점들의 열쇠 집합과 간선 집합을 하나로 묶어준 후, 다시 간선 $(u, v, c)$에 대하여 $u \in P, v \notin P, R_u=c$인 $v$를 찾아 $par(u)=v$로 간선을 새롭게 이어주면 된다.

    위 과정을 반복하다 보면, 완성된 그래프는 더이상 functional graph가 남아 있지 않고, 여러 트리들의 집합이 남는다.
    트리의 루트에 속하는 정점들은 더 이상 밖으로 나가는 간선을 찾을 수 없다는 의미이니, 집합 밖으로 이동할 수 없고, 따라서 답으로 가능한 정점들은 오직 루트에 속한 정점들이다.

    이를 효율적으로 관리하기 위하여 Union Find와 각 정점의 열쇠 집합과 나가는 간선들의 집합을 관리하기 위하여 Set과 Small to Large를 이용하면 된다.
    전체 시간복잡도는 Set에서 Small to Large를 해야 하니, $O((N+M)log^2M)$이 된다.

!!! complexity "Complexity"
    Time Complexity : $O((N+M)log^2M)$

## Code
``` cpp linenums="1"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 3e5;
 
int N, M;
int R[MAXN+10];
int ans[MAXN+10];
 
set<pii> adj[MAXN+10];
vector<pii> adj2[MAXN+10];
set<int> S[MAXN+10];
 
int par[MAXN+10];
int vis[MAXN+10];
bool dead[MAXN+10];
 
struct UF
{
	int par[MAXN+10];
	int Find(int x)
	{
		if(x==par[x]) return x;
		return par[x]=Find(par[x]);
	}
	void Union(int x, int y)
	{
		x=Find(x); y=Find(y);
		par[x]=y;
	}
	void init()
	{
		for(int i=1; i<=N; i++) par[i]=i;
	}
}uf, uf2;
 
int cnt[MAXN+10];
 
vector<int> find_reachable(vector<int> _R, vector<int> _U, vector<int> _V, vector<int> _C)
{
	N=_R.size(); M=_U.size();
	for(int i=1; i<=N; i++) R[i]=_R[i-1]+1;
	for(int i=1; i<=M; i++)
	{
		int u=_U[i-1]+1, v=_V[i-1]+1, w=_C[i-1]+1;
		if(R[u]!=w) adj[u].insert({w, v});
		else adj2[u].push_back({w, v});
 
		if(R[v]!=w) adj[v].insert({w, u});
		else adj2[v].push_back({w, u});
	}
 
	uf.init(); uf2.init();
	for(int i=1; i<=N; i++)
	{
		S[i].insert(R[i]);
 
		if(!adj2[i].empty())
		{
			par[i]=adj2[i].back().second;
			uf.Union(i, par[i]);
		}
	}
 
	queue<int> Q;
	for(int i=1; i<=N; i++)
	{
		int now=i;
		while(1)
		{
			if(vis[now]) break;
			vis[now]=i;
			if(par[now]==0) break;
			now=par[now];
		}
		if(par[now]!=0 && vis[now]==i) Q.push(now);
	}
 
	while(!Q.empty())
	{
		int now=Q.front(); Q.pop();
		now=uf2.Find(now);
 
		vector<int> V;
		for(int i=par[now]; i!=now; i=uf2.Find(par[i])) V.push_back(i);
 
		for(auto it : V)
		{
			if(adj[now].size()+adj2[now].size()+S[now].size()<adj[it].size()+adj2[it].size()+S[it].size()) swap(now, it);
			
			for(auto jt : adj2[it]) adj2[now].push_back(jt);
			for(auto jt : adj[it])
			{
				auto pt=S[now].lower_bound(jt.first);
				if(pt!=S[now].end() && *pt==jt.first) adj2[now].push_back(jt);
				else adj[now].insert(jt);
			}
			for(auto jt : S[it])
			{
				for(auto pt=adj[now].lower_bound({jt, 0}); pt!=adj[now].end() && pt->first==jt; pt=adj[now].erase(pt)) adj2[now].push_back(*pt);
				S[now].insert(jt);
			}
			uf2.Union(it, now);
			dead[it]=true;
		}
 
		while(!adj2[now].empty() && uf2.Find(adj2[now].back().second)==now) adj2[now].pop_back();
 
		if(!adj2[now].empty())
		{
			assert(S[now].count(adj2[now].back().first));
			par[now]=uf2.Find(adj2[now].back().second);
			if(uf.Find(now)==uf.Find(par[now])) Q.push(now);
			else uf.Union(now, par[now]);
		}
		else par[now]=0;
	}
	for(int i=1; i<=N; i++) cnt[uf2.Find(i)]++;
 
	int val=N;
	set<int> SS;
	for(int i=1; i<=N; i++) if(par[uf2.Find(i)]==0) val=min(val, cnt[uf2.Find(i)]);
	for(int i=1; i<=N; i++) if(par[uf2.Find(i)]==0 && cnt[uf2.Find(i)]==val) SS.insert(uf2.Find(i));
	for(int i=1; i<=N; i++) if(SS.count(uf2.Find(i))) ans[i]=1;
	
	return vector<int>(ans+1, ans+N+1);
}
```