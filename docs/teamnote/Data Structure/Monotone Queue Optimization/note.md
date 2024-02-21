# Monotone Queue Optimization

## Problem

!!! definition "Definition 1"
    $a \le b \le c \le d$ 일 때, $cost(a, c) + cost(b, d) \le cost(a, d) + cost(b, c)$ ($cost(a, c) + cost(b, d)$가 $cost(a, d) + cost(b, c)$보다 최적) 라면 $cost(j, i)$를 **monge** 하다고 한다.

$$dp[i] = min_{j<i} (dp[j] + cost(j, i))$$

위와 같은 형태의 점화식에서 $cost(j, i)$가 monge 할 때 $dp[N]$를 구하고, 실제 최적해를 역추적한다.

## Algorithm

!!! property "Property 1"
    $cost(j, i)$가 monge 하니, $p \le q \le x_1 \le x_2$ 에 대해 $cost(p, x_1)-cost(q, x_1) \le cost(p, x_2)-cost(q, x_2)$.  
    $f_p(x) = dp[p] + cost(p, x)$라 하면 $f_p(x_1)-f_q(x_1) \le f_p(x_2)-f_q(x_2)$.

    $f_p(x)-f_q(x)$는 증가함수이다. $(f_p(x)<f_q(x) \ \rightarrow \ f_p(x)=f_q(x) \ \rightarrow \ f_p(x)>f_q(x))$  
    $f_p(x)$와 $f_q(x)$는 대소관계가 정확히 한 번 바뀌니, 직선과 같이 취급할 수 있다.

**Property 1**에 의해, $f_p(x)$는 직선과 같이 관리할 수 있고, 따라서 함수들을 CHT와 비슷한 방법으로 관리한다.
두 함수 $f_p(x)$, $f_q(x)$에 대하여 $cross(p, q)$를 $f_p(x)<f_q(x)$인 최대 $x$로 정의한다.
$cross(p, q)$는 이분탐색을 통하여 구할 수 있다.

최적의 함수 $f_p(x) = dp[p] + cost(p, x)$들을 deque로 관리한다.
`cross(DQ[i-1], DQ[i]) < cross(DQ[i], DQ[i+1])`를 강제한다.
새로운 함수를 추가할 때, 불변식을 만족시키지 않는 직선들을 deque의 위쪽에서 하나씩 제거한 후, 새로운 함수를 스택에 추가한다.
DP값을 구할 때, 한 번 최적해가 아닌 함수는 앞으로도 최적해가 될 수 없음을 이용하여 최적이 아닌 함수들을 앞에서부터 하나씩 제거한 후, 최적해를 구한다.

!!! complexity
    $O(NlogN)$

## Code

``` cpp linenums="1" title="monotone_queue.cpp"
namespace Monotone_Queue
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

    // cost(p, q) must be monge
    ll cost(int p, int q) {}

    // Get maximum x that dp[p]+cost(p, x) < dp[q]+cost(q, x) (p is optimal than q)
    // p < q must hold
    int cross(int p, int q)
    {
        int lo=q, hi=N+1;
        while(lo+1<hi)
        {
            int mid=lo+hi>>1;
            if(dp[p]+cost(p, mid) < dp[q]+cost(q, mid)) lo=mid; // min : <, max : >
            else hi=mid;
        }
        return lo;
    }

    // Get optimal dp[N]
    // dp[i] = min(or max)_{j<i} (dp[j] + cost(j, i)) 
    // changes dp, cnt, memo, V
    void solve()
    {
        // initialize dp, cnt, memo, V, (other data structures)
        for(int i=0; i<=N; i++) dp[i]=cnt[i]=memo[i]=0;
        V.clear();

        deque<int> DQ;
        DQ.push_back(0);

        for(int i=1; i<=N; i++)
        {
            while(DQ.size()>1 && dp[DQ[0]]+cost(DQ[0], i) >= dp[DQ[1]]+cost(DQ[1], i)) DQ.pop_front(); // min : >=, max : <=
            
            // opt = argmin(or max)_{j<i} (dp[j] + cost(j, i))
            int opt = DQ.front();
            dp[i] = dp[opt]+cost(opt, i);
            cnt[i] = cnt[opt]+1;
            memo[i] = opt;

            // cross(DQ[i-1], DQ[i]) < cross(DQ[i], DQ[i+1])
            while(DQ.size()>1 && !(cross(DQ[DQ.size()-2], DQ[DQ.size()-1]) < cross(DQ[DQ.size()-1], i))) DQ.pop_back();
            DQ.push_back(i);
        }
        
        for(int i=N; i>0;)
        {
            V.push_back(i);
            i=memo[i];
        }
        V.push_back(0);
        reverse(V.begin(), V.end());
    }
}
```

## Details

``` cpp linenums="1" title="template"
namespace Monotone_Queue
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

    // cost(p, q) must be monge
    ll cost(int p, int q) {}

    // Get maximum x that dp[p]+cost(p, x) < dp[q]+cost(q, x) (p is optimal than q)
    // p < q must hold
    int cross(int p, int q) {}

    // Get optimal dp[N]
    // dp[i] = min(or max)_{j<i} (dp[j] + cost(j, i)) 
    // changes dp, cnt, memo, V
    void solve() {}
}
```

- `MAXN`이 선언되어야 함
- `void init(int _N) {}` : 초기화
- `ll cost(int p, int q) {}` : $cost(p, q)$의 값을 리턴함
    - 문제 상황에 따라 구현하여 사용함
    - $cost(p, q)$가 monge해야 함
- `int cross(int p, int q) {}` : $dp[p]+cost(p, x)<dp[q]+cost(q, x)$인 최대 $x$를 리턴함
- `void solve() {}` : 최적의 $dp[N]$을 구함 (`dp`, `cnt`, `memo`, `V`를 채움)
    - `dp[i]` : $dp[i]$의 값
    - `cnt[i]` : $dp[i]$까지 사용한 transition의 개수
    - `memo[i]` : $dp[i]$에서 사용한 마지막 transition의 위치
    - `V` : 복구한 최적해
    - `cross(DQ[i-1], DQ[i]) < cross(DQ[i], DQ[i+1])`를 만족함

``` cpp linenums="1" title="example"
void test_monotone_queue()
{
    // min, cost(j, i) = (i-j)*(i-j)+15

    int N=15;
    Monotone_Queue::init(N);
    Monotone_Queue::solve();
    
    assert(Monotone_Queue::dp[N] = 57);
    assert(Monotone_Queue::V == vector<int>({0, 4, 8, 12, 15}));
}
```