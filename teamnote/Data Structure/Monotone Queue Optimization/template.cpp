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