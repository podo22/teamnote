// Monotone Chain 알고리즘, O(NlogN)
// 반시계 방향(CCW)으로 정렬된 볼록 껍질 반환
// 일직선상의 점을 제외하려면 ccw <= 0, 포함하려면 ccw < 0
vector<P> ConvexHull(vector<P> ps) {
    if (sz(ps) <= 2) return ps;
    sort(all(ps)); vector<P> v(sz(ps)+2);
    int s = 0, t = 0;
    for (int i = 2; i--; s = --t, reverse(all(ps))) {
        for (P p : ps) {
            while (t >= s+2 && ccw(v[t-2], v[t-1], p) <= 0) t--;
            v[t++] = p;
        }
    }
    v.resize(t - (t > 1)); return v;
}