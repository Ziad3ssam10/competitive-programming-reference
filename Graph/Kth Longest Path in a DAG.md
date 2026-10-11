# Kth Longest Path in a DAG

Eppstein's algorithm restricted to DAGs, used to enumerate the **k-th largest** path values (edges are negated so Eppstein's shortest-path machinery yields the largest paths).

- Time Complexity: `O(V + E log V + K log K)`
- Memory Complexity: `O(V + E + V log E + K)`
- Works on DAGs only. Nodes must be topologically ordered (`0 .. n-1`), with `src <= dest`.

```cpp
const ll INF = 1e18;
// WORKS ON DAGS ONLYYY!!!!!!
// TIME COMPLEXITY : O(V + E log V + K log K)
// Memory Complexity : O(V + E + V log E + K)
template<typename T>
struct heap
{
    struct node
    {
        int ch[2] = {0, 0};
        int sz = 0;
        T val = 0;
        int from = 0, to = 0;
    };
    static vector<node> pool;
    static void init_pool()
    {
        pool.clear();
        pool.push_back(node()); // index 0 acts as our null pointer
    }
    static int new_node(int orig)
    {
        pool.push_back(pool[orig]);
        return pool.size() - 1;
    }
    static int new_node(T val, int from, int to)
    {
        node n;
        n.sz = 1;
        n.val = val;
        n.from = from;
        n.to = to;
        pool.push_back(n);
        return pool.size() - 1;
    }
    int root = 0;
    heap(int t = 0) : root(t) {}
    static int meld(int a, int b)
    {
        if(!a)
            return b; // Do NOT copy b! Share the memory!
        if(!b)
            return a;
        if(pool[a].val > pool[b].val)
            swap(a, b);
        int res = new_node(a); // Only copy the root of 'a'
        pool[res].ch[1] = meld(pool[res].ch[1], b);
        if(!pool[res].ch[0] || pool[pool[res].ch[0]].sz < pool[pool[res].ch[1]].sz)
            swap(pool[res].ch[0], pool[res].ch[1]);
        pool[res].sz = (pool[res].ch[1] ? pool[pool[res].ch[1]].sz : 0) + 1;
        return res;
    }
    static int np_meld(int a, int b) // non-persistent meld
    {
        if(!a)
            return b;
        if(!b)
            return a;
        if(pool[a].val > pool[b].val)
            swap(a, b);
        pool[a].ch[1] = np_meld(pool[a].ch[1], b);
        if(!pool[a].ch[0] || pool[pool[a].ch[0]].sz < pool[pool[a].ch[1]].sz)
            swap(pool[a].ch[0], pool[a].ch[1]);
        pool[a].sz = (pool[a].ch[1] ? pool[pool[a].ch[1]].sz : 0) + 1;
        return a;
    }
    heap meld(heap b) { return heap(meld(root, b.root)); }
    heap insert(T x, int from, int to)
    {
        return heap(meld(root, new_node(x, from, to)));
    }
    T top() { return root ? pool[root].val : T(-1); }
    bool empty() { return !root; }
};
template<typename T>
vector<typename heap<T>::node> heap<T>::pool;

vector<vector<array<int, 3>>> g;
vector<vector<array<int, 3>>> rg;

vector<ll> Eppstein(int n, int src, int dest, int k)
{
    // 0 indexed, directed graph
    vector<ll> d(n, INF);
    vector<int> par(n, -1);
    vector<int> idx(n, -1);
    vector<vector<int>> t(n);
    d[dest] = 0;
    for(int u = dest - 1; u >= src; --u)
    {
        for(auto [v, cost, id] : rg[u])
        {
            if(d[v] != INF && d[u] > d[v] + cost)
            {
                d[u] = d[v] + cost;
                par[u] = v;
                idx[u] = id;
            }
        }
    }
    for(int i = 0; i < n; ++i)
    {
        if(par[i] != -1)
            t[par[i]].push_back(i);
    }
    heap<ll>::init_pool();
    vector<heap<ll>> h(n);
    for(int i = 0; i < n; ++i)
        h[i] = heap<ll>();
    queue<int> q;
    q.emplace(dest);
    while(!q.empty())
    {
        auto u = q.front();
        q.pop();
        // 1. Inherit the parent's persistent heap
        if(par[u] != -1)
            h[u] = h[par[u]];
        // 2. Build a local heap of the non-tree edges non-persistently
        int local_root = 0;
        for(auto [v, cost, id] : rg[u])
        {
            if(id != idx[u])
            {
                int n_node = heap<ll>::new_node(cost - d[u] + d[v], u, v);
                local_root = heap<ll>::np_meld(local_root, n_node);
            }
        }
        // 3. Persistently meld the parent heap together with the local edges
        if(local_root) h[u] = h[u].meld(heap<ll>(local_root));
        for(auto v : t[u])
            q.emplace(v);
    }
    auto comp = [](auto s, auto t)
    {
        return get<0>(s) > get<0>(t);
    };
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, decltype(comp)> Q(comp);
    heap<ll> s;
    s = s.insert(d[src], -1, src);
    Q.emplace(d[src], s.root);
    vector<ll> ans;
    while(!Q.empty())
    {
        auto [w, cur] = Q.top();
        Q.pop();
        if(w >= INF / 2)
            break;
        ans.push_back(w);
        if(ans.size() == k)
            break;
        if(heap<ll>::pool[cur].ch[0])
        {
            int nxt = heap<ll>::pool[cur].ch[0];
            Q.emplace(w + heap<ll>::pool[nxt].val - heap<ll>::pool[cur].val, nxt);
        }
        if(heap<ll>::pool[cur].ch[1])
        {
            int nxt = heap<ll>::pool[cur].ch[1];
            Q.emplace(w + heap<ll>::pool[nxt].val - heap<ll>::pool[cur].val, nxt);
        }
        int to = heap<ll>::pool[cur].to;
        if(h[to].root)
            Q.emplace(w + heap<ll>::pool[h[to].root].val, h[to].root);
    }
    while(ans.size() < k)
        ans.push_back(-1); // Pad if necessary
    return ans;
}

int edgeCnt;
void addEdge(int u, int v, int w)
{
    w *= -1; // negate so we get the k-th LARGEST path
    rg[u].push_back({v, w, edgeCnt});
    g[v].push_back({u, w, edgeCnt});
    edgeCnt++;
}
```
