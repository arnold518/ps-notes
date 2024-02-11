#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

namespace KMP
{
    // Get failure function of S
    // S is 1-based (leading "?")
    // getFail(S = "?ababca") = [-1, 0, 0, 1, 2, 0, 1]
    vector<int> getFail(string S)
    {
        int N=S.size()-1;
        vector<int> fail(N+1);

        fail[0]=-1;
        for(int i=1; i<=N; i++)
        {
            int j=fail[i-1];
            while(j>=0 && S[j+1]!=S[i]) j=fail[j];
            fail[i]=j+1;
        }
        return fail;
    }

    // Find occurences of T in S (ending position)
    // S, T is 1-based (leading "?")
    // KMP(S = "?aabcbabaaa", T = "?aa") = [2, 9, 10]
    vector<int> KMP(string S, string T)
    {
        int N=S.size()-1, M=T.size()-1;
        vector<int> fail = getFail(T);
        vector<int> ans;

        for(int i=1, j=0; i<=N; i++)
        {
            while(j>=0 && T[j+1]!=S[i]) j=fail[j];
            j++;
            if(j==M) ans.push_back(i), j=fail[j];
        }
        return ans;
    }
}

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
        Node()
        {
            par=fail=suf=-1;
            chd=vector<int>(26, -1);
        }
    };

    int root;
    vector<Node> NS;

    // Maximum size of NS is |SV[0]|+|SV[1]|+...
    int newNode()
    {
        NS.push_back(Node());
        return NS.size()-1;
    }

    // Make trie of dictionary SV, and determine par[v], fail[v], suf[v] for all nodes
    // SV[0], SV[1], ... is 0-based
    void makeTrie(vector<string> SV)
    {
        root=newNode();
        NS[root].par=root; NS[root].fail=root; NS[root].suf=root;

        for(auto &S : SV)
        {
            int now=root;
            for(auto c : S)
            {
                if(NS[now].chd[c-'a']==-1)
                {
                    int nxt=NS[now].chd[c-'a']=newNode();
                    NS[nxt].par=now;
                }
                now=NS[now].chd[c-'a'];
            }
            NS[now].suf=now;
        }

        queue<int> Q;
        Q.push(root);
        while(!Q.empty())
        {
            int now=Q.front(); Q.pop();
            for(int i=0; i<26; i++) if(NS[now].chd[i]!=-1)
            {
                int nxt=NS[now].chd[i];
                if(now==root) NS[nxt].fail=root;
                else
                {
                    int p;
                    for(p=NS[now].fail; p!=root; p=NS[p].fail) if(NS[p].chd[i]!=-1) break;
                    if(NS[p].chd[i]==-1) NS[nxt].fail=root;
                    else NS[nxt].fail=NS[p].chd[i];
                }

                if(NS[nxt].suf==-1) NS[nxt].suf=NS[NS[nxt].fail].suf;
                Q.push(nxt);
            }
        }
    }

    // Find occurences of TV[0], TV[1], ... in S (ending position)
    // S, TV[0], TV[1], ... is 0-based
    // AhoCorasick(S = "mississippi", TV = ["ss", "sis", "ippi", "pp"]) = [3, 5, 6, 9, 10]
    vector<int> AhoCorasick(string S, vector<string> TV)
    {
        vector<int> ans;
        makeTrie(TV);

        int now=root;
        for(int i=0; i<S.size(); i++)
        {
            for(; now!=root && NS[now].chd[S[i]-'a']==-1; now=NS[now].fail);
            if(NS[now].chd[S[i]-'a']!=-1) now=NS[now].chd[S[i]-'a'];

            // now is matching node in trie with S[0...i]
            // your code goes here

            if(NS[now].suf!=root) ans.push_back(i);
        }
        return ans;
    }
}

// =======================================================================================================

void test_kmp()
{
    vector<int> V;
    V = KMP::getFail("?ababca");
    assert(V == vector<int>({-1, 0, 0, 1, 2, 0, 1}));

    V = KMP::KMP("?aabcbabaaa", "?aa");
    assert(V == vector<int>({2, 9, 10}));
}

void test_aho_corasick()
{
    vector<int> V;
    
    V = AhoCorasick::AhoCorasick("mississippi", {"ss", "sis", "ippi", "pp"});
    assert(V == vector<int>({3, 5, 6, 9, 10}));
}

int main()
{
    test_KMP();
}