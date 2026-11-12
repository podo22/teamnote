/**
 * [Metadata]
 * Original Author : JusticeHui, kactl
 * Reference : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Geometry/Intersect.cpp
 * Modified by : alreadysolved
 * [Tested on]
 * 
 */
using T = __int128_t; // T <= O(COORD^3)
// [1] 선분 교차 (정밀 좌표) / Param: 선분 ab, 선분 cd
// Return: {flag, xn, xd, yn, yd} -> 교점 (xn/xd, yn/yd)
// Flag: 0(안만남), 1(교점=끝점), 4(교차), -1(무수히 겹침)
tuple<int, T, T, T, T> segmentInter(P a, P b, P c, P d) {
  if (!isInter(a, b, c, d)) return {0, 0, 0, 0, 0};
  T det = (b - a) / (d - c);
  if (det == 0) {
    if (b < a) swap(a, b);
    if (d < c) swap(c, d);
    P l = max(a, c), r = min(b, d);
    if (l == r) return {1, l.x, 1, l.y, 1};
    return {-1, 0, 0, 0, 0};
  }
  T p = (c - a) / (d - c), q = det;
  T xp = a.x * q + (b.x - a.x) * p, xq = q;
  T yp = a.y * q + (b.y - a.y) * p, yq = q;
  if (xq < 0) { xp = -xp; xq = -xq; }
  if (yq < 0) { yp = -yp; yq = -yq; }
  T g_x = __gcd(xp < 0 ? -xp : xp, xq); xp /= g_x; xq /= g_x;
  T g_y = __gcd(yp < 0 ? -yp : yp, yq); yp /= g_y; yq /= g_y;
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
    double t1 = -a-sqrt(max(0.0, det)), t2 = -a+sqrt(max(0.0, det));
    if (t2 < -EPS || t1 > 1.0 + EPS) return r * r * atan2(p / q, p * q);
    Pd u = p + d * max(0.0, t1), v = p + d * min(1.0, t2);
    return r * r * atan2(p / u, p * u) + u / v + r * r * atan2(v / q, v * q);
  };
  double res = 0; int n = poly.size();
  for(int i = 0; i < n; i++) res += tri((poly[i] - c).d(), (poly[(i+1) % n] - c).d());
  return abs(res) * 0.5;
}
// [4] 볼록 다각형-직선 교차 (O(log N)) Param: 볼록 다각형 h (CCW), 직선 ab
// Return: {i, j} -> 직선이 변(i, i+1)과 변(j, j+1)을 교차함. 안만나면 {-1, -1}
int extrVertex(const vector<P>& h, P dir) {
  int n = sz(h);
  P base = h[1] - h[0], tar = dir * -1;
  auto half = [&](P p) {
    ll cp = base / p;
    return cp < 0 || (cp == 0 && base * p < 0);
  };
  int l = 0, r = n;
  while (l < r) {
    int m = (l + r) / 2;
    P e = h[(m+1)%n] - h[m];
    if (half(e) < half(tar) || (half(e) == half(tar) && e / tar > 0)) l = m+1;
    else r = m;
  }
  return l % n;
}
array<int,2> hullLineInter(const vector<P>& h, P a, P b) {
  P dir = b - a; int n = h.size();
  int i1 = extrVertex(h, dir), i2 = extrVertex(h, dir * -1);
  if (ccw(a, b, h[i1]) * ccw(a, b, h[i2]) > 0) return {-1, -1};
  auto search = [&](int s, int e) {
    if (ccw(a, b, h[s]) == 0) return s;
    int l = s, r = e; if (r < l) r += n;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (ccw(a, b, h[m % n]) == ccw(a, b, h[s])) l = m; else r = m;
    }
    return l % n;
  };
  return {search(i1, i2), search(i2, i1)};
}