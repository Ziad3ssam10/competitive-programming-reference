sort(vals.begin(), vals.end());
vals.erase(unique(vals.begin(), vals.end()), vals.end());
// to get a value, 0-based
ll x;
x = std::lower_bound(vals.begin(), vals.end(), x) - vals.begin();
// to reverse
x = vals[x];
