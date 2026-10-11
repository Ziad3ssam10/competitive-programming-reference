int add(int a, int b) {
    return (1ll * a + b + mod) % mod;
}
 
int mul(int a, int b) {
    return (1ll * a * b) % mod;
}
 
int fp(int a, int b) {
    if (!b)
        return 1;
    int ret = fp(a, b / 2);
    ret = mul(ret, ret);
    return (b & 1 ? mul(ret, a) : ret);
}
 
int modInverse(int a) {
    return fp(a, mod - 2);
}
 
struct GaussianMod {
    int n, m, frev = 0;
    bool hasSol = true;
    vector<vector<int> > mat;
 
    GaussianMod(vector<vector<int> > mat) : n(int(mat.size())), m(int(mat[0].size()) - 1), mat(mat) {
    }
 
    void build() {
        for (int r = 0, c = 0; r < n && c < m; r++, c++) {
            int pvr = r;
            for (int j = r + 1; j < n; j++) {
                if (mat[j][c] > mat[pvr][c])
                    pvr = j;
            }
            if (pvr != r)
                swap(mat[pvr], mat[r]);
            int inv = modInverse(mat[r][c]);
            if (mat[r][c] == 0) {
                frev++;
                r--;
                continue;
            }
            for (int j = m; j >= c; j--)
                mat[r][j] = mul(mat[r][j], inv);
 
            for (int i = 0; i < n; i++) {
                if (i == r || !mat[i][c])
                    continue;
                for (int j = m; j >= c; j--)
                    mat[i][j] = add(mat[i][j], -mul(mat[r][j], mat[i][c]));
            }
        }
        for (int i = 0; i < n; i++) {
            bool z = 1;
            for (int j = 0; j < m; j++)
                z &= mat[i][j] == 0;
            if (z) {
                z &= mat[i][m] == 0;
                hasSol &= z;
            }
        }
    }
};
