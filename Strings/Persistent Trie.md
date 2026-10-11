# persistent Trie

```cpp
const int K = 22;
struct node_t;
struct node_t {
    int time;
    node_t *to[2];
    int cnt = 0;
    node_t() : time(0) {
        to[0] = to[1] = 0;
    }
    node_t * clone() {
        node_t * cur = new node_t();
        if (this) {
            cur->time = time;
            cur->to[0] = to[0];
            cur->to[1] = to[1];
            cur->cnt = cnt;
        }
        return cur;
    }
};
node_t * last;
node_t * version[N];
void insert(int a, int time) {
    node_t * v = version[time] = last = last->clone();
    for (int i = K - 1; i >= 0; --i) {
        int bit = (a >> i) & 1;
        if(!v->to[bit])
            v->to[bit] = new node_t();
        node_t * &child = v->to[bit];
        child = child->clone();
        v = child;
        v->time = time;
        v->cnt++;
    }
}
int query(node_t * v, int x, int l) {
    int ans = 0;
    // x is a[i], l is target
    for (int i = K - 1; i >= 0; --i) {
        int bit = (x >> i) & 1;
        int othBit = (l >> i) & 1;
        if(bit == othBit) {
            if(!bit && v->to[1])
                ans += v->to[1]->cnt;
            if (v->to[0])
                v = v->to[0];
            else
                break;
        }
        else
        {
            if(bit && v->to[0])
                ans += v->to[0]->cnt;
            if (v->to[1])
                v = v->to[1];
            else
                break;
        }
    }
    return ans;
}
```
