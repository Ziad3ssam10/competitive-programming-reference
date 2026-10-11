// or (1/2) * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|
T triangleArea(point p0, point p1, point p2){
    T a = length(p0-p1), b = length(p0- p2), c = length(p1-p2);
    T s = (a+b+c)/2;
    return sqrt((s-a)*(s-b)*(s-c)*s);
}
T triangleAreaMedians(T m1, T m2, T m3){
    if(m1 <= 0 || m2 <= 0 || m3 <= 0) return -1;
    T s = 0.5*(m1+m2+m3);
    T median_area = s*(s-m1)*(s-m2)*(s-m3);
    T area = 4.0/3.0*sqrt(median_area);
    if(median_area <= 0 || area <= 0) return -1;
    return area; 
}
T fixAngle(T a) {
    return a > 1? 1 : (a < -1? -1 : a);
};
// sin(A)/a = sin(B)/b = sin(C)/c
T get_a_bAB(T b, T A, T B){
    return (sin(A)*b)/sin(B);
}
T getAngle_A_abB(T a, T b, T B){
    return asin(fixAngle(a*sin(B)/b));
}
// a^2 = b^2 + c^2 - 2*b*c*cos(A)
T getAngle_A_abc(T a, T b, T c){
    return acos(fixAngle((b*b+c*c-a*a)/(2*b*c)));
}

/*
        C
        .
       / \
      /   \
     /     \
    /       \
   /         \
A .___________. B

*/

// Given A, B, AC, AB
int triangleThirdPoint(point a, point b, ld ac, ld bc, point &c1, point &c2){
    ld ab = abs(vec(a, b));
    if(ab - (ac + bc) > eps)
        return 0;

    if(fabs(ab - (ac + bc)) < eps)
        return c1 = a + vec(a, b) * (ac / ab), 1;

    ld s = 0, e = 1000, m1, m2;
    point base = a + normalize(vec(a, b)) * ac, mid1, mid2;
    for(int i = 0; i < 200; i++){
        m1 = s + (e - s) / 3;
        m2 = e - (e - s) / 3;

        mid1 = base.rotateAround(a, (m1 / 1001) * pi / 2);
        mid2 = base.rotateAround(a, (m2 / 1001) * pi / 2);

        if(fabs(bc - dist(mid1, b)) < fabs(bc - dist(mid2, b)))
            e = m2;
        else
            s = m1;
    }

    base = base.rotateAround(a, (s / 1001) * pi / 2);
    c1 = base;
    c2 = reflectAroundLine(a, b, c1);
    return 2;
}

// Given A, B, ang(BAC), ang(ABC)
int triangleThirdPoint(point a, point b, ld bac, ld abc, point &c1, point &c2){
    if(bac < eps or pi / 2 - bac < eps)
        return 0;
    if(abc < eps or pi / 2 - abc < eps)
        return 0;

    point bRotated = b.rotateAround(a, bac);
    point aRotated = a.rotateAround(b, 2 * pi - abc);

    // treat as ray ray intersection
    return assert(intersectSegments(a, bRotated, b, aRotated, c1)), 1;
}

