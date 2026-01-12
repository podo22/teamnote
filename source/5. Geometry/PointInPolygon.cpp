/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 다각형 내부 판별 (CCW/CW 순서 무관)
bool InPoly(const vector<P>& v, P p) {
  int n = sz(v); bool chk = false;
  for (int i = 0; i < n; i++) {
    P a = v[i], b = v[(i + 1) % n];
    if ((b - a) / (p - a) == 0 && (a - p) * (b - p) <= 0) return true; // false: exclude boundary
    if ((a.y > p.y) != (b.y > p.y)) {
      double ix = (double)(b.x-a.x) * (p.y-a.y) / (double)(b.y-a.y) + a.x;
      if (p.x < ix) chk = !chk;
    }
  }
  return chk;
}