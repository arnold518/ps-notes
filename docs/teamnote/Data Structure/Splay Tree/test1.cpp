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

namespace SplayTree
{
    struct Node
    {
        int sz;
        int par, lc, rc;
        
        // val : value stored in node, sum : query value stored in node
        // lazy : lazy value to be applied to subtree of node (already applied to val, sum)
        mint val, sum;
        bool rev;
        pmm lazy;

        Node(ll x)
        {
            sz=1;
            par=lc=rc=0;

            // your code goes here
            val=sum=x;
            rev=false;
            lazy=pmm(1, 0);
        }
        Node()
        {
            sz=par=lc=rc=0;
            val=sum=0;
            rev=false;
            lazy=pmm(0, 0);
        }
    };

    // MUST include leftmost, rightmost dummy elements
    struct SplayTree
    {
        SplayTree() { NS=vector<Node>(1); }
        int newNode(ll x) { NS.push_back(Node(x)); return NS.size()-1; }

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
        
        // Rotate x with its parent
        void rotate(int x)
        {
            assert(x!=0 && NS[x].par!=0);
            int p=NS[x].par, q;
            if(NS[p].lc==x)
            {
                NS[p].lc=q=NS[x].rc;
                NS[x].rc=p;
            }
            else
            {
                NS[p].rc=q=NS[x].lc;
                NS[x].lc=p;
            }
            NS[x].par=NS[p].par;
            NS[p].par=x;
            if(q) NS[q].par=p;
            if(p==root) root=x;
            else if(NS[NS[x].par].lc==p) NS[NS[x].par].lc=x;
            else NS[NS[x].par].rc=x;

            recalc(p);
            recalc(x);
        }

        // Make x the root of tree
        // ancestors of x must be propagated before
        // ammortized O(logN), should be called after consuming time to visit any internal node
        void splay(int x)
        {
            while(NS[x].par)
            {
                int p=NS[x].par, q=NS[p].par;
                if(q) rotate((NS[p].lc==x)==(NS[q].lc==p) ? p : x);
                rotate(x);
            }
            prop(root);
        }

        // Find kth node in subtree of node
        int find_kth(int node, int k)
        {
            assert(1<=k && k<=NS[node].sz);
            prop(node);
            if(k<=NS[NS[node].lc].sz) return find_kth(NS[node].lc, k);
            if(k==NS[NS[node].lc].sz+1) return node;
            return find_kth(NS[node].rc, k-NS[NS[node].lc].sz-1);
        }
        // Find kth node of the tree, and make it root
        void find_kth(int k) { splay(find_kth(root, k)); }

        // Insert node x after the kth node in subtree of node
        void insert(int node, int k, int x)
        {
            assert(0<=k && k<=NS[node].sz);
            prop(node);

            if(k<=NS[NS[node].lc].sz)
            {
                if(NS[node].lc==0)
                {
                    NS[node].lc=x;
                    NS[x].par=node;
                }
                else insert(NS[node].lc, k, x);
            }
            else
            {
                if(NS[node].rc==0)
                {
                    NS[node].rc=x;
                    NS[x].par=node;
                }
                else insert(NS[node].rc, k-NS[NS[node].lc].sz-1, x);
            }
            recalc(node);
        }
        // Insert node x after the kth node of tree, and make it root
        void insert(int k, int x) { insert(root, k, x); splay(x); }

        // Erase root of tree
        void erase()
        {
            prop(root);
            int p=NS[root].lc, q=NS[root].rc;
            root=p;
            NS[p].par=0;
            find_kth(NS[p].sz);
            NS[root].rc=q;
            NS[q].par=root;
            NS[root].par=0;
            recalc(root);
        }

        // Merge [l, r]th nodes into subtree of NS[NS[root].lc].rc, and return it
        int interval(int l, int r)
        {
            assert(1<l && r<NS[root].sz);
            find_kth(r+1);
            int x=root;
            root=NS[x].lc;
            NS[root].par=0;
            find_kth(l-1);
            NS[x].lc=root;
            NS[root].par=x;
            root=x;
            recalc(root);
            return NS[NS[root].lc].rc;
        }

        // Update val to range [l, r]
        void update(int l, int r, bool rev, pmm lazy)
        {
            assert(1<l && r<NS[root].sz);
            int p=interval(l, r);
            apply(p, rev, lazy);
            recalc(NS[p].par);
            recalc(root);
        }
        
        // Query range [l, r]
        Node query(int l, int r)
        {
            assert(1<l && r<NS[root].sz);
            int p=interval(l, r);
            return NS[p];
        }
    };
}

int main()
{
    int N, Q;
    scanf("%d%d", &N, &Q);
    SplayTree::SplayTree T;
    T.root=T.newNode(0);

    for(int i=1; i<=N; i++)
    {
        int x;
        scanf("%d", &x);
        T.insert(i, T.newNode(x));
    }
    T.insert(N+1, T.newNode(0));

    while(Q--)
    {
        int t;
        scanf("%d", &t);
        if(t==0)
        {
            int p, x;
            scanf("%d%d", &p, &x); p++;
            T.insert(p, T.newNode(x));
        }
        else if(t==1)
        {
            int p;
            scanf("%d", &p); p+=2;
            T.find_kth(p);
            T.erase();
        }
        else if(t==2)
        {
            int l, r;
            scanf("%d%d", &l, &r); l+=2; r++;
            T.update(l, r, true, pmm(1, 0));
        }
        else if(t==3)
        {
            int l, r, x, y;
            scanf("%d%d%d%d", &l, &r, &x, &y); l+=2; r++;
            T.update(l, r, false, pmm(x, y));
        }
        else
        {
            int l, r;
            scanf("%d%d", &l, &r); l+=2; r++;
            printf("%d\n", T.query(l, r).sum.x);
        }
    }
}