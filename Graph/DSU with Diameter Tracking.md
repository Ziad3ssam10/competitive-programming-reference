# DSU with Diameter Tracking

```cpp
// --- 1. LCA and Distance Precomputation ---
// Take tree offline to add to TreeDistance struct
// Loop on queries again and use the DSU
struct TreeDistance {
    int n, log;
    vector<array<int, 20> > up;
    vector<int> depth;

    TreeDistance(int n, int log_max = 20) : n(n), log(log_max) {
        up.assign(n + 1, {});
        for (int i = 0; i <= n; i++) {
            up[i].fill(-1);
        }
        depth.assign(n + 1, 0);
    }

    void dfs(const vector<vector<int> > &adj, int u, int p, int d) {
        up[u][0] = p;
        depth[u] = d;
        for (int i = 1; i < log; i++) {
            if (up[u][i - 1] != -1) {
                up[u][i] = up[up[u][i - 1]][i - 1];
            } else {
                up[u][i] = -1;
            }
        }
        for (int v: adj[u]) {
            if (v != p) dfs(adj, v, u, d + 1);
        }
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < log; i++) {
            if ((diff >> i) & 1) u = up[u][i];
        }
        if (u == v) return u;
        for (int i = log - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    int get_dist(int u, int v) {
        if (u == -1 || v == -1) return -1;
        int lca = get_lca(u, v);
        // SAFETY FIX: Prevent Segfault if u and v are in different offline components
        if (lca == -1) return -1;
        return depth[u] + depth[v] - 2 * depth[lca];
    }
};

// --- 2. DSU with Diameter Tracking ---
struct DSU {
    vector<int> parent, sz, end1, end2, diam;
    TreeDistance *td;

    DSU(int n, TreeDistance *tree_dist) {
        parent.resize(n + 1);
        sz.resize(n + 1, 1);
        end1.resize(n + 1);
        end2.resize(n + 1);
        diam.resize(n + 1, 0);
        td = tree_dist;
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            end1[i] = i;
            end2[i] = i;
        }
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i == root_j) return false;
        if (sz[root_i] < sz[root_j]) swap(root_i, root_j);
        int u1 = end1[root_i], u2 = end2[root_i];
        int v1 = end1[root_j], v2 = end2[root_j];
        // OPTIMIZATION: Raw array avoids dynamic memory allocations during DSU merges
        int nodes[4] = {u1, u2, v1, v2};
        int max_d = -1;
        pair<int, int> best_pair;
        for (int a = 0; a < 4; a++) {
            for (int b = a + 1; b < 4; b++) {
                int d = td->get_dist(nodes[a], nodes[b]);
                if (d > max_d) {
                    max_d = d;
                    best_pair = {nodes[a], nodes[b]};
                }
            }
        }
        parent[root_j] = root_i;
        sz[root_i] += sz[root_j];
        end1[root_i] = best_pair.first;
        end2[root_i] = best_pair.second;
        diam[root_i] = max_d;
        return true;
    }

    int get_max_diameter(int u) {
        return diam[find(u)];
    }
};
```
