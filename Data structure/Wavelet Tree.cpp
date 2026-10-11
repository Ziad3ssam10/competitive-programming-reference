const int N = 2e5 + 10;
int a[N];

struct wavelet_tree {
    int lo, hi;
    wavelet_tree *l = nullptr, *r = nullptr;
    vector<int> b;
    
    // numbers are in [x, y], array is [from, to) (1-based expected)
    wavelet_tree(int *from, int *to, int x, int y) : lo(x), hi(y), l(nullptr), r(nullptr) {
        if (from >= to) return;            // empty range
        if (lo == hi) {
            // leaf node: store prefix counts (all go to left logically)
            b.reserve((to - from) + 1);
            b.push_back(0);
            for (auto it = from; it != to; ++it) b.push_back(b.back() + 1);
            return;
        }
        
        int mid = (lo + hi) >> 1;
        auto goesLeft = [mid](int val) { return val <= mid; };
        
        b.reserve((to - from) + 1);
        b.push_back(0);
        for (auto it = from; it != to; ++it) b.push_back(b.back() + (goesLeft(*it) ? 1 : 0));
        
        // partition into left (<= mid) and right (> mid)
        auto pivot = stable_partition(from, to, goesLeft);
        
        // recursively build children only if there are elements
        if (from != pivot) l = new wavelet_tree(from, pivot, lo, mid);
        if (pivot != to)   r = new wavelet_tree(pivot, to, mid + 1, hi);
    }
    
    // kth smallest in [L, R] (1-based inclusive)
    int kth(int L, int R, int k) {
        if (L > R) return 0; // invalid
        if (lo == hi) return lo;
        int inLeft = b[R] - b[L - 1];
        int lb = b[L - 1], rb = b[R];
        if (k <= inLeft) {
            // if left child doesn't exist something is wrong, but guard anyway
            if (!l) return lo;
            return l->kth(lb + 1, rb, k);
        } else {
            if (!r) return lo;
            return r->kth(L - lb, R - rb, k - inLeft);
        }
    }
    
    int LTE(int L, int R, int k) {
        if (L > R || k < lo) return 0;
        if (hi <= k) return R - L + 1;
        int lb = b[L - 1], rb = b[R];
        int leftCnt = (l ? l->LTE(lb + 1, rb, k) : 0);
        int rightCnt = (r ? r->LTE(L - lb, R - rb, k) : 0);
        return leftCnt + rightCnt;
    }
    
    int count(int L, int R, int k) {
        if (L > R || k < lo || k > hi) return 0;
        if (lo == hi) return R - L + 1;
        int lb = b[L - 1], rb = b[R], mid = (lo + hi) >> 1;
        if (k <= mid) return (l ? l->count(lb + 1, rb, k) : 0);
        return (r ? r->count(L - lb, R - rb, k) : 0);
    }
    
    ~wavelet_tree() {
        delete l;
        delete r;
    }
};

void burn() {
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    wavelet_tree wv(a + 1, a + n + 1, 0, 1000000000);
    
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        //L, R, K, 1-based
        cout << wv.kth(l, r, k) << '\n';
    }
}