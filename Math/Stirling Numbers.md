# Stirling Numbers

```cpp
// Precomputes Stirling Numbers of the First Kind (Unsigned)
// s[n][k] = ways to arrange n elements into k disjoint cycles
// Time: O(N * K) | Space: O(N * K)
vector<vector<long long>> precompute_stirling_first(int n, int k) {
    vector<vector<long long>> s(n + 1, vector<long long>(k + 1, 0));
    s[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i && j <= k; j++) {
            // New cycle OR insert after any of the (i-1) existing elements
            s[i][j] = (s[i - 1][j - 1] + (i - 1LL) * s[i - 1][j]) % MOD;
        }
    }
    return s;
}
// Precomputes Stirling Numbers of the Second Kind
// S[n][k] = ways to partition n elements into k non-empty subsets
// Time: O(N * K) | Space: O(N * K)
vector<vector<long long>> precompute_stirling_second(int n, int k) {
    vector<vector<long long>> S(n + 1, vector<long long>(k + 1, 0));
    S[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i && j <= k; j++) {
            // New subset OR join any of the j existing subsets
            S[i][j] = (S[i - 1][j - 1] + 1LL * j * S[i - 1][j]) % MOD;
        }
    }
    return S;
}
```
