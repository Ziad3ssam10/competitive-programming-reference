int add(int a, int b) {
    return (1ll * a + b + mod) % mod;
}
 
int mul(int a, int b) {
    return (1ll * a * b) % mod;
}
 
struct Matrix {
    vector<vector<int>> mat;
    Matrix(int n, int m, int val = 0){
        mat = vector<vector<int>>(n, vector<int>(m, val));
    }
    Matrix(int n) : Matrix(n, n){
        for(int i = 0; i < n; i++) mat[i][i] = 1;
    }
    Matrix operator *(const Matrix& oth) const {
        int n = this->mat.size();
        int m = oth.mat[0].size();
        int k = this->mat[0].size();
        assert(this->mat[0].size() == oth.mat.size());
        Matrix ret(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int l = 0; l < k; l++)
                    ret.mat[i][j] = add(ret.mat[i][j], mul(mat[i][l], oth.mat[l][j]));
        return ret;
    }
};

Matrix fp(Matrix& mt, ll exp) {
    if (exp == 0)
        return Matrix(mt.mat.size());
    Matrix ret = fp(mt, exp >> 1ll);
    ret = ret * ret;
    if (exp & 1)
        ret = ret * mt;
    return ret;
}
