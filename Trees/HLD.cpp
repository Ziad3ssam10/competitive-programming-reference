int par[N] , heavy[N] , head[N] , dep[N] , pos[N] , sz[N] , curPos;
vector<int> adj[N];

void dfs(int node , int p)
{
    sz[node] = 1;
    int mx_sz = 0;
    for(auto ch : adj[node])
    {
        if (ch == p) continue;
        par[ch] = node , dep[ch] = dep[node] + 1;
        dfs(ch , node);
        sz[node] += sz[ch];
        if (sz[ch] > mx_sz)
            mx_sz = sz[ch] , heavy[node] = ch;
    }
}

void hld(int node , int p , int h)
{
    head[node] = h , pos[node] = ++curPos;
    if (heavy[node] != 0)
        hld(heavy[node] , node , h);

    for(auto ch : adj[node])
    {
        if (ch != p && ch != heavy[node])
            hld(ch , node , ch);
    }
}

int get(int a , int b) //be careful if long long
{
    int res = 0;
    for(; head[a] != head[b]; b = par[head[b]])
    {
        if (dep[head[a]] > dep[head[b]])
            swap(a , b);

        int curMx = seg_tree_query(pos[head[b]] , pos[b]);
        res = max(res , curMx);
    }

    if (dep[a] > dep[b])
        swap(a , b);

    int curMx = seg_tree_query(pos[a] , pos[b]); //be careful if the query is on edges, not nodes
    res = max(res , curMx);
    return res;
}
