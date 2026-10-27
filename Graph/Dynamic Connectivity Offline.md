# Dynamic Connectivity Offline

The **Dynamic Connectivity Problem** asks how we can efficiently maintain the connected components of a network as new connections (edges) are dynamically added over time.

Imagine you have a set of $N$ isolated computers. Over time, you run cables between pairs of computers. At any given moment, you need to be able to instantly answer the question: _Is computer A connected to computer B, either directly or through a chain of other computers?_

To solve this efficiently, computer scientists use a specialized data structure called **Union-Find** (also known as a Disjoint-Set).

1. Add an edge to the graph
2. Delete an edge from the graph
3. Count the number of connected components in the graph

```cpp



struct DSU {
    vector<int> parent, sz;
    int components;
    int ans = 0;

    struct Action {
        int u, v;
        bool merged;
        int ans;
    };

    stack<Action> history;

    DSU(int n) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return find_set(parent[v]);
    }

    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);

        if (a == b) {
            history.push({a, b, 0, ans});
            return 0;
        }

        if (sz[a] < sz[b])
            swap(a, b);

        history.push({a, b, 1, ans});

        parent[b] = a;
        ans -= sz[a] - 1;
        ans -= sz[b] - 1;
        sz[a] += sz[b];
        ans += sz[a] - 1;
        components--;

        return 1;
    }

    void rollback() {
        Action act = history.top();
        history.pop();

        if (!act.merged) return;

        int a = act.u;
        int b = act.v;

        parent[b] = b;
        sz[a] -= sz[b];
        components++;
        ans = act.ans;
    }
};

struct QueryTree {
    vector<vector<pair<int, int> > > tree;
    int T, n;
    DSU dsu;

    vector<bool> is_query;
    vector<int> res;

    QueryTree(int _n, int _T) : n(_n), T(_T), dsu(_n) {
        tree.resize(T * 4 + 5);
        is_query.assign(T, 0);
        res.assign(T, 0);
    }

    void add_edge_interval(int node, int l, int r, int ql, int qr, pair<int, int> edge) {
        if (l > qr || r < ql) return;

        if (ql <= l && r <= qr) {
            tree[node].push_back(edge);
            return;
        }

        int mid = l + (r - l) / 2;

        add_edge_interval(2 * node, l, mid, ql, qr, edge);
        add_edge_interval(2 * node + 1, mid + 1, r, ql, qr, edge);
    }

    void dfs(int node, int l, int r) {
        int snapshot = 0;
        stack<DSU::Action> backup;

        for (const auto &edge: tree[node])
            dsu.union_sets(edge.first, edge.second);

        if (l == r) {
            if (is_query[l])
                res[l] = dsu.ans;
        } else {
            int mid = l + (r - l) / 2;
            dfs(2 * node, l, mid);
            dfs(2 * node + 1, mid + 1, r);
        }

        for (size_t i = 0; i < tree[node].size(); i++)
            dsu.rollback();
    }

    void add_edge(pair<int, int> edge, int l, int r) {
        if (l > r) return;
        add_edge_interval(1, 0, T - 1, l, r, edge);
    }

    void add_query(int idx) {
        is_query[idx] = 1;
    }

    void build() {
        if (T > 0)
            dfs(1, 0, T - 1);
    }
};

void solve(int tc) {
    int n, m, q;
    cin >> n >> m >> q;
    QueryTree dc(n + 2, q + 1);
    vector<pair<int, int> > edges(m);
    vector<int> lst(m, 0);
    for (auto &[l, r]: edges) {
        cin >> l >> r;
        r++;
    }
    dc.add_query(0);
    for (int i = 1; i <= q; i++) {
        int p, l, r;
        cin >> p >> l >> r;
        p--;
        dc.add_edge(edges[p], lst[p], i - 1);
        edges[p] = {l, r + 1};
        lst[p] = i;
        dc.add_query(i);
    }
    for (int i = 0; i < m; i++)
        dc.add_edge(edges[i], lst[i], q);
    dc.build();
    for (int i = 0; i <= q; i++)
        cout << dc.res[i] << "\n";
    cout << endl;
}


signed main() {
    fast_io
    files();
    int t = 1;
    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}

```
