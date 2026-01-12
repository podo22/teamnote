/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
vector<P> ConvexHull(vector<P> ps) { // Monotone chain
  if (sz(ps) <= 2) return ps;
  sort(all(ps)); vector<P> v(sz(ps)+2);
  int s = 0, t = 0;
  for (int i = 2; i--; s = --t, reverse(all(ps))) {
    for (P p : ps) { // include boundary : ccw < 0
      while (t >= s+2 && ccw(v[t-2], v[t-1], p) <= 0) t--;
      v[t++] = p;
    }
  }
  v.resize(t - (t > 1)); return v;
}