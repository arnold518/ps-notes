// https://judge.yosupo.jp/problem/convolution_mod

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// you should NOT put 'int' as left operand
// mint should be initialized with an integer in [0, MOD - 1].
// ex. mint x = (long long)1e18; << NOT GOOD
const int MOD = 998244353;
struct mint
{
    int x;
    mint(void) : x(0) {}
    mint(int _x) : x(_x) {}
    mint operator + (int ot) const { return x+ot>=MOD ? x+ot-MOD : x+ot; }
    mint operator - (void) const { return x ? MOD-x : 0; }
    mint operator - (int ot) const { return x < ot ? x+MOD-ot : x-ot; }
    mint operator * (int ot) const { return 1ll*x*ot%MOD; }
    mint operator += (int ot) { return *this = *this + ot; }
    mint operator -= (int ot) { return *this = *this - ot; }
    mint operator *= (int ot) { return *this = *this * ot; }
    operator int(void) const { return x; }
};

mint mpow(mint a, int x)
{
    mint ret=1;
    while(x)
    {
        if(x&1) ret=ret*a;
        a=a*a;
        x>>=1;
    }
    return ret;
}
mint inv(mint x) { return mpow(x, MOD-2); }

// mint must be included

namespace NTT
{
    const mint G = 3; // primitive root of MOD

    const int MAXB = 21;
    const int MAXN = (1<<MAXB); // MAXN must divide MOD-1

    vector<mint> W;
    vector<int> rev;
    void init()
    {
        W=vector<mint>(MAXN);
        rev=vector<int>(MAXN);
        W[0]=1; W[1]=mpow(G, (MOD-1)/MAXN);
        for(int i=2; i<MAXN; i++) W[i]=W[i-1]*W[1];
        for(int i=0; i<MAXN; i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(MAXB-1));
    }

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
    // dft([1, 2, 3, 4], false) = [10, 173167434, 998244351, 825076915]
    // dft([10, 173167434, 998244351, 825076915], true) = [1, 2, 3, 4]
	void dft(vector<mint> &A, bool inv)
    {
        int N=A.size(), B=__lg(N);

        for(int i=0; i<N; i++)
        {
            int r=rev[i<<(MAXB-B)];
            if(i<r) swap(A[i], A[r]);
        }

        for(int i=1; i<N; i<<=1)
        {
            for(int j=0; j<N; j+=i+i)
            {
                for(int k=0; k<i; k++)
                {
                    int t=MAXN/(i+i)*k;
                    if(inv && t) t=MAXN-t;
                    mint w=W[t];
                    mint a=A[j+k], b=A[j+k+i]*w;
                    A[j+k]=a+b; A[j+k+i]=a-b;
                }
            }
        }
        mint invN = mpow(N, MOD-2);
        if(inv) for(int i=0; i<N; i++) A[i]=A[i]*invN;
    }

    // Multiplies polynomial F, G
    // multiply([1, 2, 3], [4, 5, 6, 7, 8]) = [4, 13, 28, 34, 40, 37, 24]
	vector<mint> multiply(vector<mint> F, vector<mint> G)
    {
        int N=1;
        while(N<F.size()+G.size()-1) N<<=1;
        vector<mint> ret(F.size()+G.size()-1);
        F.resize(N); G.resize(N);
        dft(F, false); dft(G, false);
        for(int i=0; i<N; i++) F[i]*=G[i];
        dft(F, true);
        for(int i=0; i<ret.size(); i++) ret[i]=F[i];
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    NTT::init();
    int N, M;
    cin>>N>>M;
    vector<mint> F, G;
    for(int i=0; i<N; i++)
    {
        int a;
        cin>>a;
        F.push_back(a);
    }
    for(int i=0; i<M; i++)
    {
        int a;
        cin>>a;
        G.push_back(a);
    }
    vector<mint> V=NTT::multiply(F, G);
    for(auto it : V) cout<<(int)it<<" ";
    cout<<"\n";
}