mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const double EPS = 1e-9;
Pd getC(Pd a, Pd b) { return (a + b) / 2.0; }
Pd getC(Pd a, Pd b, Pd c) {
  Pd aa = b - a, bb = c - a;
  double c1 = aa * aa * 0.5, c2 = bb * bb * 0.5, d = aa / bb;
  return {a.x+(c1 * bb.y - c2 * aa.y)/d, a.y+(c2 * aa.x - c1 * bb.x)/d};
}
pair<Pd,double> solve(vector<Pd> v) {
  shuffle(all(v), rng);
  Pd p = { 0, 0 }; double r = 0;
  auto dist = [&](Pd p1, Pd p2) { return sqrt((p1-p2).dist2()); };
  for (int i = 0; i < sz(v); i++) if (dist(p, v[i]) > r + EPS) {
    p = v[i]; r = 0;
    for (int j = 0; j < i; j++) if (dist(p, v[j]) > r + EPS) {
      p = getC(v[i], v[j]); r = dist(p, v[i]);
      for (int k = 0; k < j; k++) if (dist(p, v[k]) > r + EPS) {
        p = getC(v[i], v[j], v[k]); r = dist(p, v[k]);
      }
    }
  }
  return { p, r };
}