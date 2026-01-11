// 다각형 넓이의 2배를 반환 (Shoelace Formula), O(N)
ll PolygonArea2(const vector<P>& poly) {
    ll area = 0; int n = poly.size();
    for (int i = 0; i < n; i++) area += poly[i] / poly[(i + 1) % n];
    return abs(area);
}