vector<point> convexHull(vector<point> poly, bool colinear = 0){    
    if(poly.size() <= 1) return poly;

    for(int i = 1; i < poly.size(); i++)
        if(make_pair(poly[i].Y, poly[i].X) < make_pair(poly[0].Y, poly[0].X))
            swap(poly[0], poly[i]);

    sort(poly.begin()+1, poly.end(), [&](point& a, point& b){
        double c = cross(a-poly[0], b-poly[0]);
        if(dcmp(c, 0) == 0) return lengthSqr(a-poly[0]) < lengthSqr(b-poly[0]);
        return c > 0;
    });

    vector<point> temp;
    for(auto p : poly)
        if(temp.empty() || !same(temp.back(), p)) temp.push_back(p);
    poly = temp;

    if(poly.size() <= 1) return poly;

    if(!colinear){
        temp.clear();
        for(int i = 0; i < poly.size(); i++){
            if(temp.size() > 1 && fabs(cross(temp.back()-temp[0], poly[i]-temp[0])) < eps){
                if(lengthSqr(temp.back()-poly[0]) < lengthSqr(poly[i]-poly[0]))
                    temp.back() = poly[i];
            }
            else temp.push_back(poly[i]);
        }
        poly = temp;
    }

    vector<point> ch;
    for(auto p : poly){
        while(ch.size() > 1){
            double c = cross(ch.back()-ch[ch.size()-2], p-ch.back());
            if(colinear? (dcmp(c, 0) < 0) : (dcmp(c, 0) <= 0)) ch.pop_back();
            else break;
        }
        ch.push_back(p);
    }

    //if(ch.size() >= 3) ch.push_back(ch[0]);
    return ch;
}