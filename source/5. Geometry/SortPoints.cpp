/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// Sorts points by angle relative to the bottom-left point (CCW).
void SortByAngle(vector<P>& v) {
  if (v.size() < 2) return;
  swap(v[0], *min_element(v.begin(), v.end(), [](const P& a, const P& b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
  }));
  sort(v.begin() + 1, v.end(), [&](const P& a, const P& b) {
    ll cp = (a - v[0]) / (b - v[0]); if (cp != 0) return cp > 0;
    return (a - v[0]).dist2() < (b - v[0]).dist2();
  });
}
// Sorts points by angle around a given point 'cent' in the range [0, 360).
void SortAroundPoint(vector<P>& v, P cent = {0, 0}) {
  auto half = [](const P& p) { return p.y > 0 || (p.y == 0 && p.x > 0); };
  sort(v.begin(), v.end(), [&](const P& a, const P& b) {
    P aa = a-cent, bb = b-cent;
    if (half(aa) != half(bb)) return half(aa) > half(bb);
    return (aa / bb) > 0; 
  });
}