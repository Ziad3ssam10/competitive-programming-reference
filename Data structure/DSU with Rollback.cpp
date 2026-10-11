struct Elem {
    int u, v, szU;
};

struct DSU_ROLLBACK {
    int cnt;
    stack<Elem> st;
    stack<int> checkpoint;
    vector<int> sz, par;

    DSU_ROLLBACK(int n) {
        cnt = n;
        par.resize(n + 2);
        sz.resize(n + 2, 1);
        iota(par.begin(), par.end(), 0);
    }

    int rollback() {
        int x = checkpoint.top();
        checkpoint.pop();
        while (st.size() > x) {
            auto e = st.top();
            st.pop();
            par[e.v] = e.v;
            sz[e.u] = e.szU;
            cnt++;
        }
        return cnt;
    }

    int findSet(int u) {
        return par[u] == u ? par[u] : findSet(par[u]);
    }

    void update(int u, int v) {
        st.push({u, v, sz[u]});
        cnt--;
        par[v] = u;
        sz[u] += sz[v];
    }

    void unionSet(int u, int v) {
        u = findSet(u);
        v = findSet(v);
        if (u != v) {
            if (sz[u] < sz[v])
                swap(u, v);
            update(u, v);
        }
    }

    void persist() {
        checkpoint.push(st.size());
    }
    
};
