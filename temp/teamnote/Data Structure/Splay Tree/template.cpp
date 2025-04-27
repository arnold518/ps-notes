namespace SplayTree
{
    struct Node
    {
        int sz;
        int par, lc, rc;

        // val : value stored in node, sum : query value stored in node
        // lazy : lazy value to be applied to subtree of node (already applied to val, sum)
        ll val, sum;
        ll lazy;

        Node(ll x) {}
        Node() {}
    };

    struct SplayTree
    {
        SplayTree() { NS=vector<Node>(1); root=0; }
        int newNode(ll x) { NS.push_back(Node(x)); return NS.size()-1; }

        // NS[0] : NIL node
        int root;
        vector<Node> NS;

        // Recalculate value of node from lc, rc
        // lazy must be empty
        // changes sz, sum
        void recalc(int node) {}

        // Apply update value upd to subtree of node
        // update to node itself (val, sum), and to lazy value (lazy)
        // changes lazy, val, sum
        void apply(int node, ll upd) {}

        // Propagate lazy value to lc, rc, and initialize lazy
        // should be called before going down to children
        // changes lazy
        void prop(int node) {}

        // Propagates all ancestors of x
        void prop_anc(int x)
        
        // Rotate x with its parent
        void rotate(int x) {}

        // Make x the root of tree
        // ammortized O(logN), should be called after consuming time to visit any internal node
        void splay(int x) {}

        // Find kth node in subtree of node
        int find_kth(int node, int k) {}
        // Find kth node of the tree, and make it root
        void find_kth(int k) {}

        // Insert node x after the kth node in subtree of node
        void insert(int node, int k, int x) {}
        // Insert node x after the kth node of tree, and make it root
        void insert(int k, int x) {}

        // Erase root of tree
        void erase() {}

        // Merge [l, r]th nodes into subtree of NS[NS[root].lc].rc, and return it
        int interval(int l, int r) {}

        // Update val to range [l, r]
        void update(int l, int r, ll val) {}
        
        // Query range [l, r]
        Node query(int l, int r) {}
    };
}