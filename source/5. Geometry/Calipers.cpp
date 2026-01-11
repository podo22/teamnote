// 가장 먼 두 점을 구하는 함수, O(N)
// hull: 반시계 방향(CCW)으로 정렬된 볼록 다각형
pair<P, P> Calipers(const vector<P>& hull) {
    int n = sz(hull); if (n < 2) return {hull[0], hull[0]};
    ll mx = 0; P a = hull[0], b = hull[1];
    for (int i = 0, j = 1; i < n; i++) {
        P vec_i = hull[(i + 1) % n] - hull[i];
        while ((vec_i / (hull[(j + 1) % n] - hull[j])) > 0) {
            ll now = (hull[i] - hull[j]).dist2();
            if (now > mx) mx = now, a = hull[i], b = hull[j];
            j = (j + 1) % n;
        }
        ll now = (hull[i] - hull[j]).dist2();
        if (now > mx) mx = now, a = hull[i], b = hull[j];
    }
    return { a, b };
}