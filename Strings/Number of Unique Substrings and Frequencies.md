# Number of unique Substrings and frequencies

```cpp
//O(n^2)
struct SubstringFrequency {
    int n;
    string s;
    vector<int> mx, z, cnt;
    long long total_distinct_substrings = 0;
    long long max_length_freq_product = 0;

    SubstringFrequency(const string &str) {
        s = str;
        n = s.size();
        mx.assign(n, 0);
        z.assign(n, 0);
        cnt.assign(n + 2, 0);
    }

    void z_function(int idx) {
        if (mx[idx] + idx == n) return;
        // Reset arrays for this pass
        fill(z.begin(), z.end(), 0);
        fill(cnt.begin(), cnt.end(), 0);
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
        // Suffix sum to calculate exact frequencies of all lengths
        for (int i = n - idx; i > mx[idx]; i--) {
            cnt[i] += cnt[i + 1];
            // Every length strictly greater than mx[idx] represents a new distinct substring
            total_distinct_substrings++;
            // process the frequency of this unique substring
            long long current_freq = cnt[i];
            long long length = i;
            max_length_freq_product = max(max_length_freq_product, length * current_freq);
        }
    }

    void process_all() {
        for (int i = 0; i < n; i++) {
            z_function(i);
        }
    }
};
```
