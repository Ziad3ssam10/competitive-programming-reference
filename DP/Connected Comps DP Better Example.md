# Connected Comps DP better Example

```cpp
int dp[N][N][5][5], n;
/*
dp[i][j][k][l]
i -> processed idx so far
j -> number of components
k -> prev 7rkat brkat (0 , fl nos , 1 kont shamal aw yemen , 2 comp lw7dy)
// l -> facing kam comp
*/
int solve(int i, int j, int k, int l) {
    if (j < 0) return 0;
    if (i == n) return j == 1;
    auto &ret = dp[i][j][k][l];
    if (~ret) return ret;
    ret = 0;
    // lets try to start between 2 comps
    ret = add(ret, mul(solve(i + 1, j + 1, 2, 2), max(j - 1, 0)));
    // start new component on edges
    ret = add(ret, mul(solve(i + 1, j + 1, 2, min(j, 1)), (j ? 2 : 1)));
    // lets try merging 2 comps
    ret = add(ret, mul(solve(i + 1, j - 1, 0, 0), max(0, j - 1 - l)));
    // add to existing with 1 facing
    ret = add(ret, mul(solve(i + 1, j, 1, 1), max(0, 2 * j - 2 - l)));
    // add to existing but on the very edge
    // lw last component el wa7eed mfrod 0    // 2 - 2 - 0 = 0    // tb lw last yemen aw shmal yb2a tre2a wa7da    // 2 - (1 - 0) = 1
    if (j)
        ret = add(ret, mul(solve(i + 1, j, 1, 0), max(0, 2 - (k - l))));
    return ret;
}

void solve() {
    cin >> n;
    cout << solve(0, 0, 0, 0);
}
```
