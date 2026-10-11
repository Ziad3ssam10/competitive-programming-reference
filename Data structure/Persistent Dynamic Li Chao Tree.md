# persistent dynamic LI chao Tree

```cpp
const ll DEFAULT = -1e18;
struct Line {
    ll m, c;
    Line(ll m = 0, ll c = DEFAULT) : m(m), c(c) {
    }
    ll operator()(ll x) const { return m * x + c; }
};
struct Node {
    Node *left, *right;
    Line line;
    Node(Line line = Line(), Node *left = nullptr, Node *right = nullptr)
    : left(left), right(right), line(line) {
    }
};
Node *insert(Line newLine, Node *root, ll l, ll r) {
    if (root == nullptr) {
        return new Node(newLine, nullptr, nullptr);
    }
    Node *cur = new Node(root->line, root->left, root->right);
    ll m = (l + r) / 2;
    bool lef = newLine(l) > cur->line(l);
    bool mid = newLine(m) > cur->line(m);
    if (mid)
        swap(cur->line, newLine);
    if (r - l == 1)
        return cur;
    if (lef != mid)
        cur->left = insert(newLine, cur->left, l, m);
    else
        cur->right = insert(newLine, cur->right, m, r);
    return cur;
}
ll query(ll x, Node *cur, ll l, ll r) {
    if (cur == nullptr)
        return DEFAULT;
    ll m = (l + r) / 2;
    if (r - l == 1)
        return cur->line(x);
    else if (x < m)
        return max(cur->line(x), query(x, cur->left, l, m));
    else
        return max(cur->line(x), query(x, cur->right, m, r));
}
Node *tree[MAXN];
```
