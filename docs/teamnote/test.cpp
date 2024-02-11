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

    // Find occurences of T in S
    // S, T is 1-based (leading "?")
    // KMP(S = "?aabcbabaaa", T = "?aa") = [1, 8, 9]
    vector<int> KMP(string S, string T)
    {
        int N=S.size()-1, M=T.size()-1;
        vector<int> fail = getFail(T);
        vector<int> ans;

        for(int i=1, j=0; i<=N; i++)
        {
            while(j>=0 && T[j+1]!=S[i]) j=fail[j];
            j++;
            if(j==M) ans.push_back(i-M+1), j=fail[j];
        }
        return ans;
    }
}

int main()
{
    {
        vector<int> V;
        V = KMP::getFail("?ababca");
        assert(V == vector<int>({-1, 0, 0, 1, 2, 0, 1}));

        V = KMP::KMP("?aabcbabaaa", "?aa");
        assert(V == vector<int>({1, 8, 9}));
    }
}