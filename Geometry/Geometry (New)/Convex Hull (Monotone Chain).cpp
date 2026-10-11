vector<point> convexHull(vector<point> p){
    int n = p.size(), k = 0;
    if(n <= 1) return p;
    vector<point> ch(2*n);
    sort(p.begin(), p.end(), [&](point& a, point& b){
        if(a.X == b.X) return a.Y < b.Y;
        return a.X < b.X;
    });
    
    for(int i = 0; i < n; i++){
        while(k >= 2 && cross(ch[k-1]-ch[k-2], p[i]-ch[k-2]) <= 0) k--;
        ch[k++] = p[i];
    }
    
    for(int i = n-1, t = k+1; i > 0; i--){
        while(k >= t && cross(ch[k-1]-ch[k-2], p[i-1]-ch[k-2]) <= 0) k--;
        ch[k++] = p[i-1];
    }
    ch.resize(k-1);
    return ch;
}