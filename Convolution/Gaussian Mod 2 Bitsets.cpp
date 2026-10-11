int gauss (int n, int m, bitset<N> & ans) {
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        for (int i=row; i<n; ++i)
            if (v[i][col]) {
                swap (v[i], v[row]);
                break;
            }
        if (! v[row][col])
            continue;
        where[col] = row;
        
        for (int i=0; i<n; ++i)
            if (i != row && v[i][col])
                v[i] ^= v[row];
        ++row;
    }
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = v[where[i]][m];
    for (int i=0; i<n; ++i) {
        int sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * v[i][j];
        if (sum != v[i][m])
            return 0;
    }
    
    for (int i=0; i<m; ++i)
        if (where[i] == -1 && isVariable[i])
            return INF;
    return 1;
}
