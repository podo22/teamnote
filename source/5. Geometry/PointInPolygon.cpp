// 다각형 내부 포함 판별 (Ray Casting), O(N) (CCW/CW 순서 무관)
bool PointInPolygon(const vector<P>& poly, P p) {
    int n = poly.size(); bool inside = false;
    for (int i = 0; i < n; i++) {
        P a = poly[i], b = poly[(i + 1) % n];
        if ((b - a) / (p - a) == 0 && (a - p) * (b - p) <= 0) return true; // false: exclude boundary
        if ((a.y > p.y) != (b.y > p.y)) {
            double iX = (double)(b.x-a.x) * (p.y-a.y) / (double)(b.y-a.y) + a.x;
            if (p.x < iX) inside = !inside;
        }
    }
    return inside;
}