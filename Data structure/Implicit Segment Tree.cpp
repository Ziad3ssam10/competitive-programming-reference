struct node {
    ll sum, lazy;
    node *left, *right;
 
    node() : sum(0), lazy(0), left(NULL), right(NULL) {}
 
    void addChild() {
        left = new node();
        right = new node();
    }
 
    void push(int lx, int rx) {
        if (lazy) {
            sum += lazy * (rx - lx + 1);
            if (rx != lx) {
                if (left == NULL)addChild();
                left->lazy += lazy;
                right->lazy += lazy;
            }
            lazy = 0;
        }
    }
 
    void update(int l, int r, int val, int lx, int rx) {
        push(lx, rx);
        if (lx > r || l > rx) {
            return;
        }
 
        if (lx >= l && rx <= r) {
            lazy += val;
            push(lx, rx);
            return;
        }
 
        int mid = lx + (rx - lx) / 2;
        if (left == NULL)addChild();
 
        left->update(l, r, val, lx, mid);
        right->update(l, r, val, mid + 1, rx);
        sum = left->sum + right->sum;
    }
 
    ll query(int l, int r, int lx, int rx) {
        if (l > rx || lx > r) {
            return 0;
        }
        push(lx, rx);
        if (lx >= l && rx <= r) {
            return sum;
        }
        if(left != NULL){
            int mid = lx + (rx - lx) / 2;
            return left->query(l, r, lx, mid) + right->query(l, r, mid + 1, rx);
        }
        else return 0;
    }
 
    void clear() {
        if (left != NULL) {
            left->clear();
            right->clear();
        }
        delete this;
    }
};
 
node *root = new node();
