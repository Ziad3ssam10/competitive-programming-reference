inline bool isCollinear(const point& a, const point& b, const point& c) { return fabs(cross(b-a, c-a)) < eps; }
inline bool isPointOnRay(const point& p, const point& p0, const point& p1) { return (!isCollinear(p, p0, p1)? 0 : dcmp(dot(p1-p0, p-p0), 0) >= 0); }
inline bool isPointOnSegment(const point& p, const point& p0, const point& p1) { return isPointOnRay(p, p0, p1) && isPointOnRay(p, p1, p0); }

T distToLine(const point& p, const point& p0, const point& p1){
    if(same(p0, p1)) return length(p - p0);
    return fabs(cross(p1-p0, p-p0)/length(p0-p1));
}
pair<T, point> distToSegment(const point& p, const point& p0, const point& p1){
    T d1, d2;
    point v1 = p1-p0, v2 = p-p0;
    if((d1 = dot(v1, v2)) <= 0) return {length(p-p0), p0};
    if((d2 = dot(v1, v1)) <= d1) return {length(p-p1), p1};
    return {length(p - (p0 + v1*(d1/d2))), (p0 + v1*(d1/d2))};
}
bool intersectSegments(point p0, point p1, point s0, point s1, point& intersect){
    T d1 = cross(p0-p1, s1-s0), d2 = cross(p0-s0, s1-s0), d3 = cross(p0-p1, p0-s0);
    if (fabs(d1) < eps) return false; // Parallel/identical
    T t1 = d2/d1, t2 = d3/d1;
    intersect = p0 + (p1-p0)*t1;
    if (t1 < -eps || t1 > 1 + eps || t2 < -eps || t2 > 1 + eps) return false;
    return true;
}

bool intersectSegments(point p0, point p1, point s0, point s1){
    bool x = same(p0, p1), y = same(s0, s1);
    if(x && y) return same(p0, s0);
    if(x) return ccw(s0, s1, p0) == 0;
    if(y) return ccw(p0, p1, s0) == 0;
    return ccw(p0, p1, s0) * ccw(p0, p1, s1) <= 0 && ccw(s0, s1, p0) * ccw(s0, s1, p1) <= 0 ; 
}

point ProjectPointSegment(point a, point b, point p){
    T r = dot(p - a, b - a) / dot(b - a, b - a);
    if(r < 0) return a;
    if(r > 1) return b;
    return a + (b - a) * r ;
}

point ProjectPointLine(point a, point b, point p){
    return a + (b - a) * 1.0 * dot(p - a, b - a) / dot(b - a, b - a);
}

T distToSegment(point s, point e, point c){
    point v1 = e - s, v2 = c - s;
    T d1 = dot(v1, v2), d2 = dot(v1, v1);
    if(d1 <= 0) return abs(c - s);
    if(d2 <= d1) return abs(c - e);
    T t = d1/d2;
    return abs(c - (s + v1 * t));
}

T distSegmentSegment(point a, point b, point x, point y){
    T s = 0, e = 1000, m1, m2;
    point pm1, pm2;
    for(int i = 0; i < 200; i++){
        m1 = s + (e - s) / 3;
        m2 = e - (e - s) / 3;
        pm1 = a + (b - a) * (m1 / 1000);
        pm2 = a + (b - a) * (m2 / 1000);
        if(distToSegment(x, y, pm1) <= distToSegment(x, y, pm2)) e = m2;
        else s = m1;
    }
    pm1 = a + (b - a) * (s / 1000);
    return distToSegment(x, y, pm1);
}
