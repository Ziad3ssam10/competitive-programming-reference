``` cpp const int INF = 1e9;
struct BottleneckTree {
  vector<int> link, cost;   // all inserted costs must be < INF
  BottleneckTree(int n) : link(n, 0), cost(n, INF) {
    link[0] = -1; cost[0] = INF + 1;
  }
  void rot(int x) {
    int p = link[x], g = link[p];
    swap(cost[x], cost[p]);
    link[x] = g, link[p] = x;
  }
  void skip(int x) { link[x] = link[link[x]]; }
  void access(int x) {
    for (int p = link[x]; p != -1; p = link[x]) {
      int g = link[p];
      if (cost[x] <= cost[p]) rot(x);                  // (A)
      else if (cost[p] > cost[g]) skip(p), skip(x);    // (B)
      else if (cost[g] <= cost[x]) rot(p), skip(x);    // (C)
      else skip(x);                                    // (D)
    }
  }
  int Query(int x, int y) {      // x != y; INF if disconnected
    access(x); access(y);
    return cost[x];
  }
  int AddEdge(int x, int y, int c) {   // x != y
    access(x); access(y);
    if (cost[x] > c) swap(cost[x], c);
    return c;
  }
};
```
## Some notes:

* Vertices are 0,…,n−1 and xmust be different from y
 * Costs must be smaller than INF. For bigger costs, use long long and INF = 1e18.
* Equal costs are fine. If you want to know which edge was removed, use c * m + id as the cost (or pairs).


## For example, this is how you keep the total cost of the MST:
```cpp
long long total = 0;
int r = bt.AddEdge(x, y, c);
total += (r == INF) ? c : c - r;   // if the edge didn't enter, r == c
```