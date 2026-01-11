const double EPS = 1e-9;
using T = __int128_t; // T <= O(COORD^4)
// [1] 선분 교차 (정밀 좌표) / Param: 선분 ab, 선분 cd
// Return: {flag, xn, xd, yn, yd} -> 교점 (xn/xd, yn/yd)
// Flag: 0(안만남), 1(교점=끝점), 4(교차), -1(무수히 겹침)
tuple<int, T, T, T, T> segmentInter(P a, P b, P c, P d) {
    if (!isInter(a, b, c, d)) return {0, 0, 0, 0, 0};
    T det = (b - a) / (d - c);
    if (det == 0) {
        if (b < a) swap(a, b);
        if (d < c) swap(c, d);
        if (b == c) return {1, b.x, 1, b.y, 1};
        if (d == a) return {1, d.x, 1, d.y, 1};
        return {-1, 0, 0, 0, 0};
    }
    T p = (c - a) / (d - c), q = det;
    T xp = a.x * q + (b.x - a.x) * p, xq = q;
    T yp = a.y * q + (b.y - a.y) * p, yq = q;
    if (xq < 0) { xp = -xp; xq = -xq; }
    if (yq < 0) { yp = -yp; yq = -yq; }
    T g_x = __gcd(xp, xq); xp /= g_x; xq /= g_x;
    T g_y = __gcd(yp, yq); yp /= g_y; yq /= g_y;
    int f = 4;
    if ((xp == a.x * xq && yp == a.y * yq) || (xp == b.x * xq && yp == b.y * yq)) f = 1;
    if ((xp == c.x * xq && yp == c.y * yq) || (xp == d.x * xq && yp == d.y * yq)) f = 1;
    return { f, xp, xq, yp, yq };
}
// [2] 원-직선 교차 / Param: 직선 ab, 원(c, r)
// Return: 교점 좌표 목록 (a -> b 방향 순서 정렬됨)
vector<Pd> lineCircle(P a, P b, P c, double r) {
    P ab = b - a;
    Pd p = a.d() + ab.d() * ((c - a) * ab / (double)ab.dist2());
    double h2 = r * r - (p - c.d()).dist2();
    if (h2 < -EPS) return {};
    if (abs(h2) < EPS) return {p};
    Pd h = ab.d() * (sqrt(h2) / sqrt(ab.dist2()));
    return {p - h, p + h};
}
// [3] 원-다각형 교차 넓이
// Param: 원(c, r), 다각형 poly (CCW/CW 무관) Return: 교차하는 영역의 넓이
double areaCirclePoly(P c, double r, const vector<P>& poly) {
    auto tri = [&](Pd p, Pd q) {
        Pd d = q - p;
        double a = d * p / d.dist2(), b = (p.dist2() - r * r) / d.dist2();
        double det = a * a - b;
        if (det <= EPS) return r * r * atan2(p / q, p * q);
        double t1 = -a - sqrt(max(0.0, det)), t2 = -a + sqrt(max(0.0, det));
        if (t2 < -EPS || t1 > 1.0 + EPS) return r * r * atan2(p / q, p * q);
        Pd u = p + d * max(0.0, t1), v = p + d * min(1.0, t2);
        return r * r * atan2(p / u, p * u) + u / v + r * r * atan2(v / q, v * q);
    };
    double res = 0; int n = poly.size();
    for(int i = 0; i < n; i++) 
        res += tri((poly[i] - c).d(), (poly[(i + 1) % n] - c).d());
    return res * 0.5;
}
// [4] 볼록 다각형-직선 교차 (O(log N)) Param: 볼록 다각형 h (CCW), 직선 ab
// Return: {i, j} -> 직선이 변(i, i+1)과 변(j, j+1)을 교차함. 안만나면 {-1, -1}
int extrVertex(const vector<P>& h, P dir) {
    int n = h.size();
    auto cmp = [&](int i, int j) { return ccw({0,0}, dir, h[i%n] - h[j%n]); };
    auto isExtr = [&](int i) { return cmp(i, i - 1 + n) >= 0 && cmp(i, i + 1) > 0; };
    if (isExtr(0)) return 0;
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (isExtr(m)) return m;
        if (cmp(l + 1, l) > 0) {
            if (cmp(m + 1, m) > 0 && cmp(l, m) > 0) r = m; else l = m;
        } else {
            if (cmp(m + 1, m) <= 0 && cmp(l, m) < 0) l = m; else r = m;
        }
    }
    return l;
}
array<int,2> hullLineInter(const vector<P>& h, P a, P b) {
    P dir = b - a, per = {-dir.y, dir.x};
    int n = h.size();
    int i1 = extrVertex(h, per), i2 = extrVertex(h, per * -1);
    if (ccw(a, b, h[i1]) * ccw(a, b, h[i2]) > 0) return {-1, -1};
    auto search = [&](int s, int e) {
        if (ccw(a, b, h[s]) == 0) return s;
        int l = s, r = e;
        if (r < l) r += n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (ccw(a, b, h[m % n]) == ccw(a, b, h[s])) l = m; else r = m;
        }
        return l % n;
    };
    return {search(i1, i2), search(i2, i1)};
}