struct graph
{
    vector <vector <int>> adj;
    vector <bool> vis,used;
    vector <int> mt;
    int l, r;
    graph(int l, int r)
    {
        this->l = l;
        this->r = r;
        adj.resize(l + r + 10);
        vis.resize(l + 1);
        mt.resize(l + r + 1, -1);
        used.resize(n + 1);
    }
    void addEdge(int u, int v)
    {
        adj[u].push_back(l + v);
    }
    bool try_kuhn(int u)
    {
        if(vis[u])
            return false;
        vis[u] = 1;
        for(auto &child : adj[u])
        {
            if(mt[child] == -1 || try_kuhn(mt[child]))
            {
                mt[child] = u;
                return true;
            }
        }
        return false;
    }
    int max_matching()
    {
        int ret = 0;
        for(int i = 1; i <= l; i++)
        {
            for(auto &j : adj[i])
            {
                if(mt[j] == -1)
                {
                    mt[j] = i;
                    used[j] = 1;
                    break;
                }
            }
        }
        for(int i = 1; i <= l; i++)
        {
            if(used[i])
            {
                ret++;
                continue;
            }
            vis = vector <bool> (l + 1, 0);
            ret += try_kuhn(i);
        }
        return ret;
    }
    vector <pair <int, int>> getMatches()
    {
        vector <pair <int, int>> ret;
        for(int i = l + 1; i <= l + r; i++)
        {
            if(mt[i] != -1)
                ret.emplace_back(mt[i], i - l);
        }
        return ret;
    }
};
