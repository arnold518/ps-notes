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