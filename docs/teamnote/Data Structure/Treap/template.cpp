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
        ll val, sum;
        ll lazy;

        Node(ll x) {}
        Node() {}
    };

    struct Treap
    {
        Treap() { NS=vector<Node>(1); }
        int newNode(ll x) { NS.push_back(Node(x)); return NS.size()-1; }

        // root must be initialized
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

        // Merge two consecutive trees rooted at l, r
        int merge(int l, int r) {}

        // Split tree rooted at node into two trees of size k, sz-k
        pii split(int node, int k) {}

        // ================================ Essential functions ENDS here ================================

        // Find kth node in subtree of node
        int find_kth(int node, int k) {}
        // Find kth node of the tree
        int find_kth(int k) {}

        // Insert node x after the kth node of tree
        void insert(int k, int x) {}

        // Erase kth node of tree
        void erase(int k) {}

        // Update val to range [l, r]
        void update(int l, int r, ll val) {}

        // Query range [l, r]
        Node query(int l, int r) {}
    };
}