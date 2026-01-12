/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// ccw 정렬된 convex에서 가장 먼 두 점
pair<P,P> Calipers(const vector<P>& v) {
  int n = sz(v); if (n < 2) return {v[0], v[0]};
  ll mx = 0; P a = v[0], b = v[1];
  for (int i = 0, j = 1; i < n; i++) {
    P t = v[(i+1)%n] - v[i];
    while ((t / (v[(j+1)%n] - v[j])) > 0) j = (j+1)%n;
    ll now = (v[i] - v[j]).dist2();
    if (now > mx) mx = now, a = v[i], b = v[j];
  }
  return { a, b };
}