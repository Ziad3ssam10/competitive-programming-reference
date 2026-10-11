// O(number of starts * n^2)
//Using at most X nodes
//give start, access d[number of nodes taken][destination]
vector<vector<ll>> billman(int st, int n, vector <vector <pair <int, ll>>>& adj){
    vector<vector<ll>> d(n+1, vector<ll>(n+1, 1e18));
    d[0][st] = 0;
    for(int i = 1; i <= n; i++)
        for (int u = 1; u <= n; u++) {
            d[i][u] = min(d[i][u], d[i-1][u]);
            for (auto [v, w] : adj[u])
                d[i][v] = min(d[i][v], d[i-1][u]+w);
        }
    return d;
}
