struct gph {
    int l, r;
    vector<vector<int>> adj;

    gph(int l, int r) : l(l), r(r), adj(l + 1) {}

    void add(int u, int v) {
        adj[u].push_back(v + l);
    }

    int max_match() {
        vector<int> mt(l + r + 1, -1), lv(l + 1);
        auto levlize = [&]() {
            queue<int> q;
            for (int i = 1; i <= l; i++) {
                lv[i] = -1;
                if (mt[i] < 0) {
                    q.push(i);
                    lv[i] = 0;
                }
            }
            while (q.size()) {
                int nd = q.front();
                q.pop();
                for (auto& i : adj[nd]) {
                    int v = mt[i];
                    if (v < 0)
                        return 1;
                    if (lv[v] < 0)
                        lv[v] = lv[nd] + 1, q.push(v);
                }
            }
            return 0;
            };

        function<bool(int)> agm = [&](int nd) -> int {
            for (auto& i : adj[nd]) {
                int v = mt[i];
                if (v < 0 || (lv[v] > lv[nd] && agm(v))) {
                    mt[nd] = i;
                    mt[i] = nd;
                    return 1;
                }
            }
            return 0;
            };

        int r = 0;
        while (levlize()) {
            for (int i = 1; i <= l; i++)
                if (mt[i] < 0 && agm(i))
                    r++;
        }
        return r;
    }
};