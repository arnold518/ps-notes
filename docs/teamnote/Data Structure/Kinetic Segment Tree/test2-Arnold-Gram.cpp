// https://judge.yosupo.jp/problem/line_add_get_min

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
        assert(p.b<=q.b); // min : <= , max : >=
        if(p.a<=q.a) return INF; // min : <= , max : >=
        return divfloor(p.b-q.b, q.a-p.a)+1;
    }

    struct SEG
    {
        vector<Line> tree;
        vector<ll> melt; // minimum time left for next cross in subtree
        vector<ll> lazy;

        SEG(int N)
        {
            tree = vector<Line>(N*4+10);
            melt = vector<ll>(N*4+10);
            lazy = vector<ll>(N*4+10);
        }

        void busy(int node, int tl, int tr)
        {
            assert(lazy[node]<melt[node]);
            tree[node].b+=tree[node].a*lazy[node];
            melt[node]-=lazy[node];
            if(tl!=tr) lazy[node*2]+=lazy[node], lazy[node*2+1]+=lazy[node];
            lazy[node]=0;
        }

        void init(int node, int tl, int tr)
        {
            tree[node]={0, INF}; // min : INF , max : -INF
            melt[node]=INF;
            lazy[node]=0;
            if(tl==tr) return;
            int mid=tl+tr>>1;
            init(node*2, tl, mid);
            init(node*2+1, mid+1, tr);
        }

        void recalc(int node)
        {
            melt[node]=min(melt[node*2], melt[node*2+1]);
            if(tree[node*2].b<=tree[node*2+1].b) // min : <= , max : >=
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
            busy(node, tl, tr);
            if(r<tl || tr<l) return;
            if(l<=tl && tr<=r && melt[node]>t)
            {
                lazy[node]=t;
                busy(node, tl, tr);
                return;
            }
            int mid=tl+tr>>1;
            heaten(node*2, tl, mid, l, r, t);
            heaten(node*2+1, mid+1, tr, l, r, t);
            recalc(node);
        }

        // get minimum/maximum B[i] for i in [l, r]
        // O(QlogN)
        ll query(int node, int tl, int tr, int l, int r)
        {
            busy(node, tl, tr);
            if(r<tl || tr<l) return INF; // min : INF , max : -INF
            if(l<=tl && tr<=r) return tree[node].b;
            int mid=tl+tr>>1;
            return min(query(node*2, tl, mid, l, r), query(node*2+1, mid+1, tr, l, r)); // min : min() , max : max()
        }

        // update A[pos], B[pos]
        // O(QlogN)
        void update(int node, int tl, int tr, int pos, Line p)
        {
            busy(node, tl, tr);
            if(tl==tr)
            {
                tree[node]=p;
                return;
            }
            int mid=tl+tr>>1;
            if(pos<=mid) update(node*2, tl, mid, pos, p);
            else update(node*2+1, mid+1, tr, pos, p);
            recalc(node);
        }

        void get(int node, int tl, int tr)
        {
            busy(node, tl, tr);
            printf("GET [%d %d] : %lld %lld\n", tl, tr, tree[node].a, tree[node].b);
            if(tl==tr) return;
            int mid=tl+tr>>1;
            get(node*2, tl, mid);
            get(node*2+1, mid+1, tr);
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
        scanf("%lld%lld%lld%lld", &l, &r, &a, &b);
        VV.push_back({{l, i}, KST::Line{a, b+a*l}});
        VV.push_back({{r, i}, KST::Line{0, KST::INF}});
    }

    vector<pll> V, ans;
    for(int i=1; i<=Q; i++)
    {
        int t;
        scanf("%d", &t);
        if(t==0)
        {
            ll l, r, a, b;
            scanf("%lld%lld%lld%lld", &l, &r, &a, &b);
            VV.push_back({{l, i+N}, KST::Line{a, b+a*l}});
            VV.push_back({{r, i+N}, KST::Line{0, KST::INF}});
        }
        else
        {
            ll x;
            scanf("%lld", &x);
            V.push_back({x, i+N});
        }
    }

    seg.init(1, 1, N+Q);
    sort(VV.begin(), VV.end(), [&](pair<pll, KST::Line> p, pair<pll, KST::Line> q) { return p.first<q.first; });
    sort(V.begin(), V.end());
    for(int i=0, j=0; i<V.size(); i++)
    {
        auto [x, p] = V[i];
        for(; j<VV.size() && VV[j].first.first<=x; j++)
        {
            printf("UPDATE %lld %lld %lld %lld\n", VV[j].first.first, VV[j].first.second, VV[j].second.a, VV[j].second.b);
            seg.heaten(1, 1, N+Q, 1, N+Q, VV[j].first.first-X);
            X=VV[j].first.first;

            seg.update(1, 1, N+Q, VV[j].first.second, VV[j].second);
            

            printf("X is %lld\n", X);
            seg.get(1, 1, N+Q);
        }
        seg.heaten(1, 1, N+Q, 1, N+Q, x-X);
        X=x;
        printf("X is %lld\n", X);
        seg.get(1, 1, N+Q);
        printf("QUERY %lld %lld %lld\n", x, p, seg.query(1, 1, N+Q, 1, p));
        ans.push_back({p, seg.query(1, 1, N+Q, 1, p)});
    }
    sort(ans.begin(), ans.end());
    for(auto [a, b] : ans) printf("%lld\n", b);
}