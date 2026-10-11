class PersistentCHT
{
    struct Line
    {
        ll m, c;
        Line() { }
        Line(ll _m, ll _c) : m(_m), c(_c) { }
    };
 
    vector < vector < Line > > hull;
    vector < ll > version_idx;
    vector < ll > version_sz;
    ll SZ = 0;
 
    ld inter(Line t1, Line t2)
    {
        ld ret;
        ret = (ld)(t2.c - t1.c - .0)/(t1.m - t2.m - .0);
        return ret;
    }
 
    void insert_line(Line curr)
    {
        Line temp, temp2;
        version_sz.push_back(SZ);
 
        if(SZ > 1)
        {
            ll s = 0, e = SZ - 1;
 
            while(s < e)
            {
                ll p = (s + e) / 2;
 
                temp = hull[p + 1].back();
                temp2 = hull[p].back();
 
                ld point = inter(temp, temp2);
                ld point2 = inter(temp, curr);
 
                if(point < point2) s = p+1;
                else e = p;
            }
            SZ = s + 1;
        }
 
        if(hull.size() == SZ)
        {
            vector<Line> x;
            hull.push_back(x);
        }
 
        hull[SZ].push_back(curr);
        version_idx.push_back(SZ);
        SZ++;
    }
 
public:
 
    void insert_line(ll m, ll c){ insert_line(Line(m, c)); }
 
    ll eval(ll find)
    {
        ll s = 0, e = SZ - 1;
 
        while(s < e)
        {
            ll p = (s + e) / 2;
            ld point = inter(hull[p].back(), hull[p + 1].back());
            if(point < find) s = p + 1;
            else e = p;
        }
 
        ll ret = (hull[s].back().m * find) + hull[s].back().c;
        return ret;
    }
 
    void rollback()
    {
        SZ = version_sz.back();
        version_sz.pop_back();
        hull[version_idx.back()].pop_back();
        version_idx.pop_back();
    }
 
    ll  size() { return SZ; }
 
};
