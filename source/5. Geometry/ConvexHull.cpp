// 모든 점을 포함하는 가장 작은 볼록 다각형, O(N log N)
vector<Point> ConvexHull(vector<Point> points){ // Graham scan
    if(points.size() <= 1) return points;
    swap(points[0], *min_element(all(points)));
    sort(points.begin()+1, points.end(), [&](auto a, auto b){
        int dir = CCW(points[0], a, b);
        if(dir != 0) return dir > 0;
        return Dist(points[0], a) < Dist(points[0], b);
    });
    vector<Point> hull;
    for(auto p : points){
        while(hull.size() >= 2 && CCW(hull[hull.size()-2], hull.back(), p) <= 0) hull.pop_back();
        hull.push_back(p);
    }
    return hull;
}
vector<Point> convexHull(vector<Point> points) { // Monotone chain
    if (sz(points) <= 1) return points;
    sort(all(points), [&](Point p1, Point p2) {
        return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
    });
    Polygon v(sz(points)+1);
    int s = 0, t = 0;
    for (int i = 2; i--; s = --t, reverse(all(points))) {
        for (auto p : points) {
            while (t >= s+2 && ccw(v[t-2], v[t-1], p) <= 0) t--;
            v[t++] = p;
        }
    }
    v.resize(t - (t==2 && v[0].x == v[1].x && v[0].y == v[1].y));
    return v;
}