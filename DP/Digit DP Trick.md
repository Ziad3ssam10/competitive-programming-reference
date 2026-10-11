# Digit DP Trick

```cpp
const int N = 3000;
int prime[N];
int dp[20][200][2000];
char num[20];

int solve(int idx, bool tight,int sum,int sum2) {
    if (idx == 0) {
        return prime[sum] and prime[sum2];
    }

    if (!tight and dp[idx][sum][sum2] != -1) {
        return dp[idx][sum][sum2];
    }
    int limit = tight ? (num[19 - idx] - '0') : 9;
    int ans = 0;
    for (int d = 0; d <= limit; d++) {
        bool next_tight = tight and (d == limit);
        ans += solve(idx - 1, next_tight, sum + d, sum2 + d * d);
    }
    if (!tight) {
        dp[idx][sum][sum2] = ans;
    }
    return ans;
}

int count(int x) {
    if (x < 0) return 0;
    for (int i = 0; i < 19; i++) {
        num[18 - i] = char('0' + x % 10);
        x /= 10;
    }

    return solve(19, 1, 0, 0);
}

void solve(int tc) {
    int l, r;
    cin >> l >> r;
    cout << count(r) - count(l - 1) << endl;
}


signed main() {
    fast_io
    files();
    memset(prime, 1, sizeof(prime));
    prime[0] = prime[1] = 0;
    for (int p = 2; p * p < N; p++) {
        if (prime[p]) {
            for (int i = p * p; i < N; i += p) {
                prime[i] = 0;
            }
        }
    }
    memset(dp, -1, sizeof dp);
    int t = 1;
    cin >> t;
    int tc = 1;
    while (t--)
        solve(tc++);
}
```
