#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const ll INF = 4e18;
struct Line
{
    ll a, b;
    Line() : a(0), b(INF) {} // min : INF , max : -INF
    Line(ll _a, ll _b) : a(_a), b(_b) {}
    ll operator () (ll x) { return a*x+b; }
};
struct LiChao
{
    struct Node
    {
        Line f;
        int lc, rc;
        Node() : f(), lc(-1), rc(-1) {}
    };
    vector<Node> tree;
    int root;

    int newNode()
    {
        tree.push_back(Node());
        return tree.size()-1;
    }

    void update(int node, ll tl, ll tr, Line p)
    {
        ll mid=tl+tr>>1;
        if(p(mid) < tree[node].f(mid)) swap(p, tree[node].f); // min : < , max : >
        if(tl==tr) return;
        if(p(tl) < tree[node].f(tl)) // min : < , max : >
        {
            if(tree[node].lc==-1) tree[node].lc=newNode();
            update(tree[node].lc, tl, mid, p);
        }
        if(p(tr) < tree[node].f(tr)) // min : < , max : >
        {
            if(tree[node].rc==-1) tree[node].rc=newNode();
            update(tree[node].rc, mid+1, tr, p);
        }
    }

    ll query(int node, ll tl, ll tr, ll x)
    {
        if(node==-1) return INF; // min : INF , max : -INF
        ll mid=tl+tr>>1;
        ll ret=tree[node].f(x);
        if(x<=mid) ret=min(ret, query(tree[node].lc, tl, mid, x)); // min : min() , max : max()
        else ret=min(ret, query(tree[node].rc, mid+1, tr, x)); // min : min() , max : max()
        return ret;
    }

    LiChao()
    {
        root=newNode();
    }
}lct;

int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    ll tt=1e9;
    for(int i=1; i<=N; i++)
    {
        ll a, b;
        scanf("%lld%lld", &a, &b);
        lct.update(lct.root, -tt, tt, Line(a, b));
    }
    while(Q--)
    {
        int t;
        scanf("%d", &t);
        if(t==0)
        {
            ll a, b;
            scanf("%lld%lld", &a, &b);
            lct.update(lct.root, -tt, tt, Line(a, b));
        }
        else
        {
            ll x;
            scanf("%lld", &x);
            printf("%lld\n", lct.query(lct.root, -tt, tt, x));
        }
    }
}