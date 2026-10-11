# Parallel Binary search

```cpp
//question is, given u, v when is pair (u, v) first connected
vector <pair <int, int>> queries(q);
vector <int> L(q), R(q), ans(q, -1);
vector <vector <int>> buckets(m + 1);
for(int i = 0; i < q; i++)
{
    int u, v;
    cin >> u >> v;
    queries[i] = {u, v};
    L[i] = 0, R[i] = m;
}
auto add = [&] ()
{
    for(int i = 0; i < q; i++)
        if(L[i] <= R[i])
            buckets[(L[i] + R[i]) / 2].push_back(i);
};
int c = 20;
while(c--)
{
    DSU dsu(n);
    for(int i = 0; i <= m; i++)
    {
        if(i)
            dsu.merge(edges[i - 1].first, edges[i - 1].second);
        for(auto &j : buckets[i])
        {
            auto [u, v] = queries[j];
            if(dsu.find(u) == dsu.find(v))
                ans[j] = i, R[j] = i - 1;
            else
                L[j] = i + 1;
        }
        buckets[i].clear();
    }
}
for(auto &i : ans)
    cout << i << '\n';
```
