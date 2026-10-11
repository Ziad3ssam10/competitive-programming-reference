struct node {
    int p[2];
    int cnt;

    node() {
        memset(p, 0, sizeof p);
        cnt = 0;
    }
};

struct Trie {
    vector<node> tree;

    Trie() {
        tree.push_back(node());
    }

    void insert(int n) {
        int cur = 0;
        for (int i = 31; ~i; i--) {
            bool c = ((1ll << i) & n);
            if (!tree[cur].p[c])
                tree[cur].p[c] = tree.size(), tree.push_back(node());
            cur = tree[cur].p[c];
            tree[cur].cnt++;
        }
    }

    void del(int n) {
        int cur = 0;
        for (int i = 31; ~i; i--) {
            bool c = ((1ll << i) & n);
            int pv = cur;
            cur = tree[cur].p[c];
            if (tree[cur].cnt == 1)
                tree[pv].p[c] = 0;
            tree[cur].cnt--;
            bf.md
            2024 - 07 - 22
            83 / 150
        }
    }

    int calc(int n) {
        int cur = 0;
        int ret = 0;
        for (int i = 31; ~i; i--) {
            bool c = ((1ll << i) & n);
            if (tree[cur].p[!c])
                cur = tree[cur].p[!c], ret += (1ll << i);
            else
                cur = tree[cur].p[c];
        }
        return ret;
    }
};
