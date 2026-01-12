/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/2389 (2D)
 * https://www.acmicpc.net/problem/11930 (3D)
 */
Pd getC(Pd a, Pd b) { return (a + b) / 2.0; }
Pd getC(Pd a, Pd b, Pd c) {
  Pd u = b-a, v = c-a; double d = 2*(u/v);
  if (abs(d) < EPS) return {0, 0};
  return a - (v * u.dist2() - u * v.dist2()).rot90() / d;
}
/* // for 3D
Pd getC(Pd a, Pd b, Pd c) {
  Pd u = b-a, v = c-a, n = u/v;
  if (n.dist2() < EPS) return getC(a, b);
  Pd top = (n/u) * v.dist2() + (v/n) * u.dist2();
  return a + top / (2*n.dist2());
}
Pd getC(Pd a, Pd b, Pd c, Pd d) { 
  Pd p = b-a, q = c-a, r = d-a;
  double bot = ((p / q) * r) * 2.0;
  if (abs(bot) < EPS) return a;
  Pd top = (p/q) * r.dist2() + (q/r) * p.dist2() + (r/p) * q.dist2();
  return a + top / bot;
} */
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
pair<Pd,double> min_circle(vector<Pd> v) {
  shuffle(all(v), rng);
  Pd c = { 0, 0 }; double r = 0;
  auto dist = [&](Pd p1, Pd p2) { return sqrt((p1-p2).dist2()); };
  auto chk = [&](Pd p) { return dist(c, p) > r+EPS; };
  for (int i = 0; i < sz(v); i++) if (chk(v[i])) {
    c = v[i]; r = 0;
    for (int j = 0; j < i; j++) if (chk(v[j])) {
      c = getC(v[i], v[j]); r = dist(c, v[i]);
      for (int k = 0; k < j; k++) if (chk(v[k])) {
        c = getC(v[i], v[j], v[k]); r = dist(c, v[k]);
      }
    }
  }
  return { c, r };
}