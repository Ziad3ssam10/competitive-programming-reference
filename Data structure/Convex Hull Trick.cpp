struct CHT //This works for minimum, *= -1 slope and intercept to get max
{
    struct  Line
    {
        int slope, yIntercept;
        Line(int slope, int yInter) : slope(slope), yIntercept(yInter) {}
        int val(int x)
        {
            return slope * x + yIntercept;
        }
        int getIntersection(Line l)
        {
            return (l.yIntercept - yIntercept + slope - l.slope - 1) / (slope - l.slope);
        }
    };
    deque <pair <Line, int>> dq;
    
    void insert(int slope, int yInter)
    {
        while(dq.size() && dq.back().second >= dq.back().first.getIntersection(Line(slope, yInter)))
            dq.pop_back();
        dq.emplace_back(Line(slope, yInter), (dq.size() ? dq.back().first.getIntersection(Line(slope, yInter)) : 0));
    }
    ll query(int x)
    {
        while(dq.size() > 1 && dq[1].second <= x)
            dq.pop_front();
        return dq[0].first.val(x);
    }
};
