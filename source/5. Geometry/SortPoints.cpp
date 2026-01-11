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
// Sorts points by angle around origin (0,0) from range [0, 360).
void SortAroundOrigin(vector<P>& v) {
  auto half = [](const P& p) { return p.y > 0 || (p.y == 0 && p.x > 0); };
  sort(v.begin(), v.end(), [&](const P& a, const P& b) {
    if (half(a) != half(b)) return half(a) > half(b);
    return (a / b) > 0; 
  });
}