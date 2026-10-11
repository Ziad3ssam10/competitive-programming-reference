# 3D MO

```cpp
#include <bits/stdc++.h>
using namespace std;
// 1. Set Block Size to N^(2/3)
const int B = 2150;
const int N = 2e5 + 5;

struct Query {
    int l, r, t, id;

    bool operator<(const Query &o) const {
        int l1 = l / B, l2 = o.l / B;
        if (l1 != l2) return l1 < l2;
        int r1 = r / B, r2 = o.r / B;
        if (r1 != r2) return l1 % 2 == 0 ? r1 < r2 : r1 > r2;
        return r1 % 2 == 0 ? t < o.t : t > o.t;
    }
};

struct Update {
    int pos, old_val, new_val;
};

int a[N];
int ans[N], fq[N], fuckFq[N];
vector<Query> queries;
vector<Update> updates;
// =================================================================
// ONLY MODIFY THIS SECTION
// =================================================================
void add(int idx) {
    int &curFq = fq[a[idx]];
    fuckFq[curFq]--;
    curFq++;
    fuckFq[curFq]++;
}

void remove(int idx) {
    int &curFq = fq[a[idx]];
    fuckFq[curFq]--;
    curFq--;
    fuckFq[curFq]++;
}

int get_ans() {
    int cMex{};
    while (fuckFq[cMex]) cMex++;
    return cMex;
}

// =================================================================
map<int,int> toId;
int to(int x) {
    if (toId.count(x)) return toId[x];
    int n = toId.size();
    return toId[x] = n;
}

// Core Mo's Logic (Braindead easy to leave alone)
void apply_update(int t_idx, int L, int R) {
    int p = updates[t_idx].pos;
    if (L <= p && p <= R) remove(p);
    a[p] = updates[t_idx].new_val;
    if (L <= p && p <= R) add(p);
}

void undo_update(int t_idx, int L, int R) {
    int p = updates[t_idx].pos;
    if (L <= p && p <= R) remove(p);
    a[p] = updates[t_idx].old_val;
    if (L <= p && p <= R) add(p);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    fuckFq[0] = 1e9 + 1;
    for (int i = 0; i < n; i++) cin >> a[i], a[i] = to(a[i]);
    // Read queries and updates
    int time_counter = 0;
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            // Query
            int l, r;
            cin >> l >> r;
            l--;
            r--;
            queries.push_back({l, r, time_counter, (int) queries.size()});
        } else {
            // Update
            int pos, val;
            cin >> pos >> val;
            pos--;
            updates.push_back({pos, a[pos], to(val)});
            a[pos] = to(val);
            time_counter++;
        }
    }
    for (int i = (int) updates.size() - 1; i >= 0; i--)
        a[updates[i].pos] = updates[i].old_val;
    sort(queries.begin(), queries.end());
    int L = 0, R = -1, T = 0;
    for (auto &q: queries) {
        while (T < q.t) apply_update(T++, L, R);
        while (T > q.t) undo_update(--T, L, R);
        while (L > q.l) add(--L);
        while (R < q.r) add(++R);
        while (L < q.l) remove(L++);
        while (R > q.r) remove(R--);
        ans[q.id] = get_ans();
    }
    for (int i = 0; i < queries.size(); i++)
        cout << ans[i] << "\n";
    return 0;
}
```
