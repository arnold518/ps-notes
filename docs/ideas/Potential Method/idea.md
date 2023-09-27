---
title: Potential Method
tags:
    - ~idea
---

# Potential Method

## Definition

Ammortized time complexity를 분석하기 위하여, 현재 자료구조의 상태를 나타낼 수 있는 potential function $\Phi(S)$를 정의하자.
$\Phi(S)$는 자료구조가 이상적인 상태와 비교해 얼마나 어지럽혀 있는지를 나타내는 함수로, 물리에서의 위치에너지와 같은 개념으로 생각해도 좋다.

!!! definition "Definition 1"
    - $\Phi(S):=$ 자료구조가 상태 $S$일 때의 potential function $(\Phi : S \rightarrow \mathbb{R}_{\ge 0})$
    - $T_{\text{ammortized}}(o)=T_{\text{actual}}(o)+C \cdot \varDelta \Phi(S) = T_{\text{actual}}(o)+C \cdot (\Phi(S_{\text{after}})-\Phi(S_{\text{before}}))$

위 **Definition 1**과 같이 $\Phi(S)$와 $T_{\text{ammortized}}(o)$를 정의한다면, 여러 연산들 $O=\{o_1, o_2, ..., o_n\}$을 모두 실행한 후의 실제 시간복잡도 $T_{\text{actual}}(O)$의 상한을 ammortized 시간복잡도 $T_{\text{ammortized}}(O)$를 이용하여 구할 수 있다.

!!! property "Property 1"
    연산들 $O=\{o_1, o_2, ..., o_n\}$에 대하여 실제 시간복잡도를 $T_{\text{actual}}(O)$, ammortized 시간복잡도를 $T_{\text{ammortized}}(O)$라 한다면 다음이 성립한다.

    $$\displaystyle
    T_{\text{ammortized}}(O)
    =\sum_{i=1}^{n} (T_{\text{actual}}(o_i)+C \cdot (\Phi(S_i)-\Phi(S_{i-1})))
    $$

    $$
    T_{\text{ammortized}}(O)
    =T_{\text{actual}}(O)+C \cdot (\Phi(S_n)-\Phi(S_0))
    $$

    ---

    $$T_{\text{actual}}(O)=T_{\text{ammortized}}(O)-C \cdot (\Phi(S_n)-\Phi(S_0))$$

    $\Phi(S_0)=0$, $\Phi(S_n) \ge 0$이니, $T_{\text{actual}}(O) \le T_{\text{ammortized}}(O)$가 성립한다.

## Example

### Multi-Pop Stack

간단한 예시로, 다음과 같은 두 연산을 지원하는 스택 $S$를 생각하자.

- $S$에 새로운 원소를 하나 추가한다.
- $S$에서 $k$ $(k \le |S|)$개의 원소를 제거한다.

!!! property "Property 2"
    스택 $S$가 다음 두 연산을 지원할 때, $N$개의 연산의 전체 시간복잡도는 $O(N)$이다.
    
    - $S$에 새로운 원소를 하나 추가한다.
    - $S$에서 $k$ $(k \le |S|)$개의 원소를 제거한다.

!!! proof
    Potential function $\Phi(S)=|S|$이라 하자.  
    각 경우에 대하여 $T_{\text{ammortized}}(o)$를 분석하자.

    - $S$에 새로운 원소를 하나 추가할 때는, $T_{\text{actual}}(o)=1$, $\varDelta \Phi(S)=1$이니, $T_{\text{ammortized}}(o)=O(1)$
    - $S$에서 $k$ $(k \le |S|)$개의 원소를 제거할 때는, $T_{\text{actual}}(o)=k$, $\varDelta \Phi(S)=-k$이니, $T_{\text{ammortized}}(o)=O(1)$
  
    따라서, 각 연산의 ammortized 시간복잡도가 $T_{\text{ammortized}}(o)=O(1)$이니, $T_{\text{ammortized}}(O)=O(N)$이고 $T_{\text{actual}}(O) = O(N)$이다.

### Binary Counter

수들을 이진수로 표현할 때, $x=0$에서 시작하여 $x$를 $1$씩 증가시키는 연산을 생각하자.
한 번에 한 개의 비트만 바꿀 수 있을 때, 각 연산의 시간복잡도가 ammortized $O(1)$임을 보이자.

!!! property "Property 3"
    수들을 이진수로 표현할 때, $x=0$에서 시작하여 $x$를 $1$씩 증가시키는 연산을 생각하자.
    한 번에 한 개의 비트만 바꿀 수 있을 때, 각 연산의 시간복잡도는 ammortized $O(1)$이다.

!!! proof
    Potential function $\Phi(x)=x$의 켜진 비트의 수라 하자.

    $$x= ...0111111_{(2)} \rightarrow x= ...1000000_{(2)}$$

    각 연산은 $0$번째 비트부터 연속하여 켜져 있는 비트들을 모두 뒤집는다.  
    따라서 $0$번째 비트부터 연속하여 켜져 있는 비트들이 $k$개일 때, $T_{\text{actual}}(o)=k+1$, $\varDelta \Phi(S)=-k+1$이니, $T_{\text{ammortized}}(o)=2$이다.
  
    따라서, 각 연산의 ammortized 시간복잡도가 $T_{\text{ammortized}}(o)=O(1)$이니, $N$개의 연산에 대해서 $T_{\text{ammortized}}(O)=O(N)$이고 $T_{\text{actual}}(O) = O(N)$이다.

### Dynamic Array

C++의 `std::vector`과 같이 크기를 $1$씩 증가시킬 수 있는 배열을 생각하자.
실제 길이 $n$의 dynamic array를 관리하기 위하여 실제로는 길이 $N$의 배열에 값들을 저장한다.
크기를 $1$ 증가시켜야 되는 상황일 때 다음과 같이 작동한다.

- $n<N$이라면 아직 사용할 수 있는 칸이 남아 있으니 $n$을 $1$ 증가시킨다.
- $n=N$이라면 크기 $N=2n$의 배열로 모든 수들을 옮긴 후 $n$을 $1$ 증가시킨다.

위 알고리즘은 $n \le N \le 2n$이 성립하니, 실제 길이 $n$의 dynamic array를 관리하기 위하여 $O(n)$ 크기의 메모리만 사용함을 알 수 있다.
이제 크기를 $1$ 증가시키는 시간이 ammortized $O(1)$임을 보이자.

!!! property "Property 4"
    Dynamic array의 크기를 $1$ 증가시키는 연산의 시간복잡도는 ammortized $O(1)$이다.

!!! proof
    Potential function $\Phi(S)=2n-N$이라 하자.
    $n \le N \le 2n$에 의해 $\Phi(S) \le 0$이 성립한다.  
    각 경우에 대하여 $T_{\text{ammortized}}(o)$를 분석하자.

    - $n<N$이라면 $T_{\text{actual}}(o)=1$, $\varDelta \Phi(S)=2$이니, $T_{\text{ammortized}}(o)=O(1)$
    - $n=N$이라면 $T_{\text{actual}}(o)=3n$, $\varDelta \Phi(S)=-n$이니, $C=3$으로 설정하면 $T_{\text{ammortized}}(o)=O(1)$

    따라서, 각 연산의 ammortized 시간복잡도가 $T_{\text{ammortized}}(o)=O(1)$이니, $T_{\text{ammortized}}(O)=O(N)$이고 $T_{\text{actual}}(O) \le O(N)$이다.

## Application

Splay tree, segment tree beats, kinetic segment tree 등의 다양한 ammortized 시간복잡도를 갖는 자료구조의 시간복잡도 증명을 potential method를 이용하여 할 수 있다.

[Segment Tree Beats](../../../../algorithms/Data Structures/Segment Tree Beats/algorithm/#complexity)

Merging / Splitting Dynamic Segment Trees

## Reference

- [https://en.wikipedia.org/wiki/Potential_method](https://en.wikipedia.org/wiki/Potential_method)
- [https://algoshitpo.github.io/2020/03/23/PotentialMethod/](https://algoshitpo.github.io/2020/03/23/PotentialMethod/)