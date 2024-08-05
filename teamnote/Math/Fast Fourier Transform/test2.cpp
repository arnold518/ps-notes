// https://judge.yosupo.jp/problem/convolution_mod_1000000007

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

typedef __int128 dll;

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
	vector<dll> multiply(vector<int> F, vector<int> G)
    {
        int N=1;
        while(N<F.size()+G.size()-1) N<<=1;
        vector<cpx> CF(N), CG(N);
        for(int i=0; i<F.size(); i++) CF[i]=cpx(F[i], 0);
        for(int i=0; i<G.size(); i++) CG[i]=cpx(G[i], 0);
        dft(CF, false); dft(CG, false);
        for(int i=0; i<N; i++) CF[i]*=CG[i];
        dft(CF, true);
        vector<dll> ret(F.size()+G.size()-1);
        for(int i=0; i<ret.size(); i++) ret[i]=(dll)round(CF[i].real());
        return ret;
    }

    const int D = 4e4; // sqrt(MAXV)
    // Multiplies polynomial F, G (MAXV is big)
    // MAXV * MAXV * N <= long_range
    // D * D * N = MAXV * N <= double_range / 2
    vector<dll> multiply2(vector<int> F, vector<int> G)
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
        vector<dll> ret(F.size()+G.size()-1);
        for(int i=0; i<ret.size(); i++) ret[i]=(dll)round(R1[i].real())*D*D + (dll)round(R2[i].real())*D + (dll)round(R3[i].real());
        return ret;
    }
};

int main()
{
    FFT::init();

    int N, M;
    scanf("%d%d", &N, &M);
    vector<int> A, B; vector<dll> C;
    for(int i=1; i<=N; i++)
    {
        int t;
        scanf("%d", &t);
        A.push_back(t);
    }
    for(int i=1; i<=M; i++)
    {
        int t;
        scanf("%d", &t);
        B.push_back(t);
    }
    C=FFT::multiply2(A, B);
    
    const int MOD = 1e9+7;
    for(auto it : C) printf("%d ", (int)(it%MOD));
    printf("\n");
}