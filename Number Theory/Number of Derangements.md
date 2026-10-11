# Number of Derangements

A derangement is a permutation of $n$ elements with **no fixed points** (no element stays in its original position).

Recurrence: $D(n) = (n - 1)\big(D(n-1) + D(n-2)\big)$

Base cases:
- $D(0) = 1$
- $D(1) = 0$
- $D(2) = 1$

```cpp
ll res[N];
// number of permutations with no fixed points
int derangement(int n)
{
    if(n <= 2)
        return n != 1;
    if(res[n])
        return res[n];
    return res[n] = (n - 1) * (derangement(n - 1) + derangement(n - 2));
}
```
