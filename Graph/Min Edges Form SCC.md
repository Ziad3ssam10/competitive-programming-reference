# Min edges Form SCC

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> graph[N];
int owner[N];
int id[N], cmp[N];
bool instk[N];
int timer = 1;

void SCCDFS(int node, stack<int> &st) {
    id[node] = cmp[node] = timer++;
    st.push(node);
    instk[node] = true;
    for (auto child: graph[node]) {
        if (!id[child])
            SCCDFS(child, st);
        if (instk[child])
            cmp[node] = min(cmp[node], cmp[child]);
    }
    if (id[node] == cmp[node]) {
        owner[id[node]] = node;
        while (1) {
            int cur = st.top();
            st.pop();
            instk[cur] = false;
            cmp[cur] = id[node];
            if (cur == node) break;
        }
    }
}

int SCC(int n) {
    stack<int> st;
    int ct = 0;
    for (int i = 1; i <= n; i++) {
        if (!id[i])
            SCCDFS(i, st);
        ct += (id[i] == cmp[i]);
    }
    return ct;
}

bool in[N], out[N];
vector<int> compGraph[N];
bool vis[N];
int findLeaf(int node) {
    vis[node] = true;
    if (compGraph[node].empty()) return node;
    for (auto child: compGraph[node]) {
        if (vis[child]) continue;
        int ret = findLeaf(child);
        if (~ret) return ret;
    }
    return -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    if (SCC(n) == 1) {
        cout << 0 << '\n';
        return 0;
    }
    vector<pair<int, int> > ans;
    for (int node = 1; node <= n; node++) {
        for (auto child: graph[node]) {
            if (cmp[node] == cmp[child]) continue;
            compGraph[cmp[node]].push_back(cmp[child]);
            in[cmp[child]] = 1;
            out[cmp[node]] = 1;
        }
    }
    vector<int> unsued;
    int randomSource, randomLeaf;
    for (int i = 1; i <= n; i++) {
        if (!owner[i]) continue;
        if (!in[i]) {
            int leaf = findLeaf(i);
            randomSource = i;
            if (~leaf) {
                ans.emplace_back(owner[leaf], owner[i]);
                randomLeaf = leaf;
            } else
                unsued.push_back(i);
        }
    }
    for (int i = 1; i < ans.size(); i++)
        swap(ans[i].first, ans[i - 1].first);
    for (int i = 1; i <= n; i++) {
        if (!owner[i]) continue;
        if (!out[i] && !vis[i]) {
            if (unsued.size()) {
                ans.emplace_back(owner[i], owner[unsued.back()]);
                unsued.pop_back();
            } else {
                ans.emplace_back(owner[i], owner[randomSource]);
            }
        }
    }
    for (auto i: unsued) {
        ans.emplace_back(owner[randomLeaf], owner[i]);
    }
    cout << ans.size() << '\n';
    for (auto [u, v]: ans)
        cout << u << ' ' << v << '\n';
}
```
