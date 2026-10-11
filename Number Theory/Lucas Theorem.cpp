// When you want to calculate nCr but the n and r are very large and the mod is small and prime.
int lucas(ll n, ll r) {
if (r > n) return 0;
if (n < mod) return C.ncr(n, r); // This is regular ncr
return lucas(n / mod, r / mod) * lucas(n % mod, r % mod);
}
