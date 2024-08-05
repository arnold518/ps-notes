// https://www.acmicpc.net/problem/4220

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 1e5;
const ll INF = 1e18;

struct Data { ll D, P, R, G; };

int N; ll C, D, dp[MAXN+10];
Data A[MAXN+10];

namespace LineContainer
{
    const ll INF = 9e18;
    struct Line
    {
        mutable ll a, b, p;
        bool operator < (const Line& o) const { return a!=o.a ? o.a>a : b>o.b; } // min : < , max : > (both)
        bool operator < (ll x) const { return p < x; }
    };

    // multiset of Line, sorted in increasing order of cross points
    struct LineContainer : multiset<Line, less<>>
    {
        // for doubles, use INF = 1/.0, div(a,b) = a/b
        ll div(ll u, ll d) { return u/d - ((u^d)<0 && u%d); }
        bool isect(iterator x, iterator y)
        {
            if (y == end()) { x->p = INF; return 0; }
            if (x->a == y->a) x->p = x->b > y->b ? INF : -INF; // min : < , max : >
            else x->p = div(y->b - x->b, x->a - y->a);
            return x->p >= y->p;
        }
        void push(ll a, ll b) {
            auto z = insert({a, b, 0}), y = z++, x = y;
            while (isect(y, z)) z = erase(z);
            if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
            while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
        }
        ll query(ll x) {
            assert(!empty());
            auto l = *lower_bound(x);
            return l.a * x + l.b;
        }
    };
}

int main()
{
	int i, j;

	for(int tc=1; ; tc++)
	{
		scanf("%d%lld%lld", &N, &C, &D);
		if(N==0) return 0;
		for(i=1; i<=N; i++) scanf("%lld%lld%lld%lld", &A[i].D, &A[i].P, &A[i].R, &A[i].G);
		sort(A+1, A+N+1, [&](const Data &p, const Data &q) { return p.D<q.D; });

		ll ans=C;

        LineContainer::LineContainer cht;
		for(i=1; i<=N; i++)
		{
			ll t=C;
            if(!cht.empty()) t=max(t, cht.query(A[i].D));

			if(t<A[i].P) dp[i]=-INF;
			else
			{
				dp[i]=t;
                cht.push(A[i].G, dp[i]-A[i].D*A[i].G-A[i].G+A[i].R-A[i].P);
				ans=max(ans, dp[i]+(D-A[i].D)*A[i].G+A[i].R-A[i].P);
			}
		}
		printf("Case %d: %lld\n", tc, ans);
	}
}