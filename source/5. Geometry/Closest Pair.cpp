/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* https://judge.yosupo.jp/problem/closest_pair
*/
struct P { ll x, y; int id; };
// O(N log N), ret: {거리, id1, id2}
array<ll,3> closestPair(vector<P> &v, const auto &dist) {
  sort(all(v), [](const P &a, const P &b) { return a.x < b.x; });
  auto cmp = [](const P &a, const P &b) { return a.y == b.y ? a.x < b.x : a.y < b.y; };
  set<P,decltype(cmp)> s(cmp);
  ll d = 9e18; array<ll,3> ans = { d, -1, -1 };
  for (int i = 0, j = 0; i < sz(v); i++) {
    while (j < i && dist(v[i], {v[j].x, v[i].y}) >= d) s.erase(v[j++]);
    auto scan = [&](auto it, auto end) {
      for (; it != end; it++) {
        if (dist(v[i], {v[i].x, it->y}) >= d) break;
        ll cur = dist(v[i], *it);
        if (cur < d) ans = { d = cur, v[i].id, it->id };
      }
    };
    auto it = s.lower_bound({ LLONG_MIN, v[i].y, -1 });
    scan(it, s.end()); scan(make_reverse_iterator(it), s.rend());
    s.insert(v[i]);
  }
  return ans;
}
closestPair(pv, [](P a, P b) { return (a-b).dist2(); }); // 유클리드 제곱
closestPair(pv, [](P a, P b) { return abs(a.x-b.x) + abs(a.y-b.y); }); // 맨해튼
closestPair(pv, [](P a, P b) { return max(abs(a.x-b.x), abs(a.y-b.y)); }); // 체비셰프