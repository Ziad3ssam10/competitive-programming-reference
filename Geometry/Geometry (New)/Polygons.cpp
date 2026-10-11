T polygonArea(vector<point>& p){
    T a = 0;
    p.push_back(p[0]);
    for(int i = 1; i < p.size(); i++) a += cross(p[i-1], p[i]);
    p.pop_back();
    return fabs(a/2.0);
}

point polygonCenteriod(vector<point>& p) {
    T x = 0, y = 0, a = 0, c;
    p.push_back(p[0]);
    for(int i = 0; i+1 < p.size(); ++i){
        int j = i+1;
        c = cross(p[i], p[j]), a += c;
        x += (p[i].X + p[j].X) * c;
        y += (p[i].Y + p[j].Y) * c;
    }
    p.pop_back();
    if(dcmp(a, 0) == 0) return (p[0] + p.back()) * 0.5;   // Line
    a /= 2, x /= 6 * a, y /= 6 * a;
    // Fix values in case
    if (dcmp(x, 0) == 0) x = 0;
    if (dcmp(y, 0) == 0) y = 0;
    return point(x, y);
}

int isInsidePoly(vector<point>& p, point p0) {
    int wn = 0;  // the winding number counter
    p.push_back(p[0]);
    for(int i = 1; i < p.size(); i++) {
        point cur = p[i-1], nxt = p[i];
        if (isPointOnSegment(p0, cur, nxt)){
            p.pop_back(); return true;
        }
        if (cur.Y <= p0.Y) { // Upward edge
            if (nxt.Y > p0.Y && cross(nxt-cur, p0-cur) > eps)
                ++wn;
        }
        else { // Downward edge
            if (nxt.Y <= p0.Y && cross(nxt-cur, p0-cur) < -eps)
                --wn;
        }
    }
    p.pop_back();
    return wn != 0;
}

bool pointInConvex(point p, vector<point>& poly){ // O(log(n))
    int n = poly.size();
    int l = 2, r = n-1, mid, idx = 2;
    
    while(l <= r){
        mid = l+(r-l)/2;
        if(ccw(poly[0], poly[mid], p) == -1) l = mid+1;
        else r = mid-1, idx = mid;
    }
    vector<point> ps = {poly[0], poly[idx-1], poly[idx]};
    return isInsidePoly(ps, p);
        //    && !isPointOnSegment(p, poly[idx-1], poly[idx]) &&
        //    !isPointOnSegment(p, poly[idx], poly[(idx+1)%n]) &&
        //    !isPointOnSegment(p, poly[(idx-2+n)%n], poly[idx-1])
}

ll pointsInPoly(vector<point>& p){ // Area = PointsInPoly + BoundaryPoints/2 - 1
    int n = p.size();
    ll b = 0; // boundary points
    for(int i = 0; i < n; i++)
        b += abs(__gcd(p[i].X-p[(i+1)%n].X, p[i].Y-p[(i+1)%n].Y));
    return (polygonArea(p)-b)/2+1; // PolygonArea is *2 (remove division by 2)
}

// gets polygon LEFT of line
vector<point> polygonCut(vector<point> &p, point a, point b){
    vector<point> ret;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        bool in1 = cross(vec(a,b),vec(a,p[i])) > eps;
        bool in2 = cross(vec(a,b),vec(a,p[j])) > eps;

        if(in1) ret.push_back(p[i]);
        if(in1 ^ in2) {
            point r;
            intersectSegments(a, b, p[i], p[j], r); // LINE - Segment
            ret.push_back(r);
        }
    }
    return ret;
}

vector<point> convexPolygonPolygonIntersection(vector<point>& p, vector<point>& q){ // both CCW
    vector<point> ret = q;
    for (int i = 0; i < p.size(); i++) {
        int j = (i + 1) % p.size();
        vector<point> temp = polygonCut(ret, p[i], p[j]);
        ret = temp;
        if(ret.empty())
            return {};
    }
    return ret;
}
