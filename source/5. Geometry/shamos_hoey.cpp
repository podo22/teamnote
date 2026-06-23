/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Geometry/shamos_hoey.cpp)
 * [Tested on]
 * 
 */
ll x_cur;
struct Line{
  PT p, d, p2; int idx;
  Line(PT a, PT b) {
    if (a >= b) swap(a, b);
    p = a; p2 = b; d = b - a;
  }
  ll eval() const {
    return d.y*(x_cur - p.x) + p.y*d.x;
  }
  bool operator<(const Line &v) const {
    ll y1 = eval(), y2 = v.eval();
    if (y1 == y2) return idx < v.idx;
    return y1 < y2;
  }
};
bool shamos_hoey(vector<Line> &v) {
  ll K = 1e9+7; int n = v.size();
  for (int i = 0; i < n; i++) {
    auto [x, y] = v[i].p;
    v[i].p = PT(x+K*y, y-K*x);
    auto [x2, y2] = v[i].p2;
    v[i].p2 = PT(x2+K*y2, y2-K*x2);
    if (v[i].p >= v[i].p2) swap(v[i].p, v[i].p2);
    v[i].d = v[i].p2 - v[i].p;
  }
  vector<array<ll, 4>> event;
  for (int i = 0; i < n; i++) {
    auto l = v[i];
    event.push_back({l.p.x, l.p.y, 0, i});
    event.push_back({l.p2.x, l.p2.y, 1, i});
  }
  sort(all(event));
  vector<multiset<Line>::iterator> iter(n+1);
  multiset<Line> S;
  for (auto [x, y, t, idx] : event) {
    x_cur = x;
    auto l1 = v[idx];
    if (t == 0) {
      auto it = S.insert(v[idx]);
      iter[idx] = it;
      if (next(it) != S.end()) {
        auto l2 = *next(it);
        if (isIntersect(l1.p, l1.p2, l2.p, l2.p2)) return true;
      }
      if (it != S.begin()) {
        auto l2 = *prev(it);
        if (isIntersect(l1.p, l1.p2, l2.p, l2.p2)) return true;
      }
    } else {
      auto it = iter[idx];
      if (it != S.begin() && next(it) != S.end()) {
        auto l1 = *prev(it);
        auto l2 = *next(it);
        if (isIntersect(l1.p, l1.p2, l2.p, l2.p2)) return true;
      }
      S.erase(it);
    }
  }
  return false;
}