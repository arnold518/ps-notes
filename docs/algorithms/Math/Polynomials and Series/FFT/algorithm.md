---
title: FFT (Fast Fourier Transform)
tags:
    - fft
    - math
    - ~ algorithm
---

# FFT (Fast Fourier Transform)

FFT (Fast Fourier Transform)는 다항식 곱셈을 $O(NlogN)$의 시간복잡도에 하는 알고리즘이다.

<center>
$A(x)=\displaystyle \sum_{i=0}^{n-1}a_ix^i=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}$  
$B(x)=\displaystyle \sum_{i=0}^{n-1}b_ix^i=b_0+b_1x+b_2x^2+\cdots+b_{n-1}x^{n-1}$  
$A(x) \cdot B(x)=\displaystyle \sum_{i=0}^{n-1} \sum_{j=0}^{n-1} a_i b_j x^{i+j}$
</center>

## Idea

기본적인 아이디어는 다음과 같다.

특정 값들 $x_0, x_1, \cdots, x_{n-1}$에 대하여 다항식에 대입한 값들 $A(x_0), A(x_1), \cdots, A(x_{n-1})$을 알고 있다고 생각하자.
다항식 $A(x)=\displaystyle \sum_{i=0}^{n-1}a_ix^i=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}$에서 이는 미지수가 $n$개인 선형 연립방정식으로 생각하여, 미지수 $a_0, a_1, \cdots, a_{n-1}$을 구할 수 있다.

우리가 구하고 싶은 것은 $A(x) \cdot B(x)$의 계수들이니, 거꾸로 특정 값들 $x_0, x_1, \cdots, x_{n-1}$에 대하여 $A(x_0)B(x_0), A(x_1)B(x_1), \cdots, A(x_{n-1})B(x_{n-1})$을 구할 수 있다면, 위 방법을 활용하여 역으로 $A(x) \cdot B(x)$의 계수들을 구할 수 있다.

1. $x_0, x_1, \cdots, x_{n-1}$에 대하여 다항식의 계수 $a_0, a_1, \cdots, a_{n-1}$을 알고 있을 때 다항식에 대입한 값들 $A(x_0), A(x_1), \cdots, A(x_{n-1})$ 구하기
2. $x_0, x_1, \cdots, x_{n-1}$에 대하여 다항식에 대입한 값들 $A(x_0), A(x_1), \cdots, A(x_{n-1})$를 알고 있을 때 다항식의 계수 $a_0, a_1, \cdots, a_{n-1}$ 구하기

이제, 위 두 가지 작업을 $O(NlogN)$의 시간복잡도에 실행할 수 있는 알고리즘과, 적당한 $x_0, x_1, \cdots, x_{n-1}$을 선택하면 된다.

## DFT (Discrete Fourier Transform)

$$\omega_n=e^{\frac{2\pi i}{n}}=\cos\frac{2\pi}{n}+i\sin\frac{2\pi}{n}$$

[$n$-th root of unity](https://en.wikipedia.org/wiki/Root_of_unity), $\omega_n$을 생각하자.
$\omega_n$은 다음 두 성질을 만족한다.

!!! property "Property 1"
    $$\omega_n^n=1$$

!!! property "Property 2"
    $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$은 모두 서로 다르다.  
    $\omega_n^k=e^{\frac{2\pi ik}{n}}=\cos\frac{2\pi k}{n}+i\sin\frac{2\pi k}{n}$

!!! property "Property 3"
    $$\displaystyle \sum_{i=0}^{n-1} \omega_n^i = \omega_n^0 + \omega_n^1 + \cdots + \omega_n^{n-1} = \frac{1 - \omega_n^n}{1 - \omega_n} = 0$$

다항식에 대입할 값들 $x_0, x_1, \cdots, x_{n-1}$로, $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$를 선택했을 때의 함숫값들을 $DFT$로 표현하자.
또한, $DFT$의 역함수를 $IDFT$라 정의하자.

!!! definition "Definition 1"
    $DFT(a_0, a_1, \cdots, a_{n-1})=(A(\omega_n^0), A(\omega_n^1), \cdots, A(\omega_n^{n-1}))=(y_0, y_1, \cdots, y_{n-1})$

!!! definition "Definition 2"
    $IDFT(y_0, y_1, \cdots, y_{n-1})=IDFT(A(\omega_n^0), A(\omega_n^1), \cdots, A(\omega_n^{n-1}))=(a_0, a_1, \cdots, a_{n-1})$

DFT는 다음과 같이 행렬곱의 형태로 표현할 수 있다.

$$
\displaystyle y_j = \sum_{i=0}^{n-1} a_i \omega_n^{ij}
$$

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

$$
W=
\begin{bmatrix}
    \omega_n^{ij}
\end{bmatrix}_{0 \le i, j < n}
$$

$IDFT$를 구하기 위해 $DFT$ 행렬 $W$의 역행렬을 구하면 다음과 같다.

$$
W^{-1}=
\frac{1}{n}
\begin{bmatrix}
    \omega_n^{-ij}
\end{bmatrix}_{0 \le i, j < n}
$$

!!! property "Property 4"
    $$
    W=
    \begin{bmatrix}
        \omega_n^{ij}
    \end{bmatrix}_{0 \le i, j < n}
    $$

    $$
    W^{-1}=
    \frac{1}{n}
    \begin{bmatrix}
        \omega_n^{-ij}
    \end{bmatrix}_{0 \le i, j < n}
    $$

!!! proof "Proof"
    $W'=\frac{1}{n}\begin{bmatrix}\omega_n^{-ij}\end{bmatrix}_{0 \le i, j < n}$

    $\displaystyle \begin{bmatrix} W \times W' \end{bmatrix}_{i, j} = \frac{1}{n} \sum_{k=0}^{n-1} \omega_n^{ik} \omega_n^{-kj} = \frac{1}{n} \sum_{k=0}^{n-1} \omega_n^{k(i-j)} = \frac{1}{n} \sum_{k=0}^{n-1} (\omega_n^{(i-j)})^k$

    1. $i \ne j$  
    $\displaystyle \frac{1}{n} \sum_{k=0}^{n-1} (\omega_n^{(i-j)})^k = \frac{1}{n} \frac{1 - \omega_n^{n(i-j)}}{1 - \omega_n^{(i-j)}}=0$

    2. $i = j$  
    $\displaystyle \frac{1}{n} \sum_{k=0}^{n-1} (\omega_n^{(i-j)})^k = \frac{1}{n} \sum_{k=0}^{n-1} 1 = 1$
    
    $\therefore W \times W' = I_n, W^{-1}=W'$

$$
\displaystyle a_j = \frac{1}{n}\sum_{i=0}^{n-1} y_i \omega_n^{-ij}
$$

따라서, $IDFT$는 $DFT$의 $\omega_n$을 $\omega_n^{-1}$로 바꿔준 후, 결과값에 $\frac{1}{n}$을 곱해주면 된다.

## FFT (Fast Fourier Transform)

$DFT$를 빠르게 구하기 위해서 Cooley-Tukey algorithm을 사용한다.

분할 정복을 하기 위해, $n$은 $2$의 거듭제곱의 형태라 가정한다.
만약 그렇지 않은 경우, $n$이 $2$의 거듭제곱이 될 때 까지 $0$을 채워넣어주면 된다.

$$
A(x)=\displaystyle \sum_{i=0}^{n-1}a_ix^i=a_0+a_1x+a_2x^2+\cdots+a_{n-1}x^{n-1}
$$

위 다항식 $A(x)$에서 짝수 번째 계수들을 모아 만든 다항식을 $A_0(x)$, 홀수 번째 계수들을 모아 만든 다항식을 $A_1(x)$라고 하자.

<center>
$A_0(x)=\displaystyle \sum_{i=0}^{\frac{n}{2}-1}a_{2i}x^i=a_0+a_2x+a_4x^2+\cdots+a_{n-2}x^{\frac{n}{2}-1}$
</center>
<center>
$A_1(x)=\displaystyle \sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}x^i=a_1+a_3x+a_5x^2+\cdots+a_{n-1}x^{\frac{n}{2}-1}$
</center>

!!! definition "Definition 3"
    다항식 $A(x)$에서 짝수 번째 계수들을 모아 만든 다항식을 $A_0(x)$, 홀수 번째 계수들을 모아 만든 다항식을 $A_1(x)$라고 한다.  
    $A_0(x)=\displaystyle \sum_{i=0}^{\frac{n}{2}-1}a_{2i}x^i=a_0+a_2x+a_4x^2+\cdots+a_{n-2}x^{\frac{n}{2}-1}$  
    $A_1(x)=\displaystyle \sum_{i=0}^{\frac{n}{2}-1}a_{2i+1}x^i=a_1+a_3x+a_5x^2+\cdots+a_{n-1}x^{\frac{n}{2}-1}$  
    $DFT(A_0(x))=((y_0)_0, (y_0)_1, (y_0)_2, \cdots, (y_0)_{\frac{n}{2}-1})$  
    $DFT(A_1(x))=((y_1)_0, (y_1)_1, (y_1)_2, \cdots, (y_1)_{\frac{n}{2}-1})$

위 식들에서 다음과 같은 사실을 확인할 수 있다.

$$
A(x)=A_0(x^2)+xA_1(x^2)
$$

!!! property "Property 5"
    $$
    A(x)=A_0(x^2)+xA_1(x^2)
    $$

이 때, $A(x)$의 $DFT$에서는 $\omega_n$을 사용하지만, $A_0(x)$, $A_1(x)$의 $DFT$에서는 $\omega_{\frac{n}{2}}$를 사용한다는 점에 주의하자.
$\omega_n$과 $\omega_{\frac{n}{2}}$ 사이에는 다음 관계가 성립한다.

$$
\omega_n^2=\omega_{\frac{n}{2}}, \omega_n^{\frac{n}{2}}=-1
$$

!!! property "Property 6"
    $$
    \omega_n^2=\omega_{\frac{n}{2}}, \ \omega_n^{\frac{n}{2}}=-1
    $$

이제, $DFT(A_0)$, $DFT(A_1)$를 이용하여 $DFT(A)$를 구하자.

1. 앞의 $\frac{n}{2}$개의 $y_k$  
   $y_k=A(\omega_n^k)=A_0(\omega_n^{2k})+\omega_n^kA_1(\omega_n^{2k})=A_0(\omega_{\frac{n}{2}}^k)+\omega_n^kA_1(\omega_{\frac{n}{2}}^k)=(y_0)_k+\omega_n^k(y_1)_k$
2. 뒤의 $\frac{n}{2}$개의 $y_{k+\frac{n}{2}}$  
   $y_{k+\frac{n}{2}}=A(\omega_n^{k+\frac{n}{2}})=A_0(\omega_n^{2k+n})+\omega_n^{k+\frac{n}{2}}A_1(\omega_n^{2k+n})=A_0(\omega_{\frac{n}{2}}^k)-\omega_n^kA_1(\omega_{\frac{n}{2}}^k)$  
   $=(y0)_k-\omega_n^k(y1)_k$

따라서 다음과 같이 정리할 수 있다.

<center>
$y_k=(y_0)_k+\omega_n^k(y_1)_k$  
$y_{k+\frac{n}{2}}=(y_0)_k-\omega_n^k(y_1)_k$  
$(k=0, 1, \cdots, \frac{n}{2}-1)$
</center>

!!! property "Property 7"
    <center>
    $y_k=(y_0)_k+\omega_n^k(y_1)_k$  
    $y_{k+\frac{n}{2}}=(y_0)_k-\omega_n^k(y_1)_k$  
    $(k=0, 1, \cdots, \frac{n}{2}-1)$
    </center>

$DFT(A_0)$, $DFT(A_1)$를 구했다면, $O(N)$의 시간에 $DFT(A)$를 구할 수 있다.

!!! algorithm "Algorithm 1"
    $n$이 $2$의 거듭제곱이 아니라면, $0$을 뒤에 채워넣어 $2$의 거듭제곱으로 만들어준다.  
    $DFT(A)$에서 짝수 번째 계수들과 홀수 번째 계수들을 각각 분리하여 $DFT(A_0)$과 $DFT(A_1)$을 재귀적으로 구한다.  
    **Property 7**의 식을 이용하여 $DFT(A_0)$, $DFT(A_1)$의 결과를 합쳐준다.


따라서 위 분할정복 알고리즘의 시간복잡도는 $T(N)=2T(\frac{N}{2})+O(N)$으로, $O(NlogN)$이다.

!!! complexity "Time Complexity"
    <center>
    Time Complexity : $O(NlogN)$
    </center>

### In-Place Computation

만약, 처음부터 배열을 보았을 때 짝수 번째 계수들은 왼쪽에, 홀수 번째 계수들은 오른쪽에 쪼개어져 있다면 재귀 과정에서 값들을 추가 배열을 만들어서 작업할 필요가 없거나 더 나아가 재귀 자체를 하지 않아도 될 수 있다.

재귀의 첫 단계에서, $0$번째 비트가 $0$인 수들은 왼쪽으로, $1$인 수들은 오른쪽으로 배치된다.
이러한 과정이 반복되면, 결국 재배열은 각 수들의 비트를 뒤집었을 때 증가하는 순서대로 배치됨을 알 수 있다.
이러한 순열을 **bit-reversal permutation**이라 한다.
구현은 단순히 $x$의 비트를 뒤집은 수가 $y$일 때 $x<y$이면 $a_x$와 $a_y$를 swap해주면 된다.

다음은 $n=8$일 때의 예시이다.

$$
(((a_0, a_4), (a_2, a_6)), ((a_1, a_5), (a_3, a_7)))
$$

위 아이디어를 통해 재귀 없이, 반복만으로도 **Property 7**을 이용하여 한 배열 내에서 계산을 할 수 있다.
**Property 7**에서 $y_k$와 $y_{k+\frac{n}{2}}$를 계산하기 위하여 필요한 값이, 현재 작업하는 배열에 해당하는 칸 $k$, $k+\frac{n}{2}$에 들어 있는 $(y_0)_k$와 $(y_1)_k$이니, $k$를 증가시켜 나가며 배열을 갱신시키면 된다.

!!! algorithm "Algorithm 2"
    $n$이 $2$의 거듭제곱이 아니라면, $0$을 뒤에 채워넣어 $2$의 거듭제곱으로 만들어준다.  
    $x$의 비트를 뒤집은 수가 $y$일 때 $x<y$이면 $a_x$와 $a_y$를 swap해주어 계수 배열의 **bit-reversal permutation**을 얻는다.  
    구간의 길이를 $2^0, 2^1, \cdots$로 늘려 가며 인접한 두 구간을 하나로 합쳐준다.
    이 때 **Property 7**에서 $y_k$와 $y_{k+\frac{n}{2}}$를 계산하기 위하여 필요한 값이, 현재 작업하는 배열에 해당하는 칸 $k$, $k+\frac{n}{2}$에 들어 있는 $(y_0)_k$와 $(y_1)_k$임을 이용하여, $k$를 증가시켜 나가며 배열을 갱신시킨다.

### Implementation

``` cpp linenums="1"
typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> &A, bool inv)
{
	int N=A.size(), B=31-__builtin_clz(N);
	for(int i=0; i<N; i++)
	{
		int rev=0;
		for(int j=0; j<B; j++) rev<<=1, rev|=(i>>j)&1;
		if(rev>i) swap(A[rev], A[i]);
	}

	for(int i=1; i<N; i<<=1)
	{
		cd w(cos(PI/i), (inv ? -1 : 1)*sin(PI/i));
		for(int j=0; j<N; j+=i+i)
		{
			cd s(1, 0);
			for(int k=0; k<i; k++)
			{
				cd a=A[j+k], b=A[j+i+k]*s;
				A[j+k]=a+b; A[j+i+k]=a-b;
				s*=w;
			}
		}
	}
	if(inv) for(int i=0; i<N; i++) A[i]/=N;
}
```

## NTT (Number Theoretic Transform)

**FFT**에서 다항식에 대입할 $x_0, x_1, \cdots, x_{n-1}$으로 $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$을 선정한 이유는 위에서 사용한 다양한 성질들을 만족시키기 위함이었다.
그 중에서도, 특히 다른 성질들로 표현할 수 없었던, 필수적인 성질들은 **Property 1**과 **Property 2**이다.

이제, 수의 범위를 복소수 $\mathbb{C}$에서 정수 나머지 $\mathbb{Z}_p$로 바꿔보자.
마찬가지로, $\mathbb{Z}_p$에서도 **Property 1**과 **Property 2**를 만족하는 어떠한 $\omega_n$을 찾을 수 있다면, **FFT**를 그대로 적용할 수 있다.

$p$가 소수일 때, [$n$-th primitive root of unity modulo $p$](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n) $\omega_n$이 존재할 필요충분조건은 $n \ | \ p-1$이다.

!!! property "Property 8"
    $p$가 소수일 때, "$n$-th primitive root of unity modulo $p$" $\omega_n$이 존재할 필요충분조건은 $n \ | \ p-1$이다.

모든 소수는 [root of unity modulo $p$](https://en.wikipedia.org/wiki/Root_of_unity_modulo_n) 원시근 $\omega=\omega_{p-1}$가 존재한다.
원시근을 쉽게 구하는 방법은 아직 알려지지 않았다.
원시근 $\omega$를 알고 있을 때, $n \ | \ p-1$인 $n$에 대하여 $\omega_n=\omega^{\frac{p-1}{n}}$으로 구할 수 있다.

$$
\omega_n=\omega^{\frac{p-1}{n}}
$$

$$
\omega_n^n=(\omega^{\frac{p-1}{n}})^n=\omega^{p-1}\equiv 1
$$

!!! property "Property 9"
    $p$가 소수일 때, root of unity modulo $p$ 원시근 $\omega=\omega_{p-1}$가 존재한다.  
    원시근 $\omega$를 알고 있을 때, $n \ | \ p-1$인 $n$에 대하여 $\omega_n=\omega^{\frac{p-1}{n}}$으로 구할 수 있다.

원시근을 모를 때, 어떤 수가 원시근인지 확인하기 위해서는 $a^{p-1} \equiv 1$, $d \ | \ p-1, d \ne p-1$인 모든 약수 $d$에 대해서는 $a^d \not\equiv 1$인지 확인해주면 된다.
대부분의 경우 $3$ 또는 $5$가 원시근이다.

특히, $p=a \cdot 2^k + 1$ 꼴일 때, $n=2^m$ ($m \le k$)이면 $n \ | \ p-1$이니 **NTT**를 적용하기가 아주 좋다.

다음은 몇 가지 소수들과 원시근의 예시이다.

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

### Implementation
``` cpp linenums="1"
const ll MOD = 998244353;
const ll _W = 3;

ll mypow(ll x, ll y)
{
	ll ret=1;
	for(; y>0; y>>=1, x=x*x%MOD)
	{
		if(y&1) ret=ret*x%MOD;
	}
	return ret;
}

ll myinv(ll x) { return mypow(x, MOD-2); }

void fft(vector<ll> &A, bool inv)
{
	int N=A.size(), B=31-__builtin_clz(N);
	for(int i=0; i<N; i++)
	{
		int rev=0;
		for(int j=0; j<B; j++) rev<<=1, rev|=(i>>j)&1;
		if(rev>i) swap(A[rev], A[i]);
	}

	for(int i=1; i<N; i<<=1)
	{
		ll w=mypow(_W, (MOD-1)/(i+i));
		if(inv) w=myinv(w);
		for(int j=0; j<N; j+=i+i)
		{
			ll s=1;
			for(int k=0; k<i; k++)
			{
				ll a=A[j+k], b=A[j+i+k]*s%MOD;
				A[j+k]=(a+b)%MOD; A[j+i+k]=(a-b+MOD)%MOD;
				s=s*w%MOD;
			}
		}
	}
	ll t=myinv(N);
	if(inv) for(int i=0; i<N; i++) A[i]=A[i]*t%MOD;
}
```

## Reference
- [https://cp-algorithms.com/algebra/fft.html](https://cp-algorithms.com/algebra/fft.html)
- [https://algoshitpo.github.io/2020/05/20/fft-ntt/](https://algoshitpo.github.io/2020/05/20/fft-ntt/)
- [https://codeforces.com/blog/entry/111371](https://codeforces.com/blog/entry/111371)
- [https://codeforces.com/blog/entry/43499](https://codeforces.com/blog/entry/43499)