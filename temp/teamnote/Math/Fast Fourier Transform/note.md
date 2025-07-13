# Fast Fourier Transform

## Problem

!!! property "Property 1"
    $$\omega_n=e^{\frac{2\pi i}{n}}=\cos\frac{2\pi}{n}+i\sin\frac{2\pi}{n}$$

    - $\omega_n^n=1$
    - $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$은 모두 서로 다르다.

!!! definition "Definition 1"
    다항식 $A(x)=\displaystyle \sum_{i=0}^{n-1}a_ix^i=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}$ 에 대한 DFT와 IDFT를 다음과 같이 정의한다.
    
    $DFT(a_0, a_1, \cdots, a_{n-1})=(A(\omega_n^0), A(\omega_n^1), \cdots, A(\omega_n^{n-1}))=(y_0, y_1, \cdots, y_{n-1})$

    $IDFT(y_0, y_1, \cdots, y_{n-1})=IDFT(A(\omega_n^0), A(\omega_n^1), \cdots, A(\omega_n^{n-1}))=(a_0, a_1, \cdots, a_{n-1})$

    ---

    $$
    DFT(a_0, a_1, \cdots, a_{n-1})=(A(\omega_n^0), A(\omega_n^1), \cdots, A(\omega_n^{n-1}))=(y_0, y_1, \cdots, y_{n-1})
    $$

    $$
    =
    \begin{bmatrix}
        \omega_n^{0 \cdot 0} & \omega_n^{0 \cdot 1} & \omega_n^{0 \cdot 2} & \dots & \omega_n^{0 \cdot (n-1)} \\
        \omega_n^{1 \cdot 0} & \omega_n^{1 \cdot 1} & \omega_n^{1 \cdot 2} & \dots & \omega_n^{1 \cdot (n-1)} \\
        \omega_n^{2 \cdot 0} & \omega_n^{2 \cdot 1} & \omega_n^{2 \cdot 2} & \dots & \omega_n^{2 \cdot (n-1)} \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        \omega_n^{(n-1) \cdot 0} & \omega_n^{(n-1) \cdot 1} & \omega_n^{(n-1) \cdot 2} & \dots & \omega_n^{(n-1) \cdot (n-1)} 
    \end{bmatrix}
    \begin{bmatrix}
        a_0 \\    
        a_1 \\
        a_2 \\
        \vdots \\
        a_{n-1}
    \end{bmatrix}
    =
    \begin{bmatrix}
        y_0 \\    
        y_1 \\
        y_2 \\
        \vdots \\
        y_{n-1}
    \end{bmatrix}
    $$

    ---

    $$
    \displaystyle y_j = \sum_{i=0}^{n-1} a_i \omega_n^{ij}
    \ \ \ \
    W=
    \begin{bmatrix}
        \omega_n^{ij}
    \end{bmatrix}_{0 \le i, j < n}
    $$

    $$
    \displaystyle a_j = \frac{1}{n}\sum_{i=0}^{n-1} y_i \omega_n^{-ij}
    \ \ \ \
    W^{-1}=
    \frac{1}{n}
    \begin{bmatrix}
        \omega_n^{-ij}
    \end{bmatrix}_{0 \le i, j < n}
    $$

구현에서 사용할 자료형에 따라 `double_range` (`double` / `long double`의 fraction 표현 범위), `long_range` (`long long` / `__int128`의 표현 범위)가 결정된다.

- **DFT / IDFT** : 배열 $A$가 주어질 때, $A$의 DFT / IDFT 배열을 구한다.
- **Convolution** : 다항식 $F(x)$, $G(x)$가 주어질 때, 다항식 곱 $(F \cdot G)(x)$를 구한다. (`MAXV * MAXV * N <= double_range`)
- **Convolution2** : 다항식 $F(x)$, $G(x)$가 주어질 때, 다항식 곱 $(F \cdot G)(x)$를 구한다. (`MAXV * N <= double_range`)

## Algorithm

- **DFT / IDFT**

    !!! definition "Definition 2"
        다항식 $A(x)$에서 짝수 번째 계수들을 모아 만든 다항식을 $A_0(x)$, 홀수 번째 계수들을 모아 만든 다항식을 $A_1(x)$라고 한다.
        
        $$
        \begin{gather}
        DFT(A_0(x))=((y_0)_0, (y_0)_1, (y_0)_2, \cdots, (y_0)_{\frac{n}{2}-1}) \\
        DFT(A_1(x))=((y_1)_0, (y_1)_1, (y_1)_2, \cdots, (y_1)_{\frac{n}{2}-1})
        \end{gather}
        $$
    
    !!! property "Property 2"
        $$
        A(x)=A_0(x^2)+xA_1(x^2)
        $$

        $$
        \begin{gather}
        y_k=(y_0)_k+\omega_n^k(y_1)_k \\
        y_{k+\frac{n}{2}}=(y_0)_k-\omega_n^k(y_1)_k \\
        (k=0, 1, \cdots, \frac{n}{2}-1)
        \end{gather}
        $$

    $DFT(A)$에서 짝수 번째 계수들과 홀수 번째 계수들을 각각 분리하여 $DFT(A_0)$과 $DFT(A_1)$을 재귀적으로 구한다.
    **Property 2**의 식을 이용하여 $O(N)$에 $DFT(A_0)$, $DFT(A_1)$의 결과를 합쳐준다.

    실제 구현에서는 $x$의 비트를 뒤집은 수가 $y$일 때 $x<y$이면 $a_x$와 $a_y$를 swap해주어 계수 배열의 bit-reversal permutation을 얻는다.
    구간의 길이를 $2^0, 2^1, \cdots$로 늘려 가며 인접한 두 구간을 하나로 합쳐준다.
    이 때 **Property 2**에서 $y_k$와 $y_{k+\frac{n}{2}}$를 계산하기 위하여 필요한 값이, 현재 작업하는 배열에 해당하는 칸 $k$, $k+\frac{n}{2}$에 들어 있는 $(y_0)_k$와 $(y_1)_k$임을 이용하여, $k$를 증가시켜 나가며 배열을 갱신시킨다.

    IDFT에서는 $\omega_n$을 $\omega_n^{-1}$로 바꾸고, 마지막에 $n$으로 나누어 준다.

    !!! complexity
        $O(N\log N)$

- **Convolution** (`MAXV * MAXV * N <= double_range`)

    !!! property "Property 3"
        $$DFT(F(x)) \cdot DFT(G(x)) = DFT((F \cdot G)(x))$$

    다항식 $F(x)$와 $G(x)$를 길이 $|F|+|G|-1$ 이상의 2의 거듭제곱 크기의 배열로 확장시킨다.
    각 배열의 DFT를 취한 후, 내적(원소별 곱) 후 IDFT를 취하여 $(F \cdot G)(x)$를 얻는다.
    총 3번의 DFT 함수를 호출한다.
    
    !!! complexity
        $O(N\log N)$

- **Convolution2** (`MAXV * N <= double_range`)
    
    !!! property "Property 4"
        $F(x)$랑 $G(x)$를 각각 DFT해야 할 때 $P=F+Gi$를 DFT하면

        $$F(\omega^k) = \frac{P(\omega^k) + \overline{P(\omega^{n-k})}}{2}, G(\omega^k) = \frac{P(\omega^k) - \overline{P(\omega^{n-k})}}{2i}$$
        
        를 써서 1번의 DFT로 모두 구할 수 있다.
    
    $D=\sqrt{\text{MAXV}}$를 기준으로 $F(x)$와 $G(x)$를 $D$로 나눈 몫과 나머지로 분리한다.
    
    $$
    \begin{gather}
    F(x) = F_1(x) \cdot D + F_2(x)\\
    G(x) = G_1(x) \cdot D + G_2(x)\\
    (F \cdot G)(x) = (F_1 \cdot G_1)(x) \cdot D^2 + (F_1 \cdot G_2 + F_2 \cdot G_1)(x) \cdot D + (F_2 \cdot G_2) (x)
    \end{gather}
    $$

    $F_1(x), F_2(x), G_1(x), G_2(x)$를 각각 DFT한 후, 위 식과 같이 합치고 IDFT를 취하여 $(F \cdot G)(x)$를 얻는다.
    각각을 DFT할 때는 **Property 4**를 이용하여 2번만의 DFT 함수를 호출하고, 총 5번의 DFT 함수를 호출한다.

    !!! complexity
        $O(N\log N)$


## Code

``` cpp linenums="1" title="fft.cpp"
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
```

## Details

``` cpp linenums="1" title="template"
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
    void init() {}

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
	void dft(vector<cpx> &A, bool inv) {}

    // Multiplies polynomial F, G (MAXV is small)
    // MAXV * MAXV * N <= long_range
    // MAXV * MAXV * N <= double_range / 2
	vector<ll> multiply(vector<int> F, vector<int> G) {}

    const int D = 5e4; // sqrt(MAXV)
    // Multiplies polynomial F, G (MAXV is big)
    // MAXV * MAXV * N <= long_range
    // D * D * N = MAXV * N <= double_range / 2
    vector<ll> multiply2(vector<int> F, vector<int> G) {}
};
```

- 구현에서 사용할 자료형에 따라 `double_range` (`double` / `long double`의 fraction 표현 범위), `long_range` (`long long` / `__int128`의 표현 범위)가 결정된다.
- `MAXV * MAXV * N <= long_range`
- `MAXB`, `MAXN`(`1<<MAXB`)이 선언되어야 함
- `void init() {}` : 초기화
- `void dft(vector<mint> &A, bool inv) {}` : 다항식 $A$의 DFT (`inv`가 true라면 IDFT)를 구하여 배열 $A$에 저장함
    - $A$의 길이는 2의 거듭제곱이어야 함
- `vector<mint> multiply(vector<mint> F, vector<mint> G) {}` : 다항식 $F$와 $G$를 곱하여 리턴함
    - `MAXV * MAXV * N <= double_range`
- `vector<mint> multiply2(vector<mint> F, vector<mint> G) {}` : 다항식 $F$와 $G$를 곱하여 리턴함
    - `MAXV * N <= double_range`

``` cpp linenums="1" title="example"
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
```