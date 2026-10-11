// N = 2 * MAX
// i -> edge(Ne(i), V(i))
// not i -> edge(V(i), Ne(i));
vector<int> adj[N], rev[N];
int w[N][3];
vector<bool> used, assignment;
vector<int> order, comp;

void dfs1(int v) {
    used[v] = true;
    for (int u: adj[v]) {
        if (!used[u])
            dfs1(u);
    }
    order.push_back(v);
}

void dfs2(int v, int cl) {
    comp[v] = cl;
    for (int u: rev[v]) {
        if (comp[u] == -1)
            dfs2(u, cl);
    }
}

bool solve(int n) {
    order.clear();
    used.assign(n, false);

    for (int i = 0; i < n; i++) {
        if (!used[i])dfs1(i);
    }

    comp.assign(n, -1);

    for (int i = 0, j = 0; i < n; i++) {
        int v = order[n - i - 1];
        if (comp[v] == -1)
            dfs2(v, j++);
    }

    assignment.assign(n / 2, false);
    for (int i = 0; i < n; i += 2) {
        if (comp[i] == comp[i + 1])
            return false;

        assignment[i / 2] = comp[i] > comp[i + 1];
    }

    return true;
}

int V(int a) {
    return (a << 1);
}

int Ne(int a) {
    return (a << 1) | 1;
}

void edge(int a, int b) {
    adj[a].push_back(b);
    rev[b].push_back(a);
}

void OR(int a, int b) {
    edge(a ^ 1, b);
    edge(b ^ 1, a);
}

void XNOR(int a, int b) {
    OR(Ne(a), V(b));
    OR(V(a), Ne(b));
}

void XOR(int a, int b) {
    OR(Ne(a), Ne(b));
    OR(V(a), V(b));
}

int get(int x) {
    int cur = V(abs(x) - 1);
    if (x < 0)
        cur |= 1;
    return cur;
}


void clear(int n) {
    for (int i = 0; i < n; i++)
        adj[i].clear(), rev[i].clear();
}

void master() {
    int n, x;
    cin >> n;
    for (int j = 0; j < 3; j++)
        for (int i = 0; i < n; i++) {
            cin >> x;
            w[i][j] = get(x);
        }


    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = j + 1; k < 3; k++) {
                OR(w[i][j], w[i][k]);// atmost one False
                // OR(w[i][j] ^ 1, w[i][k] ^ 1); atmost one True
            }
        }
    }

    if (solve(n * 2)) {
        cout << "YES";
    } else
        cout << "NO";

    for (int i = 0; i <= n * 2; i++) {
        adj[i].clear();
        rev[i].clear();
    }
}