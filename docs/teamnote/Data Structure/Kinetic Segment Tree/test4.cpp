// https://judge.yosupo.jp/problem/segment_add_get_min

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

namespace KST
{
    const ll INF = 7e18;
    struct Line { ll a, b; };
    ll divfloor(ll u, ll d) { return u/d - ((u^d)<0 && u%d); }

    // p(0) <= q(0) must hold ( min : <= , max : >= )
    // minimum t>0 s.t. p(t) > q(t) ( min : > , max : < )
    ll cross(Line p, Line q)
    {
        assert(p.b>=q.b); // min : <= , max : >=
        if(p.a>=q.a) return INF; // min : <= , max : >=
        return divfloor(p.b-q.b, q.a-p.a)+1;
    }

    struct SEG
    {
        vector<Line> tree;
        vector<ll> melt; // minimum time left for next cross in subtree
        vector<ll> lazy;

        SEG(int N)
        {
            tree = vector<Line>(N*4+10, {0, -INF}); // min : INF , max : -INF
            melt = vector<ll>(N*4+10, INF);
            lazy = vector<ll>(N*4+10, 0);
        }

        // Apply update value k to subtree of node
        // update to node itself, and to lazy value
        void apply(int node, ll k)
        {
            assert(k<melt[node]);
            tree[node].b+=tree[node].a*k;
            melt[node]-=k;
            lazy[node]+=k;
        }

        // Propagate lazy value to children, and initialize lazy
        // should be called before going down to children
        void prop(int node, int tl, int tr)
        {
            if(tl!=tr)
            {
                apply(node*2, lazy[node]);
                apply(node*2+1, lazy[node]);
            }
            lazy[node]=0;
        }

        // Recalculate value of node from children
        // lazy must be empty
        void recalc(int node)
        {
            assert(lazy[node]==0);
            melt[node]=min(melt[node*2], melt[node*2+1]);
            if(tree[node*2].b>=tree[node*2+1].b) // min : <= , max : >=
            {
                tree[node]=tree[node*2];
                melt[node]=min(melt[node], cross(tree[node*2], tree[node*2+1]));
            }
            else
            {
                tree[node]=tree[node*2+1];
                melt[node]=min(melt[node], cross(tree[node*2+1], tree[node*2]));
            }
        }

        // B[i]+=A[i]*t for all i in [l, r]
        // Ammortized O(Qlog^3N) if range heaten
        // Ammortized O(Qlog^2N) if entire heaten
        void heaten(int node, int tl, int tr, int l, int r, ll t)
        {
            if(r<tl || tr<l) return;
            if(l<=tl && tr<=r && melt[node]>t)
            {
                apply(node, t);
                return;
            }
            prop(node, tl, tr);
            int mid=tl+tr>>1;
            heaten(node*2, tl, mid, l, r, t);
            heaten(node*2+1, mid+1, tr, l, r, t);
            recalc(node);
        }

        // get minimum/maximum B[i] for i in [l, r]
        // O(QlogN)
        ll query(int node, int tl, int tr, int l, int r)
        {
            if(r<tl || tr<l) return -INF; // min : INF , max : -INF
            if(l<=tl && tr<=r) return tree[node].b;
            prop(node, tl, tr);
            int mid=tl+tr>>1;
            return max(query(node*2, tl, mid, l, r), query(node*2+1, mid+1, tr, l, r)); // min : min() , max : max()
        }

        // update A[pos], B[pos]
        // O(QlogN)
        void update(int node, int tl, int tr, int pos, Line p)
        {
            if(tl==tr)
            {
                tree[node]=p;
                return;
            }
            prop(node, tl, tr);
            int mid=tl+tr>>1;
            if(pos<=mid) update(node*2, tl, mid, pos, p);
            else update(node*2+1, mid+1, tr, pos, p);
            recalc(node);
        }
    };
}

int N, Q;

int main()
{
    scanf("%d%d", &N, &Q);

    KST::SEG seg(N+Q);

    ll X=-1e9;
    vector<pair<pll, KST::Line>> VV;
    for(int i=1; i<=N; i++)
    {
        ll l, r, a, b;
        scanf("%lld%lld%lld%lld", &l, &r, &a, &b); a*=-1; b*=-1;
        VV.push_back({{l, i}, KST::Line{a, b+a*l}});
        VV.push_back({{r, i}, KST::Line{0, -KST::INF}});
    }

    vector<pll> V, ans;
    for(int i=1; i<=Q; i++)
    {
        int t;
        scanf("%d", &t);
        if(t==0)
        {
            ll l, r, a, b;
            scanf("%lld%lld%lld%lld", &l, &r, &a, &b); a*=-1; b*=-1;
            VV.push_back({{l, i+N}, KST::Line{a, b+a*l}});
            VV.push_back({{r, i+N}, KST::Line{0, -KST::INF}});
        }
        else
        {
            ll x;
            scanf("%lld", &x);
            V.push_back({x, i+N});
        }
    }

    sort(VV.begin(), VV.end(), [&](pair<pll, KST::Line> p, pair<pll, KST::Line> q) { return p.first<q.first; });
    sort(V.begin(), V.end());
    for(int i=0, j=0; i<V.size(); i++)
    {
        auto [x, p] = V[i];
        for(; j<VV.size() && VV[j].first.first<=x; j++)
        {
            seg.heaten(1, 1, N+Q, 1, N+Q, VV[j].first.first-X);
            X=VV[j].first.first;       
            seg.update(1, 1, N+Q, VV[j].first.second, VV[j].second);
        }
        seg.heaten(1, 1, N+Q, 1, N+Q, x-X);
        X=x;
        ans.push_back({p, seg.query(1, 1, N+Q, 1, p)});
    }
    sort(ans.begin(), ans.end());
    for(auto [a, b] : ans)
    {
        if(-b==KST::INF) printf("INFINITY\n");
        else printf("%lld\n", -b);
    }
}