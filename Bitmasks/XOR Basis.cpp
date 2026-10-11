struct XORBasis
{
    int d, sz = 0;
    vector <ll> basis;
    XORBasis(int d)
    {
        this->d = d;
        basis.resize(d);
    }
    bool insert(ll num)
    {
        for(int i = d - 1; i >= 0; i--)
        {
            if(!((1ll << i) & num))
                continue;
            if(!basis[i])
            {
                basis[i] = num;
                sz++;
                return true;
            }
            num ^= basis[i];
            
        }
        return false;
    }

    bool can(ll num)
    {
        for(int i = d - 1; i >= 0; i--)
            num = min(num, num ^ basis[i]);
        return !num;
    }
    
    ll getKthSmallest(ll k)
    {
        ll val = 0, ptr = sz - 1;
        for(int i = d - 1; i >= 0; i--)
        {
            if(!basis[i])
                continue;
            bool actual = (1ll << i) & val, required = (1ll << ptr) & k;
            if(actual != required)
                val ^= basis[i];
            ptr--;
        }
        return val;
    }
    
    ll getKthLargest(ll k)
    {
        assert(k <= (1ll << sz));
        return getKthSmallest((1ll << sz) - k);
    }

    ll getLargest() {
        ll val = 0;
        for (int i = d - 1; i >= 0; i--) {
            if (!ba[i])continue;
            if (!((1 << i) & val))
                val ^= ba[i];
        }
        return val;
    }
};

XORBasis mrg(XORBasis a, XORBasis b) {
    for (int i = b.d - 1; i >= 0; i--) {
        if (!b.basis[i])continue;
        a.insert(b.basis[i]);
    }
    return a;
}