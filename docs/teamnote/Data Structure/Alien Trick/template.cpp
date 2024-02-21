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

    void init(int _N) {}

    // For given lambda, calculate dp, cnt, memo, V
    // dp[i] = min(or max)_{j<i} (dp[j] + cost(j, i)*2 - lambda) 
    void solve(ll lambda) {}

    // Get optimal dp[N][K] for given K
    // Returns (answer, restored solution)
    // dp[i][k] = min(or max)_{j<i} (dp[j][k-1] + cost(j, i))
    pair<ll, vector<int>> alien(int K) {}
}