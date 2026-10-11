struct Query
{
    int l, r, i;

    Query(int l, int r, int i) : l(l), r(r), i(i)
    {}

    bool operator<(const Query &oth) const
    {
        if(l / SQ != oth.l / SQ)
            return make_pair(l / SQ, r) < make_pair(oth.l / SQ, oth.r);
        
        if(l / SQ % 2 == 0)
            return r < oth.r;
        else
            return r > oth.r;
    }
};

void add(int i)
{
    
}

void rmv(int i)
{
    
}

int getAns()
{
    
}

vector<int> mo(vector<Query> &v)
{
    vector<int> ret(v.size());
    sort(v.begin(), v.end());

    int curL = 0, curR = -1;
    for(auto &[l, r, i]: v)
    {
        while(curR < r)
            add(++curR);
        while(curL > l)
            add(--curL);

        while(curR > r)
            rmv(curR--);
        while(curL < l)
            rmv(curL++);

        ret[i] = getAns();
    }
    return ret;
}
