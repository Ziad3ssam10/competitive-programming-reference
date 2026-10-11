inline double length(const point& p) { return hypot(p.Y, p.X); }
inline int dcmp(double a, double b) { return (fabs(a-b)) <= eps ? 0 : a < b ? -1 : 1; }

struct cmpX{
    bool operator()(const point& a, const point& b) const {
        if(dcmp(a.X, b.X) != 0) return dcmp(a.X, b.X) < 0;
        return dcmp(a.Y, b.Y) < 0;
    }
};
struct cmpY{
    bool operator()(const point& a, const point& b) const {
        if(dcmp(a.Y, b.Y) != 0) return dcmp(a.Y, b.Y) < 0;
        return dcmp(a.X, b.X) < 0;
    }
};

double closestPair(vector<point>& p){
    double d = inf;
    set<point, cmpY> window;
    sort(p.begin(), p.end(), cmpX());
    int l = 0;
    for(int r = 0; r < p.size(); r++){
        while(l < r && p[r].X-p[l].X > d) window.erase(p[l++]);
        auto s = window.lower_bound(point(-inf, p[r].Y - d)); 
        auto e = window.lower_bound(point(-inf, p[r].Y + d)); 
        while(s != e) d = min(d, length(p[r]-*s)), s++;
        window.insert(p[r]);
    }
    return d;
}