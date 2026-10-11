const T PI = acos(-1), eps = 1e-9;
typedef double T;
typedef complex<T> point;

#define X real()
#define Y imag()

T toRad(const T& degree){ return degree * PI / 180.0; }
T toDeg(const T& rad){ return rad * 180.0 / PI; }

inline T dot(const point& a, const point& b) { return (conj(a) * b).X; }
inline T cross(const point& a, const point& b) { return (conj(a) * b).Y; }// (x_1 * y_2 - y_1 * x_2)
inline T length(const point& p) { return hypot(p.Y, p.X); }
inline T lengthSqr(const point& p) { return dot(p, p); }
inline point normalize(const point& p) { return p / length(p); }

inline int dcmp(T a, T b) { return (fabs(a-b)) <= eps ? 0 : a < b ? -1 : 1; }
inline bool same(const point& a, const point& b) { return dot(b-a, b-a) < eps; }

inline T formatAngle(T a){ a = fmod(a, 2*PI); return (a >= 0? a : a + 2*PI); }
inline T angle(const point& p) { return formatAngle(atan2(p.Y, p.X)); }
inline T angle_between(const point& a, const point& b) { return formatAngle(atan2(cross(a, b), dot(a, b))); }
T angleO(point a, point O, point b) {
    point v1(a-O), v2(b-O);
    return acos(fixAngle(dot(v1, v2)/length(v1)/length(v2)));
}
inline point rotate(const point& p, T ang) { return p * exp(point(0, ang)); }
inline point rotate_around(const point& p, T ang, const point& about) { return rotate(p - about, ang) + about; }
inline point reflect(const point& v, const point& m) { return conj(v / m) * m; }
inline point reflect_point(const point& p, const point& p0, const point& p1) { return reflect(p - p0, p1 - p0) + p0; }
int ccw(point p0, point p1, point p2){ // p2 relative to p0-p1
    point v1(p1-p0), v2(p2-p0);
    if(cross(v1, v2) > eps) return 1; // 1: angle > 0 or collinear after p1
    if(cross(v1, v2) < -eps) return -1; // -1: angle < 0 or collinear after p0
    if(dot(v1, v2) < -eps) return -1;
    if(norm(v1) < norm(v2)-eps) return 1;
    return 0; //undefined -> collinear in the range [p0, p1]
}
pair<T, T> cramer(T a1, T b1, T c1, T a2, T b2, T c2){
    T det = a1*b2-a2*b1;
    return {(b1*c2-b2*c1)/det, (c1*a2-c2*a1)/det};
}
