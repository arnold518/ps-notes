---
title: FWHT (Fast Walsh Hadamard Transform)
tags:
    - fft
    - math
    - ~ algorithm
---

# FWHT (Fast Walsh Hadamard Transform)

**FFT**는 다음과 같은 형태의 convolution을 $O(NlogN)$에 계산할 수 있게 해준다.

$$
c_i = \sum_{j+k=i} a_j \cdot b_k
$$

**FWHT**는 이를 더 확장하여, convolution의 형태가 덧셈이 아닌, **bitwise xor**, **bitwise and**, **bitwise or** 등의 다양한 연산들 $\star$ 에 대하여 가능하게 하는 알고리즘이다.

$$
c_i = \sum_{j \star k=i} a_j \cdot b_k
$$

## Extension of FFT

### DFT as Matrix Multiplication

우선, **DFT**를 다항식에 대입할 값들 $x_0, x_1, \cdots, x_{n-1}$로, $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$를 선택했을 때의 함숫값을 구하는 과정으로 생각하지 말고, 행렬곱의 개념으로 생각하자.

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

이 때, DFT matrix $W$는 다음 조건을 만족한다.

$$
c_i = \sum_{j+k=i} a_j \cdot b_k
$$

$$
W
\begin{bmatrix}
    a_0 \\    
    a_1 \\
    a_2 \\
    \vdots \\
    a_{n-1}
\end{bmatrix}
\cdot
W
\begin{bmatrix}
    b_0 \\    
    b_1 \\
    b_2 \\
    \vdots \\
    b_{n-1}
\end{bmatrix}
=
W
\begin{bmatrix}
    c_0 \\    
    c_1 \\
    c_2 \\
    \vdots \\
    c_{n-1}
\end{bmatrix}
$$

임의의 연산 $\star$에 대해서도 위와 같은 성질을 만족하는 행렬(invertible matrix) $T$를 찾을 수 있다면, 다항식에 $\omega_n^0, \omega_n^1, \cdots, \omega_n^{n-1}$를 대입한 함숫값들을 의미하는 DFT matrix $W$는 아니지만, **DFT**와 같은 논리를 적용할 수 있다.

$$
c_i = \sum_{j \star k=i} a_j \cdot b_k
$$

$$
T
\begin{bmatrix}
    a_0 \\    
    a_1 \\
    a_2 \\
    \vdots \\
    a_{n-1}
\end{bmatrix}
\cdot
T
\begin{bmatrix}
    b_0 \\    
    b_1 \\
    b_2 \\
    \vdots \\
    b_{n-1}
\end{bmatrix}
=
T
\begin{bmatrix}
    c_0 \\    
    c_1 \\
    c_2 \\
    \vdots \\
    c_{n-1}
\end{bmatrix}
$$

!!! note "Property 1"
    $$
    c_i = \sum_{j \star k=i} a_j \cdot b_k
    $$

    $$
    T
    \begin{bmatrix}
        a_0 \\    
        a_1 \\
        a_2 \\
        \vdots \\
        a_{n-1}
    \end{bmatrix}
    \cdot
    T
    \begin{bmatrix}
        b_0 \\    
        b_1 \\
        b_2 \\
        \vdots \\
        b_{n-1}
    \end{bmatrix}
    =
    T
    \begin{bmatrix}
        c_0 \\    
        c_1 \\
        c_2 \\
        \vdots \\
        c_{n-1}
    \end{bmatrix}
    $$

    임의의 연산 $\star$에 대하여 위 조건을 만족하는 행렬(invertible matrix) $T$를 찾을 수 있다면, **DFT**와 같은 논리를 적용할 수 있다.

### MultiDimensional DFT

**DFT**는 다항식 $A(x)$에 특정 값들을 대입하여 그 함숫값들로 변환한다.
일변수 다항식 $A(x)$가 아닌, 이변수 다항식 $A(x, y)$, 혹은 변수가 $n$개 있는 다항식 $A(x_0, x_1, \cdots, x_{n-1})$에 대해서도 변수에 특정 값들을 대입하여 그 함숫값들로 변환할 수 있다.

구체적으로 MultiDimensional DFT를 정의하기 위하여 다음을 정의하자.

!!! quote "Definition 1"
    $A$가 $m \times n$ 행렬, $B$가 $p \times q$ 행렬일 때 $A$와 $B$의 kronecker product $A \otimes B$를 다음과 같은 크기 $mp \times nq$의 block matrix로 정의한다.

    $$
    A \bigotimes B = 
    \begin{bmatrix}
        a_{11}B & a_{12}B & a_{13}B & \dots & a_{1n}B \\
        a_{21}B & a_{22}B & a_{23}B & \dots & a_{2n}B \\
        a_{31}B & a_{32}B & a_{33}B & \dots & a_{3n}B \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        a_{m1}B & a_{m2}B & a_{m3}B & \dots & a_{mn}B \\
    \end{bmatrix}
    $$

Kronecker product 에는 다음과 같은 성질들이 성립한다.

!!! note "Property 2"
    $$(A \otimes B) \otimes C = A \otimes (B \otimes C)$$

    $$(A \otimes B)(C \otimes D) = (AC \otimes BD)$$

    $$(A \otimes B)^{-1} = (A^{-1} \otimes B^{-1})$$

!!! quote "Definition 2"
    다항식 $A(x_0, x_1, \cdots, x_{n-1})$이 다음과 같는 계수들을 갖는다.

    $$
    A(x_0, x_1, \cdots, x_{n-1}) = 
    \sum_{i_0=0}^{m_0}
    \sum_{i_1=0}^{m_1}
    \sum_{i_2=0}^{m_2}
    \cdots
    \sum_{i_{n-1}=0}^{m_{n-1}}
    a_{i_0, i_1, i_2, \cdots, i_{n-1}} x_0^{i_0} x_1^{i_1} x_2^{i_2} \cdots x_{n-1}^{i_{n-1}}
    $$

    이 때, 다항식의 vector form을 다음과 같이 정의한다.

    $\overrightarrow{a}_{0, 1, 2, \cdots, n-1}=$ 다항식들의 계수 $a_{i_0, i_1, i_2, \cdots, i_{n-1}}$를 $(i_0, i_1, i_2, \cdots, i_{n-1})$에 대한 사전순으로 일렬로 배열한 벡터.

    $$
    \overrightarrow{a}_{0, 1, 2, \cdots, n-1} = 
    \begin{bmatrix}
        a_{0, 0, 0, \cdots, 0} \\
        a_{0, 0, 0, \cdots, 1} \\
        a_{0, 0, 0, \cdots, 2} \\
        \vdots \\ 
        a_{m_0-1, m_1-1, m_2-1, \cdots, m_{n-1}-1}
    \end{bmatrix}
    $$

다항식의 vector form은 다음과 같이 재귀적으로 해석할 수 있다.

$$
\overrightarrow{a}_{0, 1, 2, \cdots, n-1} = 
\begin{bmatrix}
    a_{0, 0, 0, \cdots, 0} \\
    a_{0, 0, 0, \cdots, 1} \\
    a_{0, 0, 0, \cdots, 2} \\
    \vdots \\ 
    a_{m_0-1, m_1-1, m_2-1, \cdots, m_{n-1}-1}
\end{bmatrix}
$$

$$
=
\begin{bmatrix}
    \begin{bmatrix}
        a_{0, 0, 0, \cdots, 0} \\
        a_{0, 0, 0, \cdots, 1} \\
        \vdots \\ 
        a_{0, m_1-1, m_2-1, \cdots, m_{n-1}-1}
    \end{bmatrix} \\
    \begin{bmatrix}
        a_{1, 0, 0, \cdots, 0} \\
        a_{1, 0, 0, \cdots, 1} \\
        \vdots \\ 
        a_{1, m_1-1, m_2-1, \cdots, m_{n-1}-1}
    \end{bmatrix} \\
    \vdots \\
    \begin{bmatrix}
        a_{m_0-1, 0, 0, \cdots, 0} \\
        a_{m_0-1, 0, 0, \cdots, 1} \\
        \vdots \\ 
        a_{m_0-1, m_1-1, m_2-1, \cdots, m_{n-1}-1}
    \end{bmatrix} \\
\end{bmatrix}
=
\begin{bmatrix}
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_0 \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_1 \\
    \vdots \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_{m_0-1}
\end{bmatrix}
$$

!!! note "Property 3"
    $$
    \overrightarrow{a}_{0, 1, 2, \cdots, n-1} =
    \begin{bmatrix}
        (\overrightarrow{a}_{1, 2, \cdots, n-1})_0 \\
        (\overrightarrow{a}_{1, 2, \cdots, n-1})_1 \\
        \vdots \\
        (\overrightarrow{a}_{1, 2, \cdots, n-1})_{m_0-1}
    \end{bmatrix}
    $$


이제 1차원 **DFT**를 반복적으로 적용하여 다차원으로 확장하자.
$T_0, T_1, \cdots, T_{n-1}$을 변수 $x_0, x_1, \cdots x_{n-1}$에 대하여 **Property 1**을 만족하는 행렬이라 하자.
전체 다항식에 대한 변환 행렬 $T$를 다음과 같이 구할 수 있다.

$$
T=T_0 \otimes T_1 \otimes T_2 \cdots \otimes T_{n-1}
$$

편의를 위해 다음을 정의하자.

$$T'=T_1 \otimes T_2 \cdots \otimes T_{n-1}$$

$$(\overrightarrow{y}_{1, 2, \cdots, n-1})_k = (T_1 \otimes T_2 \cdots \otimes T_{n-1}) (\overrightarrow{a}_{1, 2, \cdots, n-1})_k = T'(\overrightarrow{a}_{1, 2, \cdots, n-1})_k$$

!!! quote "Definition 3"

    $$T'=T_1 \otimes T_2 \cdots \otimes T_{n-1}$$

    $$(\overrightarrow{y}_{1, 2, \cdots, n-1})_k = (T_1 \otimes T_2 \cdots \otimes T_{n-1}) (\overrightarrow{a}_{1, 2, \cdots, n-1})_k = T'(\overrightarrow{a}_{1, 2, \cdots, n-1})_k$$

$$
(T_0 \otimes T_1 \otimes T_2 \cdots \otimes T_{n-1}) \ \overrightarrow{a}_{0, 1, 2, \cdots, n-1}
=
(T_0 \otimes T')
\begin{bmatrix}
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_0 \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_1 \\
    \vdots \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_{m_0-1}
\end{bmatrix}
$$

$$
=\begin{bmatrix}
    (T_0)_{0,0} T' & (T_0)_{0,1} T' & \dots & (T_0)_{0, m_0-1} T' \\
    (T_0)_{1,0} T' & (T_0)_{1,1} T' & \dots & (T_0)_{1, m_0-1} T' \\
    \vdots & \vdots & \ddots & \vdots \\
    (T_0)_{m_0-1,0} T' & (T_0)_{m_0-1,1} T' & \dots & (T_0)_{m_0-1, m_0-1} T' \\
\end{bmatrix}
\begin{bmatrix}
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_0 \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_1 \\
    \vdots \\
    (\overrightarrow{a}_{1, 2, \cdots, n-1})_{m_0-1}
\end{bmatrix}
$$

$$
=\begin{bmatrix}
    (T_0)_{0,0}(\overrightarrow{y}_{1, 2, \cdots, n-1})_0 + (T_0)_{0,1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_1 + \cdots + (T_0)_{0,m_0-1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_{m_0-1}\\
    (T_0)_{1,0}(\overrightarrow{y}_{1, 2, \cdots, n-1})_0 + (T_0)_{1,1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_1 + \cdots + (T_0)_{1,m_0-1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_{m_0-1}\\
    \vdots \\
    (T_0)_{m_0-1,0}(\overrightarrow{y}_{1, 2, \cdots, n-1})_0 + (T_0)_{m_0-1,1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_1 + \cdots + (T_0)_{m_0-1,m_0-1}(\overrightarrow{y}_{1, 2, \cdots, n-1})_{m_0-1}\\
\end{bmatrix}
$$

$$
= T_0 \ 
\begin{bmatrix}
    (\overrightarrow{y}_{1, 2, \cdots, n-1})_0 \\
    (\overrightarrow{y}_{1, 2, \cdots, n-1})_1 \\
    \vdots \\
    (\overrightarrow{y}_{1, 2, \cdots, n-1})_{m_0-1}
\end{bmatrix}
=\overrightarrow{y}_{0, 1, 2, \cdots, n-1}
$$

이 때, 마지막 식에서 $T_0$ 행렬과 $\overrightarrow{a}_{0, 1, 2, \cdots, n-1}$ 벡터를 $m_0$개로 묶은 벡터를 행렬 곱셈 연산으로 곱했다는 것에 주의하자.

위 복잡한 식들의 의미는 결국, 변수 $x_0$를 무시한 후, $x_0$의 차수에 따라 분리한 다항식 계수들에 대하여 각각 **DFT**를 한 후, 결과 벡터를 하나의 수처럼 생각한 후 $x_0$에 대한 **DFT**를 하면 MultiDimensional DFT를 할 수 있다는 의미이다.
또한, 전 과정에서 DFT matrix 를 사용한 것이 아니라, **Property 1**의 성질을 만족하는 임의의 행렬을 사용해도 괜찮다.

!!! example "Algorithm 1"
    MultiDimensional DFT를 하기 위해선, 우선 첫 번째 변수 $x_0$의 차수에 따라 분리한 다항식 계수들에 대하여 각각 $n-1$차원 **DFT**를 한 후, 결과 벡터를 하나의 수처럼 생각한 후 $x_0$에 대한 **DFT**를 하면 된다.

    이때, **DFT** 대신 **Property 1**의 성질을 만족하는 단순 행렬곱으로 각 단계를 생각해도 된다.

마지막으로, **IDFT** 또한 **Property 2**를 활용하여 $T$의 역행렬을 쉽게 구할 수 있다.

$$
T^{-1} = T_0^{-1} \otimes T_1^{-1} \otimes T_2^{-1} \cdots \otimes T_{n-1}^{-1}
$$

!!! note "Property 4"
    $$
    T=T_0 \otimes T_1 \otimes T_2 \cdots \otimes T_{n-1}
    $$

    $$
    T^{-1} = T_0^{-1} \otimes T_1^{-1} \otimes T_2^{-1} \cdots \otimes T_{n-1}^{-1}
    $$

## Bitwise Convolution

**bitwise xor**, **bitwise and**, **bitwise or** 등의 여러 bitwise operation 들에 convolution을 적용하기 위하여, 다음과 같이 생각하자.
모든 연산들이 각 bit에 대하여 독립적으로 해석할 수 있으니, 각 bit를 다항식의 변수와 일대일 대응시킬 수 있다.
예를 들어, 일반적인 **DFT**에서 $a_5 = p$였다면 이를 $px^5$으로 표현했지만, **bitwise DFT**에서는 $px_2^1x_1^0x_0^1$ ($5=101_{(2)}$)의 항으로 표현된다.

따라서, 각 bit를 의미하는 다변수 다항식으로 배열을 표현한 이후, 이제 준 식에 MultiDimensional DFT를 적용할 수 있다.
각 bit에 적용할 연산 (xor, and, or)이 모두 동일하니 크기 $2 \times 2$인 한 bit에만 적용될 수 있는 행렬 $T$를 찾은 후, $T \otimes T \otimes T \cdots \otimes T$와 같이 반복적으로 kronecker product를 취하면 DFT값을 구할 수 있다.

이제, 각 연산에 대하여 각각 행렬 $T$를 찾아주기만 하면 된다.

xor의 예를 들면 **Property 1**의 식을 풀어 쓰면 다음과 같다.

$$
T_{\oplus}
\begin{bmatrix}
    p_0 \\ p_1
\end{bmatrix}
\cdot
T_{\oplus}
\begin{bmatrix}
    q_0 \\ q_1
\end{bmatrix}
=
T_{\oplus}
\begin{bmatrix}
    p_0q_0+p_1q_1 \\ p_0q_1+p_1q_0
\end{bmatrix}
$$

위 성질을 만족하는 invertible matrix를 찾으면 $T_{\oplus}$를 구할 수 있다.

$$
T_{\oplus}=
\begin{bmatrix}
    1 & 1 \\ 1 & -1
\end{bmatrix}, \
T_{\oplus}^{-1}=
\frac{1}{2}
\begin{bmatrix}
    1 & 1 \\ 1 & -1
\end{bmatrix}
$$

$$
T_{\&}=
\begin{bmatrix}
    0 & 1 \\ 1 & 1
\end{bmatrix}, \
T_{\&}^{-1}=
\begin{bmatrix}
    -1 & 1 \\ 1 & 0
\end{bmatrix}
$$

$$
T_{|}=
\begin{bmatrix}
    1 & 0 \\ 1 & 1
\end{bmatrix}, \
T_{|}^{-1}=
\begin{bmatrix}
    1 & 0 \\ -1 & 1
\end{bmatrix}
$$

!!! note "Property 5"
    $$
    T_{\oplus}=
    \begin{bmatrix}
        1 & 1 \\ 1 & -1
    \end{bmatrix}, \
    T_{\oplus}^{-1}=
    \frac{1}{2}
    \begin{bmatrix}
        1 & 1 \\ 1 & -1
    \end{bmatrix}
    $$

    $$
    T_{\&}=
    \begin{bmatrix}
        0 & 1 \\ 1 & 1
    \end{bmatrix}, \
    T_{\&}^{-1}=
    \begin{bmatrix}
        -1 & 1 \\ 1 & 0
    \end{bmatrix}
    $$

    $$
    T_{|}=
    \begin{bmatrix}
        1 & 0 \\ 1 & 1
    \end{bmatrix}, \
    T_{|}^{-1}=
    \begin{bmatrix}
        1 & 0 \\ -1 & 1
    \end{bmatrix}
    $$

시간 복잡도는 $logN$차원 **DFT**이고, 각 차원이 크기 $2$인 행렬곱이므로 $O(NlogN)$이다.

!!! tip "Time Complexity"
    <center>
    Time Complexity : $O(NlogN)$
    </center>

### XOR Convolution

(다른 관점의 해석)

**bitwise xor** 연산은 $\mathbb{Z}_2^k$상에서의 덧셈 연산과 동일하다.

$$
T_{\oplus}=
\begin{bmatrix}
    1 & 1 \\ 1 & -1
\end{bmatrix}, \
T_{\oplus}^{-1}=
\frac{1}{2}
\begin{bmatrix}
    1 & 1 \\ 1 & -1
\end{bmatrix}
$$

위 행렬을 다음과 같이 해석할 수 있다.
일반적인 **DFT**에서 $\omega_2=-1$이니, $T_{\oplus}$는 사실 크기 $2$의 DFT matrix와 동일하다.
하지만 크기 $2$인 벡터를 DFT하여 convolution하기 위해서는 크기 $3$이상의 공간이 필요하지만, 크기 $2$의 행렬을 선택하였기 때문에 $x^2$에 해당하는 값은 다시 $x^0$과 같게 취급되고, 이는 사실 $\mathbb{Z}_2$상에서의 덧셈, 즉 xor이 원하는 연산을 구현하였다고 해석할 수 있다.

---

이를 더 일반화하면, $\mathbb{Z}_2$상에서의 덧셈 연산인 **bitwise xor**에서 $\omega_2$로 구성된 크기 $2$의 DFT matrix를 사용했던 것처럼, $\mathbb{Z}_k$상에서의 덧셈 연산에서는 $\omega_k$로 구성된 크기 $k$의 DFT matrix를 사용하면 구할 수 있다.

### AND / OR Convolution

(다른 관점의 해석)

**bitwise and**연산은 **bitwise or**연산의 여집합으로 해석할 수 있으니, **bitwise or**연산에 대해서만 서술한다.
**bitwise or**연산은 $\mathbb{Z}_2^k$상에서의 max 연산, 혹은 합집합 연산과 동일하다.

$$
T_{|}=
\begin{bmatrix}
    1 & 0 \\ 1 & 1
\end{bmatrix}, \
T_{|}^{-1}=
\begin{bmatrix}
    1 & 0 \\ -1 & 1
\end{bmatrix}
$$

위 행렬은 크기 $2$인 벡터에 대한 누적합을 취하는 행렬이고, 역행렬은 거꾸로 누적합의 역연산, 즉 차이값 배열을 취하는 행렬이다.
모든 비트를 모아놓고 보면, 결국 특정 집합의 부분집합을 모두 순회하여 더하는, **Sum of Subset**을 취하는 연산임을 알 수 있다.
따라서 **OR convolution**은 각 배열 $a$, $b$에 대하여 **Sum of Subset**을 취한 후 곱하여 배열 $c'$을 구하고, **Sum of Subset**의 역연산을 통해 최종 배열 $c$를 구한다고 요약할 수 있다.

$$
c_i = \sum_{j \cup k=i} a_j \cdot b_k
$$

$$
c'_i = \sum_{j \subseteq i}c_j = \sum_{j \cup k \subseteq i} a_j \cdot b_k = \sum_{j \subseteq i \wedge k \subseteq i} a_j \cdot b_k = \sum_{j \subseteq i} a_j \cdot \sum_{k \subseteq i} b_k
$$

위 식을 통해서도 그 정당성을 확인할 수 있다.
**OR convolution**을 구현하면, **SOS DP**를 통해 위 식을 직접 계산하는 것과 동일한 작업을 한다.

---

이를 더 일반화하면, $\mathbb{Z}_2$상에서의 max 연산인 **bitwise or**에서 **Sum of Subset**을 취했던 것처럼, $\mathbb{Z}_k$상에서의 max 연산에서는 크기 $k$인 누적합을 하는 **Sum of Subset**을 구한다고 요약할 수 있다.

### Implementation

다음은 **XOR Convolution**에 대한 구현 코드이다.
**AND / OR Convolution** 또한, 행렬 $T$만 다르게 구현해주면 됨을 알 수 있다.

또한, 실제 구현은 **FFT**와 매우 유사하지만, 그 동작 원리는 크기 $2$의 FFT를 비트의 개수만큼 쌓아 MultiDimensional FFT를 하는 것임에 주의하자.

``` cpp linenums="1"
void DFT(vector<ll> &A, bool inv)
{
    int N=A.size();
	for(int i=1; i<N; i<<=1)
	{
		for(int j=0; j<N; j+=i+i)
		{
			for(int k=0; k<i; k++)
			{
				ll a=A[j+k], b=A[j+i+k];
				A[j+k]=a+b;
				A[j+i+k]=a-b;
				if(inv) A[j+k]/=2, A[j+i+k]/=2;
			}
		}
	}
}
```