const int BN = 2, ch_offset = 'a' - 1;
const int base[BN] = { 31, 37 };
int pw[N][BN], inv[N][BN];
bool init = false;

int fastPow(ll n, ll p) {
    if (p == 0) return 1;
    int half_pow = fastPow(n, p / 2);
    return (p & 1 ? ((1ll * half_pow * half_pow) % mod) * n : 1ll * half_pow * half_pow) % mod;
}

int add(int a, int b){
    return (1ll * a + b + mod) % mod;
}

int mult(int a, int b){
    return (1ll * a * b) % mod;
}

void initPows() {
    for (int i = 0; i < BN; i++) {
        pw[0][i] = inv[0][i] = 1;
        int b_inv = fastPow(base[i], mod - 2);
        for (int j = 1; j < N; j++) {
            pw[j][i] = mult(pw[j - 1][i], base[i]);
            inv[j][i] = mult(inv[j - 1][i], b_inv);
        }
    }
}

struct Hash {
    array<int, BN> val;
    int sz;

    Hash(array<int, BN> val = {}, int sz = 0) : val(val), sz(sz) {}
    Hash(char c) {
        if(!init)
            init = true, initPows();
        sz = 1;
        for(int i = 0; i < BN; i++)
            val[i] = c-ch_offset;
    }

    bool operator<(const Hash& other) const {
        return val < other.val;
    }
    bool operator==(const Hash&other) const {
        return sz == other.sz && val == other.val;
    }
    Hash operator+(const Hash& other) const {
        Hash ret;
        for (int i = 0; i < BN; i++)
            ret.val[i] = add(val[i], mult(other.val[i], pw[sz][i]));
        ret.sz = sz + other.sz;
        return ret;
    }
    Hash operator-(const Hash& other) const{
        Hash ret;
        for (int i = 0; i < BN; i++)
            ret.val[i] = mult(add(val[i], -other.val[i]), inv[other.sz][i]);
        ret.sz = sz - other.sz;
        return ret;
    }
};

class RabinKarp {
    //1-based
    vector<Hash> hashes;
    RabinKarp(string& s) {
        hashes.resize(s.size()+1);
        hashes[0] = Hash();
        for (int i = 1; i <= s.size(); i++)
            hashes[i] = hashes[i - 1] + Hash(s[i-1]);
    }

    Hash getHash(int l, int r) {
        return hashes[r] - hashes[l-1];
    }
};