# Number Theoretic Transform

## Problem

!!! property "Property 1"
    $p$가 소수일 때, root of unity modulo $p$ 원시근 $\omega=\omega_{p-1}$가 존재한다.  
    원시근 $\omega$를 알고 있을 때, $n \ | \ p-1$인 $n$에 대하여 "$n$-th primitive root of unity modulo $p$" $\omega_n=\omega^{\frac{p-1}{n}}$이다.

    - $\omega_n^n \equiv 1 \pmod{n}$
    - $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$은 모두 mod $n$으로 서로 다르다.
    
    ---

    $$
    p=a \times 2^b + 1
    $$

    <center>

    |       p       |  a  |  b | $\omega$ |
    |:-------------:|:---:|:--:|:--------:|
    |  998,244,353  | 119 | 23 |     3    |
    | 2,281,701,377 |  17 | 27 |     3    |
    | 2,483,027,969 |  37 | 26 |     3    |
    | 2,113,929,217 |  63 | 25 |     5    |
    |  104,857,601  |  25 | 22 |     3    |
    | 1,092,616,193 | 521 | 21 |     3    |
    
    </center>

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

- **DFT / IDFT** : `MOD`와 원시근 `G`가 정해져 있을 때, 배열 $A$가 주어질 때, $A$의 DFT / IDFT 배열을 구한다.
- **Convolution** : 다항식 $F(x)$, $G(x)$가 주어질 때, $\mathbb{Z}_{\text{MOD}}$에서의 다항식 곱 $(F \cdot G)(x)$를 구한다.

## Algorithm

- **DFT / IDFT**

    !!! definition "Definition 2"
        다항식 $A(x)$에서 짝수 번째 계수들을 모아 만든 다항식을 $A_0(x)$, 홀수 번째 계수들을 모아 만든 다항식을 $A_1(x)$라고 한다.  
        $DFT(A_0(x))=((y_0)_0, (y_0)_1, (y_0)_2, \cdots, (y_0)_{\frac{n}{2}-1})$  
        $DFT(A_1(x))=((y_1)_0, (y_1)_1, (y_1)_2, \cdots, (y_1)_{\frac{n}{2}-1})$
    
    !!! property "Property 2"
        $$
        A(x)=A_0(x^2)+xA_1(x^2)
        $$

        <center>
        $y_k=(y_0)_k+\omega_n^k(y_1)_k$  
        $y_{k+\frac{n}{2}}=(y_0)_k-\omega_n^k(y_1)_k$  
        $(k=0, 1, \cdots, \frac{n}{2}-1)$
        </center>

    $DFT(A)$에서 짝수 번째 계수들과 홀수 번째 계수들을 각각 분리하여 $DFT(A_0)$과 $DFT(A_1)$을 재귀적으로 구한다.
    **Property 2**의 식을 이용하여 $O(N)$에 $DFT(A_0)$, $DFT(A_1)$의 결과를 합쳐준다.

    실제 구현에서는 $x$의 비트를 뒤집은 수가 $y$일 때 $x<y$이면 $a_x$와 $a_y$를 swap해주어 계수 배열의 bit-reversal permutation을 얻는다.
    구간의 길이를 $2^0, 2^1, \cdots$로 늘려 가며 인접한 두 구간을 하나로 합쳐준다.
    이 때 **Property 2**에서 $y_k$와 $y_{k+\frac{n}{2}}$를 계산하기 위하여 필요한 값이, 현재 작업하는 배열에 해당하는 칸 $k$, $k+\frac{n}{2}$에 들어 있는 $(y_0)_k$와 $(y_1)_k$임을 이용하여, $k$를 증가시켜 나가며 배열을 갱신시킨다.

    IDFT에서는 $\omega_n$을 $\omega_n^{-1}$로 바꾸고, 마지막에 $n$으로 나누어 준다.

    !!! complexity
        $O(N\log N)$

- **Convolution**

    !!! property "Property 3"
        $$DFT(F(x)) \cdot DFT(G(x)) = DFT((F \cdot G)(x))$$

    다항식 $F(x)$와 $G(x)$를 길이 $|F|+|G|-1$ 이상의 2의 거듭제곱 크기의 배열로 확장시킨다.
    각 배열의 DFT를 취한 후, 내적(원소별 곱) 후 IDFT를 취하여 $(F \cdot G)(x)$를 얻는다.
    총 3번의 DFT 함수를 호출한다.
    
    !!! complexity
        $O(N\log N)$

## Code

``` cpp linenums="1" title="ntt.cpp"
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
```

## Details

``` cpp linenums="1" title="template"
// mint must be included

namespace NTT
{
    const mint G; // primitive root of MOD

    const int MAXB;
    const int MAXN = (1<<MAXB); // MAXN must divide MOD-1

    void init() {}

    // Get DFT (IDFT if inv is true) of polynomial A
    // length of A must be power of 2
	void dft(vector<mint> &A, bool inv) {}

    // Multiplies polynomial F, G
	vector<mint> multiply(vector<mint> F, vector<mint> G) {}
};
```

- `mint` 구현이 포함되어야 함
- `G`(`MOD`의 원시근), `MAXB`, `MAXN`(`1<<MAXB`)이 선언되어야 함
- `MAXN`은 `MOD-1`의 약수여야 함
- `void init() {}` : 초기화
- `void dft(vector<mint> &A, bool inv) {}` : 다항식 $A$의 DFT (`inv`가 true라면 IDFT)를 구하여 배열 $A$에 저장함
    - $A$의 길이는 2의 거듭제곱이어야 함
- `vector<mint> multiply(vector<mint> F, vector<mint> G) {}` : $\mathbb{Z}_{\text{MOD}}$에서 다항식 $F$와 $G$를 곱하여 리턴함

``` cpp linenums="1" title="example"
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
```