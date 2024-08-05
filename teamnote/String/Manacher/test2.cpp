// https://www.acmicpc.net/problem/13275

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

namespace Manacher
{
    // Get maximum radius of palindrome at each center
    // S[i-P[i] ... i+P[i]] is palindrome
    // S is 1-based (leading "?")
    // manacher(S = "?abcbab") = [-, 0, 0, 2, 0, 1, 0]
    vector<int> manacher(string S)
    {
        int N=S.size()-1;
        vector<int> P(N+1);

        int pos=0;
        for(int i=1; i<=N; i++)
        {
            if(i<=pos+P[pos]) P[i]=min(pos+P[pos]-i, P[pos+pos-i]);
            while(i+P[i]+1<=N && i-P[i]-1>=1 && S[i-P[i]-1]==S[i+P[i]+1]) P[i]++;
            if(P[pos]+pos<P[i]+i) pos=i;
        }
        return P;
    }
}

int main()
{
    int N;
    string S, S2;
    cin>>S;
    N=S.size();

    S2="?";
    for(auto c : S) S2+="!"+string(1, c);
    S2+="!";
    
    auto V = Manacher::manacher(S2);
    int ans=0;
    for(int i=2; i<=N+N; i++) ans=max(ans, V[i]);
    cout<<ans<<"\n";
}