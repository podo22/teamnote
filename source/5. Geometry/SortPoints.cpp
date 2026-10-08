/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// cent 기준 [0,360) 각도순. 같은 방향은 가까운 점부터.
// cent와 같은 점은 맨 앞.
void Sort(vector<P>& v, P cent) {
  auto half = [](P p) { return p.y < 0 || (p.y == 0 && p.x < 0); };
  sort(all(v), [&](P a, P b) {
    a = a-cent; b = b-cent;
    if (half(a) != half(b)) return half(a) < half(b);
    ll cp = a/b;
    return cp ? cp > 0 : a.dist2() < b.dist2();
  });
}
// 최하단·최좌측 점 기준 각도순.
void Sort(vector<P>& v) {
  if (v.empty()) return;
  P cent = *min_element(all(v), [](P a, P b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
  });
  Sort(v, cent);
}
// Sort(v); / Sort(v, {0,0});