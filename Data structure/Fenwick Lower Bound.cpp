int findKth(ll *bit, int k) { //find the position of the k-th one in a (0/1) bit (k should be <= num of ones), also it finds the first position where the prefix = k in general
    int idx = 0;
    int bitMask = 1 << (31 - __builtin_clz(n));
    // highest power of two ≤ n

    for (; bitMask; bitMask >>= 1) {
        int nxt = idx + bitMask;
        if (nxt <= n && bit[nxt] < k) {
            idx = nxt;
            k -= bit[nxt];
        }
    }
    // now idx is the largest position where prefix sum < original k
    // so the answer is idx+1
    return idx + 1;
}
