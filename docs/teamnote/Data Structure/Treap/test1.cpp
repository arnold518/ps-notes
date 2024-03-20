// https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int MAXN = 5e5;

const int MOD = 998244353;
struct mint
{
    int x;
    mint() : x(0) {}
    mint(int _x) : x(_x) {}
    mint operator + (int ot) const { return x+ot>=MOD ? x+ot-MOD : x+ot; }
    mint operator - () const { return x ? MOD-x : 0; }
    mint operator - (int ot) const { return x<ot ? x+MOD-ot : x-ot; }
    mint operator * (int ot) const { return 1ll*x*ot%MOD; }
    mint operator += (int ot) { return *this = *this + ot; }
    mint operator -= (int ot) { return *this = *this - ot; }
    mint operator *= (int ot) { return *this = *this * ot; }
    operator int () const { return x; }
};

typedef pair<mint, mint> pmm;
pmm operator + (pmm p, pmm q) { return pmm(q.first*p.first, q.first*p.second+q.second); }

namespace Treap
{
    mt19937 rng(1557);
    int rnd() { return uniform_int_distribution<int>()(rng); }

    struct Node
    {
        int pr, sz;
        int par, lc, rc;

        // val : value stored in node, sum : query value of subtree
        // lazy : lazy value to be applied to subtree of node (already applied to val, sum)
        mint val, sum;
        bool rev;
        pmm lazy;

        Node(int x)
        {
            pr=rnd();
            sz=1;
            par=lc=rc=0;

            // your code goes here
            val=sum=x;
            rev=false;
            lazy=pmm(1, 0);
        }

        Node()
        {
            pr=sz=par=lc=rc=0;
            val=sum=0;
            rev=false;
            lazy=pmm(0, 0);
        }
    };

    struct Treap
    {
        Treap() { NS=vector<Node>(1); }
        int newNode(int x) { NS.push_back(Node(x)); return NS.size()-1; }

        // root must be initialized
        // NS[0] : NIL node
        int root;
        vector<Node> NS;

        // Recalculate value of node from lc, rc
        // lazy must be empty
        // changes sz, sum
        void recalc(int node)
        {
            if(node==0) return;
            int l=NS[node].lc, r=NS[node].rc;
            NS[node].sz=NS[l].sz+NS[r].sz+1;

            NS[node].sum=NS[node].val+NS[l].sum+NS[r].sum;
        }

        // Apply update value upd to subtree of node
        // update to node itself (val, sum), and to lazy value (lazy)
        // changes lazy, val, sum
        void apply(int node, bool rev, pmm lazy)
        {
            if(node==0) return;

            NS[node].rev^=rev;
            NS[node].lazy=NS[node].lazy+lazy;

            if(rev) swap(NS[node].lc, NS[node].rc);
            NS[node].val=lazy.first*NS[node].val+lazy.second;
            NS[node].sum=lazy.first*NS[node].sum+lazy.second*NS[node].sz;
        }

        // Propagate lazy value to lc, rc, and initialize lazy
        // should be called before going down to children
        // changes lazy
        void prop(int node)
        {
            if(node==0) return;

            apply(NS[node].lc, NS[node].rev, NS[node].lazy);
            apply(NS[node].rc, NS[node].rev, NS[node].lazy);
            NS[node].rev=false;
            NS[node].lazy=pmm(1, 0);
        }

        // Merge two consecutive trees rooted at l, r
        int merge(int l, int r)
        {
            if(l==0 || r==0) return l+r;
            if(NS[l].pr>NS[r].pr)
            {
                prop(l);
                int t=merge(NS[l].rc, r);
                NS[t].par=l;
                NS[l].rc=t;
                recalc(l);
                return l;
            }
            else
            {
                prop(r);
                int t=merge(l, NS[r].lc);
                NS[t].par=r;
                NS[r].lc=t;
                recalc(r);
                return r;
            }
        }

        // Split tree rooted at node into two trees of size k, sz-k
        pii split(int node, int k)
        {
            if(node==0) return {0, 0};
            assert(0<=k && k<=NS[node].sz);
            prop(node);

            if(k<=NS[NS[node].lc].sz)
            {
                auto [l, r]=split(NS[node].lc, k);
                NS[node].lc=r;
                NS[r].par=node;
                NS[l].par=0;
                recalc(node);
                return {l, node};
            }
            else
            {
                auto [l, r]=split(NS[node].rc, k-NS[NS[node].lc].sz-1);
                NS[node].rc=l;
                NS[l].par=node;
                NS[r].par=0;
                recalc(node);
                return {node, r};
            }
        }

        // ================================ Essential functions ENDS here ================================

        // Find kth node in subtree of node
        int find_kth(int node, int k)
        {
            prop(node);
            if(NS[NS[node].lc].sz>=k) return find_kth(NS[node].lc, k);
            if(k==NS[NS[node].lc].sz+1) return node;
            return find_kth(NS[node].rc, k-NS[NS[node].lc].sz-1);
        }
        // Find kth node of the tree
        int find_kth(int k) { return find_kth(root, k); }

        // Insert node x after the kth node of tree
        void insert(int k, int x)
        {
            assert(0<=k && k<=NS[root].sz);
            auto [a, b] = split(root, k);
            root = merge(a, x);
            root = merge(root, b);
        }

        // Erase kth node of tree
        void erase(int k)
        {
            assert(1<=k && k<=NS[root].sz);
            auto [a, d] = split(root, k-1);
            auto [b, c] = split(d, 1);
            root = merge(a, c);
        }

        // Update val to range [l, r]
        void update(int l, int r, bool rev, pmm lazy)
        {
            auto [d, c] = split(root, r);
            auto [a, b] = split(d, l-1);
            apply(b, rev, lazy);
            root = merge(a, b);
            root = merge(root, c);
        }

        // Query range [l, r]
        Node query(int l, int r)
        {
            auto [d, c] = split(root, r);
            auto [a, b] = split(d, l-1);
            Node ret = NS[b];
            root = merge(a, b);
            root = merge(root, c);
            return ret;
        }
    };
}

int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    Treap::Treap T;

    for(int i=1; i<=N; i++)
    {
        int x;
        scanf("%d", &x);
        if(i==1) T.root=T.newNode(x);
        else T.root=T.merge(T.root, T.newNode(x));
    }

    while(Q--)
    {
        int t;
        scanf("%d", &t);
        if(t==0)
        {
            int p, x;
            scanf("%d%d", &p, &x);
            T.insert(p, T.newNode(x));
        }
        else if(t==1)
        {
            int p;
            scanf("%d", &p); p++;
            T.erase(p);
        }
        else if(t==2)
        {
            int l, r;
            scanf("%d%d", &l, &r); l++;
            T.update(l, r, true, pmm(1, 0));
        }
        else if(t==3)
        {
            int l, r, x, y;
            scanf("%d%d%d%d", &l, &r, &x, &y); l++;
            T.update(l, r, false, pmm(x, y));
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r); l++;
            printf("%d\n", T.query(l, r).sum.x);
        }
    }
}