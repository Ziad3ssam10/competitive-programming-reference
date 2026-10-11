// flow * edges
struct Edge {
    int to;
    int cost;
    int cap, flow, backEdge;
};

struct MCMF {
    const int inf = 1000000010;
    int n;
    int s, t;
    vector<vector<Edge>> g;
    vector<int> state, pr, e;
    vector<int> d;
    deque<int> q;

    MCMF(int n, int s, int t) : n(n), s(s), t(t) {
        g.resize(n);
        state.resize(n);
        pr.resize(n);
        e.resize(n);
        d.resize(n);
    }

    void addEdge(int u, int v, int cap, int cost) {
        Edge e1 = {v, cost, cap, 0, (int) g[v].size()};
        Edge e2 = {u, -cost, 0, 0, (int) g[u].size()};
        g[u].push_back(e1);
        g[v].push_back(e2);
    }

    void bfs() {
        for (int i = 0; i < n; i++)
            state[i] = 2, d[i] = inf, pr[i] = -1;
        state[s] = 1;
        q.clear();
        q.push_back(s);
        d[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            state[v] = 0;
            for (int i = 0; i < (int) g[v].size(); i++) {
                Edge c = g[v][i];
                if (c.flow >= c.cap || (d[c.to] <= d[v] + c.cost))
                    continue;
                int to = c.to;
                d[to] = d[v] + c.cost;
                pr[to] = v;
                e[to] = i;
                if (state[to] == 1) continue;
                if (!state[to] || (!q.empty() && d[q.front()] > d[to]))
                    q.push_front(to);
                else q.push_back(to);
                state[to] = 1;
            }
        }
    }

    pair<int, int> minCostMaxFlow(int k) {
        int flow = 0;
        int cost = 0;
        while (flow < k) {
            bfs();
            if (d[t] == inf) break;
            int it = t, addflow = inf;
            while (it != s) {
                addflow = min(addflow,
                              g[pr[it]][e[it]].cap
                              - g[pr[it]][e[it]].flow);
                it = pr[it];
            }
            if (addflow)
                addflow = min(k - flow, addflow);
            it = t;
            while (it != s) {
                g[pr[it]][e[it]].flow += addflow;
                g[it][g[pr[it]][e[it]].backEdge].flow -= addflow;
                cost += g[pr[it]][e[it]].cost * addflow;
                it = pr[it];
            }
            flow += addflow;
        }
        if (flow < k)
            return {-1, -1};
        return {cost, flow};
    }
};
