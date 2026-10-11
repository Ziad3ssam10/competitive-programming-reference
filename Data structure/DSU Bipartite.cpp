struct DSU {
    vector<int> pr, sz, odd;
    
    DSU(int n) {
        pr.resize(n + 5);
        sz.resize(n + 5);
        odd.resize(n + 5);
        
        for (int i = 0; i <= n; ++i) {
            pr[i] = i;
            sz[i] = 1;
            odd[i] = 0;
        }
    }
    
    DSU() {
    }
    
    pair<int, bool> find(int x) {
        if (pr[x] == x)
            return {x, 0};
        auto it = find(pr[x]);
        odd[x] ^= it.second;
        pr[x] = it.first;
        return {it.first, odd[x]};
    }
    
    bool UNI(int x, int y) {
        auto a = find(x), b = find(y);
        
        if (a.first == b.first)
            return odd[x] != odd[y];
        
        x = a.first, y = b.first;
        if (sz[x] < sz[y])
            swap(x, y);
        
        pr[y] = x;
        sz[x] += sz[y];
        odd[y] = (a.second == b.second);
        return 1;
    }
    
}dsu;
