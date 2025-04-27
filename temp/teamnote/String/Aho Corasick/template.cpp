namespace AhoCorasick
{
    // par[v] = parent of node v
    // fail[v] = failure link of node v
    // suf[v] = suffix link of node v
    // chd[v] = children of node v in trie
    struct Node
    {
        int par, fail, suf;
        vector<int> chd;
    };

    int root;
    vector<Node> NS;
    int newNode() {}

    // Make trie of dictionary SV, and determine par[v], fail[v], suf[v] for all nodes
    // SV[0], SV[1], ... is 0-based
    void makeTrie(vector<string> SV) {}

    // Find occurences of TV[0], TV[1], ... in S (ending position)
    // S, TV[0], TV[1], ... is 0-based
    vector<int> AhoCorasick(string S, vector<string> TV) {}
}