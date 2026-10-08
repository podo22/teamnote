/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 다각형 내부 판별 (CCW/CW 순서 무관), O(N)
bool InPoly(const vector<P>& v, P p) {
  int n = sz(v); bool chk = false;
  for (int i = 0; i < n; i++) {
    P a = v[i], b = v[(i+1)%n];
    ll cp = (b-a)/(p-a);
    if (!cp && (a-p)*(b-p) <= 0) return true; // false: exclude boundary
    if ((a.y > p.y) != (b.y > p.y) && (cp > 0) == (b.y > a.y))
      chk = !chk;
  }
  return chk;
}
// CCW 정렬된 다각형 내부 판별, O(log N)
bool InConvPoly(const vector<P>& v, P p) {
  int n = sz(v); if (n<3) return false;
  // ccw <= 0 || ccw >= 0: exclude boundary
  if (ccw(v[0], v[1], p) < 0 || ccw(v[0], v.back(), p) > 0) return false;
  int l = 1, r = n - 1;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    if (ccw(v[0], v[mid], p) >= 0) l = mid;
    else r = mid;
  }
  return ccw(v[l], v[l + 1], p) >= 0; // > 0: exclude boundary
}