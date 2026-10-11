struct node
{
    int sum;
    node * l , * r;
    node(int val) : l(nullptr) , r(nullptr) , sum(val) {}
    node(node *l , node *r) : l(l) , r(r) , sum(0)
    {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
}* root[N];

void extend(node *tmp)
{
    if (!tmp->l) tmp->l = new node(0);
    if (!tmp->r) tmp->r = new node(0);
}

node *update(node *prv , int st , int en , int idx , int val)
{
    if (st == en)
        return new node((prv->sum+ val));
    
    extend(prv);
    int mid = (st+en) >> 1;
    if (st <= idx && idx <= mid)
        return new node(update(prv->l , st , mid , idx , val) , prv->r);
    else
        return new node(prv->l , update(prv->r , mid+1 , en , idx , val));
}

int query(node *u , node *v , node *lca , node * par , int st , int en)
{
    if (st == en)
        return st;
    
    extend(u);
    extend(v);
    extend(lca);
    extend(par);
    int sm = u->l->sum + v->l->sum - lca->l->sum - par->l->sum;
    int mid = (st+en) >> 1;
    
    if(something)
        return query(u->r, v->r, lca->r, par->r, mid+1, en);
    else
        return query(u->l , v->l , lca->l , par->l , st , mid);
}


vector<int> adj[N];
int sp[N][20] , lvl[N] , in[N] , out[N] , tim , lg = 20;

void dfs(int node , int par)
{
    lvl[node] = lvl[par]+1;
    sp[node][0] = par;
    if (!par) sp[node][0] = 1;
    in[node] = ++tim;
    
    root[node] = update(root[par] , 1 , N , your_val , 1);
    
    for(int i=1; i<lg; i++)
    {
        int tmp = sp[node][i-1];
        sp[node][i] = sp[tmp][i-1];
    }
    
    for(auto ch : adj[node])
    {
        if (ch != par) dfs(ch , node);
    }
    out[node] = tim;
}

bool is_ancestor(int u, int v)
{
    return in[u] <= in[v] && out[u] >= out[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    
    for (int i = lg-1; i >= 0; --i)
    {
        if (!is_ancestor(sp[u][i], v))
            u = sp[u][i];
    }
    return sp[u][0];
}


void solve()
{
    int q;
    
    root[0] = new node(0);
    dfs(1, 0);
    
    cin >> q;
    while(q--) {
        int v , u;
        cin >> v >> u;
        
        int lc = lca(v , u);
        int par = sp[lc][0];
        if (lc == 1) par = 0;
        
        cout << query(root[u], root[v], root[lc], root[par], 1, N) << "\n";
    }
}
