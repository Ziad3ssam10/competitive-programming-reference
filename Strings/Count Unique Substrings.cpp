int countUniqueSubs(string &s) {
    ll ans = 0;
    int n = s.length();
    string t = "", rev;
    for (int i = 0; i < n; i++) {
        t += s[i], rev = t, reverse(rev.begin(), rev.end());
        auto z = zFunction(rev);
        ans += (t.size() - *max_element(z.begin(), z.end()));
    }
    return ans;
}
