---
title: IOI 2019 Day 1 P3 Rectangles
tags:
    - implementation
    - sorting
    - stack
    - ~ solution
---

# IOI 2019 Day 1 P3 Rectangles

## Problem

### Problem Link
[https://www.acmicpc.net/problem/19916](https://www.acmicpc.net/problem/19916)  
[https://oj.uz/problem/view/IOI19_rect](https://oj.uz/problem/view/IOI19_rect)

### Summary
2차원 배열 $A$가 주어질 때, $y_1 \le y \le y_2$, $x_1 \le x \le x_2$ 를 만족하는 $A[y][x]$로 구성된 $A$의 부분직사각형 $(y_1, y_2, x_1, x_2)$에 대하여 다음을 만족하는 부분직사각형의 개수를 구하여라.

- $2 \le y_1 \le y_2 \le N-1$, $2 \le x_1 \le x_2 \le M-1$
- $\forall \ y_1 \le y \le y_2, x_1 \le x \le x_2$, $min(A[y_1-1][x], A[y_2+1][x], A[y][x_1-1], A[y][x_2+1])>A[y][x]$

### Constraints

- $1 \le N, M \le 2,500$
- $0 \le A[i][j] \le 7,000,000$ $(1 \le i \le N, 1 \le j \le M)$

## Solution

### Subtask 5

- $N \le 3$

$N \le 3$이니, $1$차원 배열에서 $x$축에 대하여 다음 조건을 만족하는 구간 $(x_1, x_2)$의 개수를 세는 문제이다.

- $2 \le x_1 \le x_2 \le M-1$
- $\forall x_1 \le x \le x_2$, $min(A[2][x_1-1], A[2][x_2+1])>A[2][x]$
- $\forall x_1 \le x \le x_2$, $min(A[1][x], A[3][x])>A[2][x]$

조건 $min(A[1][x], A[3][x])>A[2][x]$을 만족하지 않는 점 $x$는 어떤 구간에도 포함될 수 없으니, 조건을 만족하는 점들만 남기고 배열을 여러 개의 배열로 쪼갤 수 있다.
이와 같이 배열을 쪼갠 후 조건 $min(A[2][x_1-1], A[2][x_2+1])>A[2][x]$을 만족하는 구간의 개수를 세자.

구간의 최댓값 $A[k]$를 고정해 놓고, $A[k]$를 포함하며 조건을 만족하는 구간 $(l, r)$이 몇개 있을 수 있는지 생각해보자.
$A[k]$가 최댓값이기 때문에 $A[l-1]>A[k]$, $A[r+1]>A[k]$, $A[i] \le A[k] (l \le i \le r)$를 만족해야 한다.
$l=r=k$에서 시작하여, 조건을 만족할 때까지 한 칸씩 확장시켜보자.  
$A[l-1] \le A[k]$이거나 $A[r+1] \le A[k]$라면, 조건을 만족하지 않기 때문에 $l$이나 $r$을 한 칸씩 확장시켜 구간 안에 포함시켜야 한다.
위 과정을 반복하여 $A[l] > A[k]$, $A[r] > A[k]$라면, 조건을 만족할 뿐만 아니라 여기서 한칸이라도 더 확장시키는 순간 $A[k]$가 최댓값이라는 조건에 위배되니, 이러한 $(l, r)$이 조건을 만족하는 유일한 $(l, r)$이다.

<center>
![image 1](./1.png)
</center>

따라서, 각 최댓값 $A[k]$에 대하여 조건을 만족하는 $(l, r)$은 최대 $1$개 존재하니, 전체 가능한 답의 개수는 최대 $O(M)$이다.
각 $k$에 대하여 $l<k, A[l]>A[k]$인 최대 $l$와 $k<r, A[r]>A[k]$인 최대 $r$을 stack으로 관리하면 $O(M)$에 해결할 수 있다.

!!! observation "Observation 1"    
    $1$차원 문제에서 구간의 최댓값을 $A[k]$로 고정하였을 때 조건 $\forall x_1 \le x \le x_2$, $min(A[2][x_1-1], A[2][x_2+1])>A[2][x]$을 만족하는 $(x_1, x_2)$은 최대 $1$개 존재한다.  
    따라서 전체 가능한 구간의 수는 최대 $O(M)$개이다.
    
!!! checkpoint "CheckPoint"
    **Observation 1**에 의해 1차원 문제에서 가능한 구간의 수는 최대 $N$개이니 각 $k$에 대하여 $l<k, A[l]>A[k]$인 최대 $l$와 $k<r, A[r]>A[k]$인 최소 $r$을 stack으로 관리하면 $O(M)$에 해결할 수 있다.

!!! complexity "Complexity"
    Time Complexity : $O(M)$

### Subtask 7 (Full)

$2$차원 상황에서도 비슷한 아이디어로 접근할 수 있다.  
우선, **Observation 1**에서 조건 $\forall \ y_1 \le y \le y_2, x_1 \le x \le x_2$, $min(A[y_1-1][x], A[y_2+1][x])>A[y][x], min(A[y][x_1-1], A[y][x_2+1])>A[y][x]$을 만족하는 "구간" $(y_1, y_2)$, $(x_1, x_2)$는 각 행, 열별로 $O(M)$, $O(N)$개이다.

또한, 전과 비슷하게 직사각형 내의 전체 최댓값 $A[p][q]$를 고정하면 **Observation 1**에서 $p$행과 $q$열에 대하여 조건을 만족하는 $(y_1, y_2, x_1, x_2)$는 정확히 $1$개이다.
따라서 전체 가능한 답의 최대 개수 또한 $O(NM)$임을 알 수 있다.

!!! observation "Observation 2"
    직사각형의 최댓값을 $A[p][q]$로 고정하였을 때 조건을 만족하는 직사각형 $(y_1, y_2, x_1, x_2)$은 **Observation 1**에 의해 정확히 하나로 결정된다.
    따라서 전체 가능한 직사각형의 수는 최대 $O(NM)$개이다.

이제 위 $O(NM)$개의 직사각형 후보들을 구하고, 각 후보에 대하여 직사각형 내의 다른 값들에 대해서도 조건이 성립하는지만 빠르게 확인해주면 된다.

우선, 직사각형 후보를 구하는 것은 각 행과 열에 대한 $1$차원 문제로 생각하고 **Subtask 5**에서 구했던 것과 같은 방법으로 stack을 이용하여 각 행, 열별로 조건을 만족하는 구간들을 구하면 된다.
각 행, 열별로 $O(M)$, $O(N)$의 시간이 걸리니 전체 $O(NM)$의 시간에 해결할 수 있다.

직사각형 후보 $(y_1, y_2, x_1, x_2)$가 조건을 성립하는지 확인하는 방법은, $\forall \ y_1 \le y \le y_2$, 행 $y$에 대한 구간 $(y, x_1, x_2)$이 조건을 만족하며 $\forall \ x_1 \le x \le x_2$, 열 $x$에 대한 구간 $(x, y_1, y_2)$이 조건을 만족하는지 확인하는 것이다.
이를 위하여 다음과 같은 값을 전처리하자.

!!! definition "Definition 1"
    $low(y_1, x_1, x_2):=$ 행 $y_1$에 대한 구간 $(y_1, x_1, x_2)$이 조건을 만족할 때, 조건을 만족하며 내려갈 수 있는 최대의 $y$  
    $low(y_1, x_1, x_2)=y_2$라 할 때, $\forall \ y_1 \le y \le y_2$, 행 $y$에 대한 구간 $(y, x_1, x_2)$이 모두 조건을 만족하는 최대의 $y_2$

    $low(x_1, y_1, y_2):=$ 열 $x_1$에 대한 구간 $(x_1, y_1, y_2)$이 조건을 만족할 때, 조건을 만족하며 오른쪽으로 갈 수 있는 최대의 $x$  
    $low(x_1, y_1, y_2)=x_2$라 할 때, $\forall \ x_1 \le x \le x_2$, 열 $x$에 대한 구간 $(x, y_1, y_2)$이 모두 조건을 만족하는 최대의 $x_2$

조건을 만족하는 행 $y$에 대한 구간 $(y, x_1, x_2)$, 열 $x$에 대한 구간 $(x, y_1, y_2)$을 모두 구해놓았다면 $low(y_1, x_1, x_2)$, $low(x_1, y_1, y_2)$ 또한 구할 수 있다.
조건을 만족하는 $NM$개의 일차원 구간들을 모두 $y$, $x$에 대하여 정렬한 후, 다음 $y$, $x$에 대한 구간이 존재하는지 확인하면 되기 때문에, 이분탐색 등을 통해 이 과정은 $O(NMlogNM)$에 전처리 하면 된다.
이제, 직사각형 후보 $(y_1, y_2, x_1, x_2)$가 조건을 성립하는지 확인하는 방법은 단순히 $low(y_1, x_1, x_2) \ge y_2$, $low(x_1, y_1, y_2) \ge x_2$인지 확인하는 것이다.

!!! checkpoint "CheckPoint"
    **Observation 2**에 의해 전체 가능한 직사각형 후보의 수가 $O(NM)$개이니, **Subtask 5**에서 구했던 것과 같은 방법으로 stack을 이용하여 각 행, 열별로 조건을 만족하는 구간들을 $O(NM)$에 구한다.
    직사각형 후보가 조건을 만족하는지 확인하기 위하여 **Definition 1**과 같이 $low(y_1, x_1, x_2)$, $low(x_1, y_1, y_2)$를 이분탐색 등을 활용하여 $O(NMlogNM)$에 전처리한다.
    이후, 직사각형 후보 $(y_1, y_2, x_1, x_2)$가 조건을 성립하는지 확인하기 위하여 $low(y_1, x_1, x_2) \ge y_2$, $low(x_1, y_1, y_2) \ge x_2$인지 확인하여 답의 개수를 센다.

!!! complexity "Complexity"
    Time Complexity : $O(NMlogNM)$

하지만 이를 그냥 구현하면 TLE를 받고, vector을 이용하지 말고, 이분탐색보다는 Two Pointer 이 가능한 경우에는 Two Pointer을 이용하고, 비트별로 쪼개는 등의 여러 최적화를 해야 100점을 맞을 수 있다.

## Code
``` cpp linenums="1"
#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
 
#include "rect.h"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 2500;
 
int N, M, A[MAXN+10][MAXN+10];
int L[MAXN+10][MAXN+10], R[MAXN+10][MAXN+10], U[MAXN+10][MAXN+10], D[MAXN+10][MAXN+10];
 
struct Line
{
	int y, x;
	Line() {}
	Line(int y, int x1, int x2) : y(y), x((x1<<12)|x2) {}
	bool operator < (const Line &p) const
	{
		if(y!=p.y) return y<p.y;
		return x<p.x;
	}
 
	bool operator == (const Line &p) { return y==p.y && x==p.x; }
	bool operator != (const Line &p) { return !(y==p.y && x==p.x); }
};
 
struct Data
{
	Line first; int second;
	Data() {}
	Data(Line a, int b) : first(a), second(b) {}
	bool operator < (const Data &p) const { return first<p.first; };
};
 
Line H[MAXN*MAXN+10], V[MAXN*MAXN+10];
int HS, VS;
int lowH[MAXN*MAXN+10], lowV[MAXN*MAXN+10];
ll ans[MAXN*MAXN+10], anss;
int posH[MAXN+10][MAXN+10], posV[MAXN+10][MAXN+10];
Data HT[MAXN*MAXN+10], VT[MAXN*MAXN+10];
int HTS, VTS;
 
ll count_rectangles(vector<vector<int>> _A)
{
	N=_A.size(); M=_A[0].size();
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) A[i][j]=_A[i-1][j-1];
 
	for(int i=1; i<=N; i++)
	{
		vector<int> S;
		S.clear();
		for(int j=1; j<=M; j++) L[i][j]=0;
		for(int j=1; j<=M; j++)
		{
			while(!S.empty() && A[i][S.back()]<=A[i][j]) S.pop_back();
			if(!S.empty()) L[i][j]=S.back();
			S.push_back(j);
		}
 
		S.clear();
		for(int j=1; j<=M; j++) R[i][j]=M+1;
		for(int j=M; j>=1; j--)
		{
			while(!S.empty() && A[i][S.back()]<=A[i][j]) S.pop_back();
			if(!S.empty()) R[i][j]=S.back();
			S.push_back(j);
		}
	}
	
	for(int i=1; i<=M; i++)
	{
		vector<int> S;
		S.clear();
		for(int j=1; j<=N; j++) U[j][i]=0;
		for(int j=1; j<=N; j++)
		{
			while(!S.empty() && A[S.back()][i]<=A[j][i]) S.pop_back();
			if(!S.empty()) U[j][i]=S.back();
			S.push_back(j);
		}
 
		S.clear();
		for(int j=1; j<=N; j++) D[j][i]=N+1;
		for(int j=N; j>=1; j--)
		{
			while(!S.empty() && A[S.back()][i]<=A[j][i]) S.pop_back();
			if(!S.empty()) D[j][i]=S.back();
			S.push_back(j);
		}
	}
 
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			if(L[i][j]==0) continue;
			if(R[i][j]==M+1) continue;
			H[HS++]=Line(i, L[i][j]+1, R[i][j]-1);
		}
		for(int j=1; j<=M; j++)
		{
			if(U[i][j]==0) continue;
			if(D[i][j]==N+1) continue;
			V[VS++]=Line(j, U[i][j]+1, D[i][j]-1);
		}
	}
 
	sort(H, H+HS);
	HS=unique(H, H+HS)-H;
 
	sort(V, V+VS);
	VS=unique(V, V+VS)-V;
 
	for(int i=HS-1, j=HS-1; i>=0; i--)
	{
		lowH[i]=H[i].y;
		Line t=Line(H[i].y+1, H[i].x>>12, H[i].x&4095);
		for(int ; j>=0 && t<H[j]; j--);
		if(j>=0 && t==H[j]) lowH[i]=lowH[j];
	}
 
	for(int i=VS-1, j=VS-1; i>=0; i--)
	{
		lowV[i]=V[i].y;
		Line t=Line(V[i].y+1, V[i].x>>12, V[i].x&4095);
		for(int ; j>=0 && t<V[j]; j--);
		if(j>=0 && t==V[j]) lowV[i]=lowV[j];
	}
 	
	for(int i=2; i<=N-1; i++) for(int j=2; j<=M-1; j++)
	{
		if(L[i][j]==0) continue;
		if(R[i][j]==M+1) continue;
		if(U[i][j]==0) continue;
		if(D[i][j]==N+1) continue;
 	
		Line tu={U[i][j]+1, L[i][j]+1, R[i][j]-1};
		Line tl={L[i][j]+1, U[i][j]+1, D[i][j]-1};
 		
 		HT[HTS++]=Data(tu, (i<<12)|j);
 		VT[VTS++]=Data(tl, (i<<12)|j);
 	}
 
 	sort(HT, HT+HTS);
 	for(int i=0, j=0; i<HTS; i++)
 	{
 		for(int ; j<HS && H[j]<HT[i].first; j++);
 		if(j<HS && HT[i].first==H[j]) posH[HT[i].second>>12][HT[i].second&4095]=j;
 		else posH[HT[i].second>>12][HT[i].second&4095]=-1;
 	}
 
 	sort(VT, VT+VTS);
 	for(int i=0, j=0; i<VTS; i++)
 	{
 		for(int ; j<VS && V[j]<VT[i].first; j++);
 		if(j<VS && VT[i].first==V[j]) posV[VT[i].second>>12][VT[i].second&4095]=j;
 		else posV[VT[i].second>>12][VT[i].second&4095]=-1;
 	}
 
 	for(int i=2; i<=N-1; i++) for(int j=2; j<=M-1; j++)
	{
		if(L[i][j]==0) continue;
		if(R[i][j]==M+1) continue;
		if(U[i][j]==0) continue;
		if(D[i][j]==N+1) continue;
 
		int it=posH[i][j];
		int jt=posV[i][j];
 		
 		if(it==-1 || jt==-1) continue;
 
		if(lowH[it]<D[i][j]-1) continue;
		if(lowV[jt]<R[i][j]-1) continue;
 
		ans[anss++]=(((L[i][j]<<12)|R[i][j])*1000000000ll+((U[i][j]<<12)|D[i][j]));
	}
	sort(ans, ans+anss);
	return unique(ans, ans+anss)-ans;
}
```

TLE(72점) 이지만 최적화 등을 하지 않아 가독성이 더 좋은 코드이다.
``` cpp linenums="1"
#include "rect.h"
#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
 
const int MAXN = 2500;
 
int N, M, A[MAXN+10][MAXN+10];
int L[MAXN+10][MAXN+10], R[MAXN+10][MAXN+10], U[MAXN+10][MAXN+10], D[MAXN+10][MAXN+10];
 
struct Line
{
	int y, x1, x2;
	bool operator < (const Line &p) const
	{
		if(y!=p.y) return y<p.y;
		if(x1!=p.x1) return x1<p.x1;
		return x2<p.x2;
	}
 
	bool operator == (const Line &p) { return y==p.y && x1==p.x1 && x2==p.x2; }
};
 
vector<Line> H, V;
int lowH[MAXN*MAXN+10], lowV[MAXN*MAXN+10];
 
ll count_rectangles(vector<vector<int>> _A)
{
	N=_A.size(); M=_A[0].size();
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++) A[i][j]=_A[i-1][j-1];
 
	for(int i=1; i<=N; i++)
	{
		vector<int> S;
		S.clear();
		for(int j=1; j<=M; j++) L[i][j]=0;
		for(int j=1; j<=M; j++)
		{
			while(!S.empty() && A[i][S.back()]<=A[i][j]) S.pop_back();
			if(!S.empty()) L[i][j]=S.back();
			S.push_back(j);
		}
 
		S.clear();
		for(int j=1; j<=M; j++) R[i][j]=M+1;
		for(int j=M; j>=1; j--)
		{
			while(!S.empty() && A[i][S.back()]<=A[i][j]) S.pop_back();
			if(!S.empty()) R[i][j]=S.back();
			S.push_back(j);
		}
	}
	
	for(int i=1; i<=M; i++)
	{
		vector<int> S;
		S.clear();
		for(int j=1; j<=N; j++) U[j][i]=0;
		for(int j=1; j<=N; j++)
		{
			while(!S.empty() && A[S.back()][i]<=A[j][i]) S.pop_back();
			if(!S.empty()) U[j][i]=S.back();
			S.push_back(j);
		}
 
		S.clear();
		for(int j=1; j<=N; j++) D[j][i]=N+1;
		for(int j=N; j>=1; j--)
		{
			while(!S.empty() && A[S.back()][i]<=A[j][i]) S.pop_back();
			if(!S.empty()) D[j][i]=S.back();
			S.push_back(j);
		}
	}
 
	for(int i=1; i<=N; i++)
	{
		for(int j=1; j<=M; j++)
		{
			if(L[i][j]==0) continue;
			if(R[i][j]==M+1) continue;
			H.push_back({i, L[i][j]+1, R[i][j]-1});
		}
		for(int j=1; j<=M; j++)
		{
			if(U[i][j]==0) continue;
			if(D[i][j]==N+1) continue;
			V.push_back({j, U[i][j]+1, D[i][j]-1});
		}
	}
 
	sort(H.begin(), H.end());
	H.erase(unique(H.begin(), H.end()), H.end());
 
	sort(V.begin(), V.end());
	V.erase(unique(V.begin(), V.end()), V.end());
 
	for(int i=H.size()-1; i>=0; i--)
	{
		lowH[i]=H[i].y;
		Line t={H[i].y+1, H[i].x1, H[i].x2};
		if(binary_search(H.begin(), H.end(), t)) lowH[i]=lowH[lower_bound(H.begin(), H.end(), t)-H.begin()];
	}
 
	for(int i=V.size()-1; i>=0; i--)
	{
		lowV[i]=V[i].y;
		Line t={V[i].y+1, V[i].x1, V[i].x2};
		if(binary_search(V.begin(), V.end(), t)) lowV[i]=lowV[lower_bound(V.begin(), V.end(), t)-V.begin()];
	}
 
	vector<tuple<int, int, int, int>> ans;
	for(int i=1; i<=N; i++) for(int j=1; j<=M; j++)
	{
 
		//printf("%d %d : %d %d %d %d\n", i, j, L[i][j], R[i][j], U[i][j], D[i][j]);
		if(L[i][j]==0) continue;
		if(R[i][j]==M+1) continue;
		if(U[i][j]==0) continue;
		if(D[i][j]==N+1) continue;
 
		Line tu={U[i][j]+1, L[i][j]+1, R[i][j]-1};
		if(!binary_search(H.begin(), H.end(), tu)) continue;
		Line tl={L[i][j]+1, U[i][j]+1, D[i][j]-1};
		if(!binary_search(V.begin(), V.end(), tl)) continue;
 
		if(lowH[lower_bound(H.begin(), H.end(), tu)-H.begin()]<D[i][j]-1) continue;
		if(lowV[lower_bound(V.begin(), V.end(), tl)-V.begin()]<R[i][j]-1) continue;
 
		ans.push_back(make_tuple(L[i][j]+1, R[i][j]-1, U[i][j]+1, D[i][j]-1));
	}
	sort(ans.begin(), ans.end());
	ans.erase(unique(ans.begin(), ans.end()), ans.end());
	return ans.size();
}
```