namespace SA_LCP
{
    const int MAXN;

    // SA[i] : starting position of i-th suffix when sorted
    // R[i] : lexicographic order of i-th suffix, R[SA[i]]=i
    // LCP[i] : LCP(S[SA[i-1] ...], S[SA[i] ...])
    int SA[MAXN+10], R[MAXN+10], LCP[MAXN+10];

    // R2[i][j] : R[i] when d = 1<<j
    int R2[MAXN+10][21];

    // Get Suffix array, LCP array of S
    // Fill SA[i], R[i], LCP[i]
    // S is 1-based (leading "?")
    void SA_LCP(string S) {}

    // Compare substring, return true if S[l1 ... r1] < S[l2 ... r2]
    bool cmp(int l1, int r1, int l2, int r2) {}
}