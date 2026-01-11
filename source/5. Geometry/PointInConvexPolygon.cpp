// CCW 정렬된 다각형 내부/경계 판별, O(log N)
bool PointInConvexPolygon(const vector<P>& v, P p) {
  int n = v.size(); if (n < 3) return false;
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