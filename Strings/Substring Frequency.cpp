// O(n^2)
int mx[N];

void z_function(string &s, int idx) {
    int n = s.size();

    if (mx[idx] + idx == n)
        return;

    vector<int> z(n), cnt(n + 2);
    int l = 0, r = 0;

    for (int i = idx + 1; i < n; i++) {
        if (i < r) {
            z[i] = min(r - i, z[i - l + idx]);
        }
        while (i + z[i] < n && s[z[i] + idx] == s[i + z[i]]) {
            z[i]++;
        }
        cnt[z[i]]++;
        mx[i] = max(mx[i], z[i]);
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }

    cnt[n - idx]++;

    for (int i = n - idx; i > mx[idx]; i--) {
        cnt[i] += cnt[i + 1];
        // edit
    }

}
