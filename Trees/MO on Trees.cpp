int in[N], out[N], ctr, par[N][LG], val[N], n, frq[N];
vector <int> path;
vector <vector <int>> adj;
int curL, curR;
void dfs(int node, int p)
{
    in[node] = ctr++;
    path.push_back(node);
    par[node][0] = p;
    for(int i = 1; i < LG; i++)
        par[node][i] = par[par[node][i - 1]][i - 1];
    
    for(auto &child : adj[node])
        if(p != child)
            dfs(child, node);
    path.push_back(node);
    out[node] = ctr++;
}

bool isPar(int u, int v)
{
    return in[v] >= in[u] && out[v] <= out[u];
}

int lca(int u, int v)
{
    if(isPar(u, v))
        return u;
    if(isPar(v, u))
        return v;
    for(int i = LG - 1; i >= 0; i--)
    {
        if(!isPar(par[u][i], v))
            u = par[u][i];
    }
    return par[u][0];
}
struct Query
{
    int l, r, i, typ, lc;
    Query(int l, int r, int i, int typ, int lc) : l(l), r(r), i(i), typ(typ), lc(lc) {}
    bool operator< (const Query &oth) const
    {
        if(l / SQ != oth.l / SQ)
            return make_pair(l / SQ, r) < make_pair(oth.l / SQ, oth.r);
        if(l / SQ % 2 == 0)
            return r < oth.r;
        else
            return r > oth.r;
    }
};

void rmv(int node)
{
    
}
void add(int node)
{
    
}
void update(int i)
{
    int node = path[i];
    if(frq[node])
        rmv(node);
    else
        add(node);
}

int getAns()
{
    
}

vector <int> mo(vector <Query> &v)
{
    vector <int> ret(v.size());
    sort(v.begin(), v.end());
    curL = 0, curR = -1;
    for(auto &[l, r, i, typ, lc] : v)
    {
        while(curR < r)
            update(++curR);
        while(curL > l)
            update(--curL);
        while(curR > r)
            update(curR--);
        while(curL < l)
            update(curL++);
        if(typ == 2)
            add(lc);
        ret[i] = getAns();
        if(typ == 2)
            rmv(lc);
    }
    return ret;
}
void burn()
{
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> val[i];
    adj = vector <vector <int>> (n + 1);
    for(int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ctr = 0;
    path.clear();
    
    dfs(1, 1);
    
    int q;
    cin >> q;
    vector <Query> queries;
    for(int i = 0; i < q; i++)
    {
        int u, v;
        cin >> u >> v;
        if(in[u] > in[v])
            swap(u, v);
        int lc = lca(u, v), l, r, t = 1;
        if(lc == u)
            l = in[u], r = in[v];
        else
            l = out[u], r = in[v], t++;
        queries.emplace_back(l, r, i, t, lc);
    }
    auto ans = mo(queries);
    for(auto &i : ans)
        cout << i << '\n';
}
