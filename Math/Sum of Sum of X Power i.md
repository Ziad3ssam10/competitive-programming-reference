# Sum of Sum of X power i

```cpp
#include <bits/stdc++.h>
using namespace std;
// given f(n, k) is sum(i^k) from 0 to n
// calculate sum(f(n, i)) for i from 0 to k
// complexity per i is O(i^2)
// so total complexity is ~ O(k^3)
const int K = 105;
typedef __int128_t i128;
const i128 mod = ((i128) 1) << 100;
const i128 modm1 = mod - 1;
typedef unsigned long long ull;

i128 mult(i128 a, i128 b) {
    return (a * b) & modm1;
}

i128 add(i128 a, i128 b) {
    return (a + b + mod) & modm1;
}

i128 egcd(i128 a, i128 b, i128 &x, i128 &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    i128 x1, y1;
    i128 d = egcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

i128 inv(i128 a) {
    i128 x, y;
    i128 g = egcd(a, mod, x, y);
    if (g != 1) return 0;
    return (x % mod + mod) & modm1;
}

i128 nCr[K][K], p[K], s[K];
bitset<K> vis;
//sum of i^k from 1 to n
i128 getSum(i128 n, int k) {
    if (vis[k])
        return s[k];
    vis[k] = 1;
    auto &ret = s[k];
    ret = p[k + 1];
    int sign = 1;
    for (int i = 1; i <= k; i++) {
        ret = add(ret, sign * (mult(nCr[k + 1][i + 1], getSum(n, k - i))));
        sign *= -1;
    }
    int divi = k + 1, ct = 0;
    while (!(divi & 1)) {
        divi >>= 1;
        ct++;
    }
    i128 divInv = inv(divi);
    if (divInv)
        ret = mult(ret, divInv);
    return s[k] = (ret >> ct);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //pascal triangle
    for (int i = 1; i < K; i++) {
        nCr[i][0] = nCr[i][i] = 1;
        for (int j = 1; j < i; j++)
            nCr[i][j] = add(nCr[i - 1][j - 1], nCr[i - 1][j]);
    }
    ull n;
    int k;
    cin >> n >> k;
    p[0] = 1;
    for (int i = 1; i < K; i++)
        p[i] = mult(p[i - 1], n);
    i128 ans = 0;
    for (int i = 0; i <= k; i++)
        ans = add(ans, getSum(n, i));
    cout << (ull) add(ans, 1) << '\n';
}
```
