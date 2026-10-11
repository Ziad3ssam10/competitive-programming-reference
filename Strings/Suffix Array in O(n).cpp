struct SFX {
    using vi = vector<int>;
#define all(s) s.begin() , s.end()
#define rep(a, b) for(int i=a;i<b;i++)

    vi sa, lcp;

    SFX(string s, int lim = 256) {
        int n = s.size() + 1, k = 0, a, b;
        vi x(all(s) + 1), y(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            fill(all(ws), 0);
            rep(0, n) ws[x[i]]++;
            rep(1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;)sa[--ws[x[y[i]]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(1, n) a = sa[i - 1], b = sa[i], x[b] =
                (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        }
        rep(1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k&& k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k];
                k++);
    }
};