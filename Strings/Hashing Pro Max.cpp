struct Hash
{
    vector<pair<int, int>> prefixHash;
    int sz;
    Hash(string &sz)
    {
        prefixHash = vector<pair<int, int>>(sz.size());
        for (int i = 0; i < sz.size(); i++)
        {
            prefixHash[i].first = mul(sz[i] - 'a' + 1, pw[i]);
            prefixHash[i].second = mul(sz[i] - 'a' + 1, pw2[i]);
            if (i)
            {
                prefixHash[i].first = add(prefixHash[i].first, prefixHash[i - 1].first);
                prefixHash[i].second = add(prefixHash[i].second, prefixHash[i - 1].second);
            }
        }
    }
    pair<int, int> getHashValue(int l, int r)
    {
        return {
            mul(add(prefixHash[r].first, (l ? -prefixHash[l - 1].first : 0)), inv[l]),
            mul(add(prefixHash[r].second, (l ? -prefixHash[l - 1].second : 0)), inv2[l])};
    }
    static pair<int, int> concat(pair<int, int> h1,
                                 pair<int, int> h2, int h1_sz)
    {
        h1.first = add(h1.first, mul(h2.first, pw[h1_sz]));
        h1.second = add(h1.second, mul(h2.second, pw2[h1_sz]));
        return h1;
    }
};
struct Hash2
{
    pair<int, int> hsh;
    int sz;
    Hash2(string &s)
    {
        hsh = {0, 0};
        for (int i = 0; i < s.size(); i++)
        {
            hsh.first = add(hsh.first, mul(s[i] - 'a' + 1, pw[i]));
            hsh.second = add(hsh.second, mul(s[i] - 'a' + 1, pw2[i]));
        }
        sz = s.size();
    }
    static Hash2 concat(Hash2 h1,
                        Hash2 h2)
    {
        h1.hsh.first = add(h1.hsh.first, mul(h2.hsh.first, pw[h1.sz]));
        h1.hsh.second = add(h1.hsh.second, mul(h2.hsh.second, pw2[h1.sz]));
        return h1;
    }
};