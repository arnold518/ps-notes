typedef unsigned long long ull;

namespace tree_iso
{
    const int MAXV = 1e6;
    
    mt19937 rnd;
    ull rng() { return uniform_int_distribution<ull>()(rnd); }
    
    int N;
    vector<int> adj[MAXV+10];
    int sz[MAXV+10], ht[MAXV+10];
    vector<ull> RA, RB;

    void init_rand(int seed)
    {
        rnd=mt19937(seed);
        RA=vector<ull>(); RB=vector<ull>();
        for(int i=0; i<MAXV; i++) RA.push_back(rng());
        for(int i=0; i<MAXV; i++) RB.push_back(rng());
    }

    void init(int _N)
    {
        N=_N;
        for(int i=1; i<=N; i++) adj[i]=vector<int>();
    }

    void add_edge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void getsz(int now, int bef)
    {
        sz[now]=1;
        for(int nxt : adj[now])
        {
            if(nxt==bef) continue;
            getsz(nxt, now);
            sz[now]+=sz[nxt];
        }
    }

    pii getcen(int now, int bef)
    {
        for(int nxt : adj[now])
        {
            if(nxt==bef) continue;
            if(sz[nxt]*2>=N) return getcen(nxt, now);
        }
        if(sz[now]*2==N) return pii(now, bef);
        return pii(now, 0);
    }

    ull dfs(int now, int bef)
    {
        vector<ull> V;
        ht[now]=0;
        for(int nxt : adj[now])
        {
            if(nxt==bef) continue;
            V.push_back(dfs(nxt, now));
            ht[now]=max(ht[now], ht[nxt]+1);
        }
        V.push_back(1);
        sort(V.begin(), V.end());
        ull ret=0;
        for(int i=0; i<V.size(); i++) ret+=RA[ht[now]]^RB[i]^V[i];
        return ret;
    }

    ull get_hash()
    {
        getsz(1, 1);
        pii cen=getcen(1, 1);
        if(cen.second==0) return dfs(cen.first, cen.first);
        else return dfs(cen.first, cen.second)*dfs(cen.second, cen.first);
    }
}