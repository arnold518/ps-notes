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

namespace Z
{
    // Get Z function of S
    // Z[i] = LCP(S[i...], S)
    // S is 1-based (leading "?")
    // getZ(S = "?abacaba") = [-, 0, 0, 1, 0, 3, 0, 1]
    vector<int> getZ(string S)
    {
        int N=S.size()-1;
        vector<int> Z(N+1);

        int pos=1;
        for(int i=2; i<=N; i++)
        {
            if(i<=pos+Z[pos]-1) Z[i]=min(pos+Z[pos]-i, Z[i-pos+1]);
            while(i+Z[i]<=N && S[i+Z[i]]==S[Z[i]+1]) Z[i]++;
            if(Z[pos]+pos<Z[i]+i) pos=i;
        }
        return Z;
    }

    // Get LCP of all suffixes in S with T
    // F[i] = LCP(S[i...], T)
    // S, T is 1-based (leading "?")
    // matchZ(S = "?abacabacaba", T = "?abacaba") = [-, 7, 0, 1, 0, 7, 0, 1, 0, 3, 0, 1]
    vector<int> matchZ(string S, string T)
    {
        int N=S.size()-1, M=T.size()-1;
        vector<int> Z = getZ(T);
        vector<int> F(N+1);

        int pos=0;
        for(int i=1; i<=N; i++)
        {
            if(i<=pos+F[pos]-1) F[i]=min(pos+F[pos]-i, Z[i-pos+1]);
            while(i+F[i]<=N && F[i]+1<=M && S[i+F[i]]==T[F[i]+1]) F[i]++;
            if(pos+F[pos]<i+F[i]) pos=i;
        }
        return F;
    }
}

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

namespace SA_LCP
{
    // uncomment code to use cmp
    
    // MAXN must be defined
    const int MAXN = 5e5;

    // SA[i] : starting position of i-th suffix when sorted
    // R[i] : lexicographic order of i-th suffix, R[SA[i]]=i
    // LCP[i] : LCP(S[SA[i-1]...], S[SA[i]...])
    int SA[MAXN+10], R[MAXN+10], LCP[MAXN+10];
    
    // R2[i][j] : R[i] when d = 1<<j
    int R2[MAXN+10][21];

    // Get Suffix array, LCP array of S
    // Fill SA[i], R[i], LCP[i]
    // S is 1-based (leading "?")
    // getSA("?banana") =>
    //  SA = [-, 6, 4, 2, 1, 5, 3]
    //   R = [-, 4, 3, 6, 2, 5, 1]
    // LCP = [-, -, 1, 3, 0, 0, 2]
    void SA_LCP(string S)
    {
        int N=S.size()-1, t=1;
        vector<int> F(N+1), T(N+1);

        for(int i=1; i<=N; i++) SA[i]=i;
        sort(SA+1, SA+N+1, [&](const int &p, const int &q) { return S[p]<S[q]; });
        for(int i=1; i<=N; i++) R[SA[i]]=R[SA[i-1]]+(i==1 || S[SA[i]]!=S[SA[i-1]]);
        for(int i=1; i<=N; i++) R2[i][0]=R[i];

        for(int d=1; d<=N; d<<=1, t++)
        {
            if(R[SA[N]]==N) break;

            F[0]=d;
            for(int i=d+1; i<=N; i++) F[R[i]]++; 
            for(int i=1; i<=N; i++) F[i]+=F[i-1];
            for(int i=1; i<=N; i++) SA[F[(i+d>N ? 0 : R[i+d])]--]=i;
            for(int i=0; i<=N; i++) F[i]=0;

            for(int i=1; i<=N; i++) F[R[i]]++; 
            for(int i=1; i<=N; i++) F[i]+=F[i-1];
            for(int i=1; i<=N; i++) T[i]=SA[i];
            for(int i=N; i>=1; i--) SA[F[R[T[i]]]--]=T[i];
            for(int i=0; i<=N; i++) F[i]=0;

            for(int i=1; i<=N; i++) T[i]=R[i];
            for(int i=1; i<=N; i++)
            {
                R[SA[i]]=R[SA[i-1]];
                if(i==1 || T[SA[i]]!=T[SA[i-1]]) R[SA[i]]++;
                else
                {
                    int p=(SA[i-1]+d>N ? 0 : T[SA[i-1]+d]);
                    int q=(SA[i]+d>N ? 0 : T[SA[i]+d]);
                    if(p!=q) R[SA[i]]++;
                }
            }
            for(int i=1; i<=N; i++) R2[i][t]=R[i];
        }
        for(; t<=20; t++) for(int i=1; i<=N; i++) R2[i][t]=R[i];
        
        for(int i=1, k=0; i<=N; i++)
        {
            if(R[i]>1)
            {
                for(; i+k<=N && SA[R[i]-1]+k<=N && S[i+k]==S[SA[R[i]-1]+k]; k++);
                LCP[R[i]]=k;
            }
            if(k) k--;
        }
    }

    // Compare two substrings, return true if S[l1 ... r1] < S[l2 ... r2]
    bool cmp(int l1, int r1, int l2, int r2)
    {
        if(l2>r2) return false;
        if(l1>r1) return true;
        int len=min(r1-l1+1, r2-l2+1), t=__lg(len);
        if(R2[l1][t]!=R2[l2][t]) return R2[l1][t] < R2[l2][t];
        if(R2[l1+len-(1<<t)][t]!=R2[l2+len-(1<<t)][t]) return R2[l1+len-(1<<t)][t] < R2[l2+len-(1<<t)][t];
        return (r1-l1) < (r2-l2);
    }
}

namespace CHT
{
    typedef __int128 dll;
    struct Line { ll a, b; };
    struct Frac
    {
        ll u, d;
        Frac(ll _u, ll _d) : u(_u), d(_d) { if(d<0) u=-u, d=-d; }
        bool operator < (const Frac &ot) const { return (dll)u*ot.d < (dll)ot.u*d; }
        bool operator > (const Frac &ot) const { return (dll)u*ot.d > (dll)ot.u*d; }
    };
    ll divfloor(ll u, ll d) { return u/d - ((u^d)<0 && u%d); }
    ll divceil(ll u, ll d) { return u/d + ((u^d)>0 && u%d); }

    // min/max : ?, slope : ?, dir : ?
    struct CHT
    {
        // Get cross point of line p, q
        // If all queries are integer, change 'Frac' to 'div'
        Frac cross(const Line &p, const Line &q) { return Frac(p.b-q.b, q.a-p.a); } // dir + : divfloor, dir - : divceil
        deque<Line> V;
    
        // Insert line p = ax+b
        // b must be increasing (or decreasing) ('slope')
        // cross(V[i-1], V[i]) < (or >) cross(V[i], V[i+1]) ('dir')
        void push(Line p)
        {
            if(!V.empty() && V.back().a==p.a)
            {
                if(V.back().b <= p.b) return; // min : <= , max : >=
                V.pop_back();
            }
            while(V.size()>1 && !(cross(V[V.size()-2], V[V.size()-1]) < cross(V[V.size()-1], p))) V.pop_back(); // dir + : <, dir - : >
            V.push_back(p);
        }
    
        // Get min (or max) value at x in O(logN)
        ll query(ll x)
        {
            assert(!V.empty());
            int lo=0, hi=V.size();
            while(lo+1<hi)
            {
                int mid=lo+hi>>1;
                if(cross(V[mid-1], V[mid]) < Frac(x, 1)) lo=mid; // dir + : <, dir - : >
                else hi=mid;
            }
            return V[lo].a*x+V[lo].b;
        }
    
        // Get min (or max) value at x in ammortized O(1)
        // x must be increasing (or decreasing) ('dir')
        ll query2(ll x)
        {
            assert(!V.empty());
            while(V.size()>1 && cross(V[0], V[1]) < Frac(x, 1)) V.pop_front(); // dir + : <, dir - : >
            return V[0].a*x+V[0].b;
        }
    };
}

namespace Alien
{
    // MAXN must be defined
    const int MAXN = 5e5;
    int N;
    
    // dp[i] : optimal dp value of i
    // cnt[i] : how much transitions were used in optimal dp[i]
    // memo[i] : previous transition position from i
    // V : restored optimal solution
    ll dp[MAXN+10];
    int cnt[MAXN+10], memo[MAXN+10];
    vector<int> V;

    void init(int _N)
    {
        N=_N;
    }

    // For given lambda, calculate dp, cnt, memo, V
    // dp[i] = min(or max)_{j<i} (dp[j] + cost(j, i)*2 - lambda) 
    void solve(ll lambda)
    {
        // initialize dp, cnt, memo, V, (other data structures)
        for(int i=0; i<=N; i++) dp[i]=cnt[i]=memo[i]=0;
        V.clear();

        for(int i=1; i<=N; i++)
        {
            // get_opt(i), cost(p, q) must be implemented
            // opt = argmin(or max)_{j<i} (dp[j] + cost(j, i)*2)
            // your code goes here
            int opt = 0;
            for(int j=0; j<i; j++) if(dp[opt]+(ll)(i-opt)*(i-opt)*2 > dp[j]+(ll)(i-j)*(i-j)*2) opt=j;
            dp[i] = dp[opt] + (ll)(i-opt)*(i-opt)*2 - lambda; // Don't forget *2
            cnt[i] = cnt[opt]+1;
            memo[i] = opt;
        }

        for(int i=N; i>0;)
        {
            V.push_back(i);
            i=memo[i];
        }
        V.push_back(0);
        reverse(V.begin(), V.end());
    }

    // Get optimal dp[N][K] for given K
    // Returns (answer, restored solution)
    // dp[i][k] = min(or max)_{j<i} (dp[j][k-1] + cost(j, i))
    pair<ll, vector<int>> alien(int K)
    {
        // lambda equals slope
        // minimum : K increase, lambda increase
        // maximum : k increase, lambda decrease

        ll lo=-1e18, hi=1e18; // range for lambda is [2*lo+1, 2*hi+1]
        while(lo+1<hi)
        {
            ll mid=lo+hi>>1;
            solve(2*mid+1);
            if(K <= cnt[N]) hi=mid; // min : <= , max : >=
            else lo=mid;
        }
        
        vector<int> P1, P2, ansV;
        solve(2*lo+1); P1=V;
        solve(2*hi+1); P2=V;
        if(P1.size()>P2.size()) swap(P1, P2);

        if(P1.size()-1==K) ansV=P1;
        else if(P2.size()-1==K) ansV=P2;
        else
        {
            assert(P1.size()-1<K && K<P2.size()-1);
            int x=K+1-P1.size();
            for(int i=0; i+1<P1.size() && i+x+1<P2.size(); i++)
            {
                if(P1[i]<=P2[i+x] && P2[i+x+1]<=P1[i+1])
                {
                    for(int j=0; j<=i+x; j++) ansV.push_back(P2[j]);
                    for(int j=i+1; j<P1.size(); j++) ansV.push_back(P1[j]);
                    break;
                }
            }
        }
        assert(ansV.size()==K+1);

        solve(2*hi);
        ll ans=dp[N]/2+hi*K;
        return {ans, ansV};
    }
}

namespace FFT
{
    // double (double_range : 2^52) <=> long double (double_range : 2^63)
    // ll (long_range : 2^63) <=> dll (long_range : 2^128)

	typedef complex<double> cpx;
    const double PI = acos((double)-1);

    const int MAXB = 21;
    const int MAXN = (1<<MAXB);

    vector<cpx> W;
    vector<int> rev;
    void init()
    {
        W=vector<cpx>(MAXN);
        rev=vector<int>(MAXN);
        for(int i=0; i<MAXN; i++) W[i]=cpx(cos(PI/MAXN*i), sin(PI/MAXN*i));
        for(int i=0; i<MAXN; i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(MAXB-1));
    }

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
	void dft(vector<cpx> &A, bool inv)
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
                    cpx w=W[MAXN/i*k];
                    if(inv) w=conj(w);
                    cpx a=A[j+k], b=A[j+k+i]*w;
                    A[j+k]=a+b; A[j+k+i]=a-b;
                }
            }
        }
        if(inv) for(int i=0; i<N; i++) A[i]/=N;
    }

    // Multiplies polynomial F, G (MAXV is small)
    // MAXV * MAXV * N <= long_range
    // MAXV * MAXV * N <= double_range / 2
    // multiply([1, 2, 3], [4, 5, 6, 7, 8]) = [4, 13, 28, 34, 40, 37, 24]
	vector<ll> multiply(vector<int> F, vector<int> G)
    {
        int N=1;
        while(N<F.size()+G.size()-1) N<<=1;
        vector<cpx> CF(N), CG(N);
        for(int i=0; i<F.size(); i++) CF[i]=cpx(F[i], 0);
        for(int i=0; i<G.size(); i++) CG[i]=cpx(G[i], 0);
        dft(CF, false); dft(CG, false);
        for(int i=0; i<N; i++) CF[i]*=CG[i];
        dft(CF, true);
        vector<ll> ret(F.size()+G.size()-1);
        for(int i=0; i<ret.size(); i++) ret[i]=(ll)round(CF[i].real());
        return ret;
    }

    const int D = 5e4; // sqrt(MAXV)
    // Multiplies polynomial F, G (MAXV is big)
    // MAXV * MAXV * N <= long_range
    // D * D * N = MAXV * N <= double_range / 2
    // multiply2([1, 2, 3], [4, 5, 6, 7, 8]) = [4, 13, 28, 34, 40, 37, 24]
    vector<ll> multiply2(vector<int> F, vector<int> G)
    {
        int N=1;
        while(N<F.size()+G.size()-1) N<<=1;
        vector<cpx> P(N), Q(N), R1(N), R2(N), R3(N);
        for(int i=0; i<F.size(); i++) P[i]=cpx(F[i]/D, F[i]%D);
        for(int i=0; i<G.size(); i++) Q[i]=cpx(G[i]/D, G[i]%D);
        dft(P, false);
        dft(Q, false);
        for(int i=0; i<N; i++)
        {
            cpx p1, p2, q1, q2;
            int j=(N-i)%N;
            p1=(P[i]+conj(P[j]))*cpx(0.5, 0);
            p2=(P[i]-conj(P[j]))*cpx(0, -0.5);
            q1=(Q[i]+conj(Q[j]))*cpx(0.5, 0);
            q2=(Q[i]-conj(Q[j]))*cpx(0, -0.5);
            R1[i]=p1*q1;
            R2[i]=p1*q2+p2*q1;
            R3[i]=p2*q2;
        }
        dft(R1, true);
        dft(R2, true);
        dft(R3, true);
        vector<ll> ret(F.size()+G.size()-1);
        for(int i=0; i<ret.size(); i++) ret[i]=(ll)round(R1[i].real())*D*D + (ll)round(R2[i].real())*D + (ll)round(R3[i].real());
        return ret;
    }
};

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

void test_z()
{
    vector<int> V;

    V = Z::getZ("?abacaba");
    assert(V == vector<int>({0, 0, 0, 1, 0, 3, 0, 1}));
    
    V = Z::matchZ("?abacabacaba", "?abacaba");
    assert(V == vector<int>({0, 7, 0, 1, 0, 7, 0, 1, 0, 3, 0, 1}));
}

void test_manacher()
{
    vector<int> V;

    V = Manacher::manacher("?abcbab");
    assert(V == vector<int>({0, 0, 0, 2, 0, 1, 0}));
}

void test_sa_lcp()
{
    SA_LCP::SA_LCP("?banana");

    assert(vector<int>(SA_LCP::SA+1, SA_LCP::SA+7) == vector<int>({6, 4, 2, 1, 5, 3}));
    assert(vector<int>(SA_LCP::R+1, SA_LCP::R+7) == vector<int>({4, 3, 6, 2, 5, 1}));
    assert(vector<int>(SA_LCP::LCP+2, SA_LCP::LCP+7) == vector<int>({1, 3, 0, 0, 2}));

    assert(SA_LCP::cmp(2, 3, 4, 6) == true); // "an" < "ana"
    assert(SA_LCP::cmp(2, 4, 3, 5) == true); // "ana" < "nan"
    assert(SA_LCP::cmp(1, 6, 2, 4) == false); // "banana" >= "ana"
    assert(SA_LCP::cmp(2, 4, 4, 6) == false); // "ana" >= "ana"
}

void test_cht()
{
    // min/max : min, slope : -, dir : +
    CHT::CHT cht;
    
    cht.push({0, 1});
    cht.push({-1, -1});
    cht.push({-2, -1});

    assert(cht.query(-2) == 1);
    assert(cht.query(-1) == 0);
    assert(cht.query(0) == -1);
    assert(cht.query(1) == -3);
    
    assert(cht.query2(-2) == 1);
    assert(cht.query2(-1) == 0);
    assert(cht.query2(0) == -1);
    assert(cht.query2(1) == -3);
}

void test_alien()
{
    // min, cost(j, i) = (i-j)*(i-j)
    Alien::init(15);
    auto [ans, ansV] = Alien::alien(4);
    
    assert(ans == 57 && ansV == vector<int>({0, 3, 7, 11, 15}));
}

void test_fft()
{
    vector<ll> V;             

    FFT::init();

    V = FFT::multiply({1, 2, 3}, {4, 5, 6, 7, 8});
    assert(V == vector<ll>({4, 13, 28, 34, 40, 37, 24}));

    int D = 1e8; ll D2 = (ll)D*D;
    V = FFT::multiply2({1*D, 2*D, 3*D}, {4*D, 5*D, 6*D, 7*D, 8*D});
    assert(V == vector<ll>({4*D2, 13*D2, 28*D2, 34*D2, 40*D2, 37*D2, 24*D2}));
}

void test_ntt()
{
    vector<mint> V;             

    // MOD = 998244353, G = 3
    NTT::init();

    V = vector<mint>({1, 2, 3, 4});
    NTT::dft(V, false);
    assert(V == vector<mint>({10, 173167434, 998244351, 825076915}));

    V = vector<mint>({10, 173167434, 998244351, 825076915});
    NTT::dft(V, true);
    assert(V == vector<mint>({1, 2, 3, 4}));

    V = NTT::multiply({1, 2, 3}, {4, 5, 6, 7, 8});
    assert(V == vector<mint>({4, 13, 28, 34, 40, 37, 24}));
}

int main()
{
    test_kmp();
    test_aho_corasick();
    test_z();
    test_manacher();
    test_sa_lcp();

    test_cht();
    test_alien();

    test_fft();
    test_ntt();
}