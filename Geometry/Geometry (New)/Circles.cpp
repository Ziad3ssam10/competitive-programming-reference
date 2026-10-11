pair<point, T> findCircle(point a, point b, point c){
    point m1 = (a+b)*0.5, v1 = b-a, pv1 = point(v1.Y, -v1.X);
    point m2 = (b+c)*0.5, v2 = b-c, pv2 = point(v2.Y, -v2.X);
    point end1 = m1+pv1, end2 = m2+pv2, center = -1;
    intersectSegments(m1, end1, m2, end2, center);
    return {center, length(a-center)};
}
vector<point> instersectLineCircle(point p0, point p1, point C, T r){
    T a = dot(p1-p0, p1-p0), b = 2*dot(p1-p0, p0-C), c = dot(p0-C, p0-C)-r*r;
    T f = b*b-4*a*c;
    vector<point> ret;
    if(dcmp(f, 0) >= 0) {
        if(dcmp(f, 0) == 0) f = 0;
        T t1 = (-b + sqrt(f))/(2*a);
        T t2 = (-b - sqrt(f))/(2*a);
        ret.push_back(p0+t1*(p1-p0));
        if(dcmp(f, 0) != 0) ret.push_back(p0+t2*(p1-p0));
    }
    return ret;
}
vector<point> instersectCircleCircle(point c1, T r1, point c2, T r2){
    if(same(c1, c2) && dcmp(r1, r2) == 0 && dcmp(r1, 0) > 0) return vector<point>(3, c1);
    T ang1 = angle(c2-c1), ang2 = getAngle_A_abc(r2, r1, length(c2-c1));
    if(::isnan(ang2)) ang2 = 0;
    vector<point> v(1, polar(r1, ang1+ang2)+c1);
    if(dcmp(dot(v[0]-c1, v[0]-c1), r1*r1) != 0 ||
       dcmp(dot(v[0]-c2, v[0]-c2), r2*r2) != 0) return {};
    v.push_back(polar(r1, ang1-ang2)+c1);
    if(same(v[0], v[1])) v.pop_back();
    return v;
}

ld intersection_area(ll r1, ll r2, ld d) {
    if (d >= r1 + r2) return 0.0;
    if (d <= abs(r1 - r2))
        return area(min(r1, r2));

    ld r1_sq = r1 * r1;
    ld r2_sq = r2 * r2;
    ld d_sq = d * d;

    ld alpha = acos((r1_sq + d_sq - r2_sq) / (2 * r1 * d));
    ld beta = acos((r2_sq + d_sq - r1_sq) / (2 * r2 * d));

    ld a1 = r1_sq * alpha - r1_sq * sin(alpha * 2) / 2.0;
    ld a2 = r2_sq * beta - r2_sq * sin(beta * 2) / 2.0;

    return a1 + a2;
}

const int MAX = 100000+9;
point pnts[MAX], r[3], cen;
double rad;
int ps, rs;	// ps = n, rs = 0, initially

// random_shuffle(pnts, pnts+ps);		rs = 0;
void MEC() {
	if(ps == 0 && rs == 2) {
		cen = (r[0]+r[1])/2.0;
		rad = length(r[0]-cen);
	}
	else if(rs == 3) {
		pair<double, point> p = findCircle(r[0], r[1], r[2]);
		cen = p.second;
		rad = p.first;
	}
	else if(ps == 0) {
		cen = r[0];	// sometime be garbage, but will not affect
		rad = 0;
	}
	else {
		ps--;
		MEC();

		if(length(pnts[ps]-cen) > rad) {
			r[rs++] = pnts[ps];
			MEC();
			rs--;
		}

		ps++;
	}
}
