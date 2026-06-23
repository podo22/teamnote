/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* https://judge.yosupo.jp/problem/closest_pair
*/
struct P { ll x, y; int id; };
ll dist(const P &a, const P &b) {
  return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}
array<ll,3> closestPair(vector<P> &v) {
  sort(all(v), [](const P &a, const P &b) { return a.x < b.x; });
  auto cmp = [](const P &a, const P &b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
  };
  set<P, decltype(cmp)> s(cmp);
  ll d = 9e18; array<ll,3> ans = { d, -1, -1 };
  for (int i = 0, j = 0; i < sz(v); i++) {
    while (j < i && (v[i].x-v[j].x)*(v[i].x-v[j].x) >= d) s.erase(v[j++]);
    ll dsq = sqrt(d)+1;
    auto it1 = s.lower_bound({ LLONG_MIN, v[i].y - dsq, -1 });
    auto it2 = s.upper_bound({ LLONG_MAX, v[i].y + dsq, -1 });
    for (auto it = it1; it != it2; it++) {
      ll cur = dist(v[i], *it);
      if (cur < d) ans = { d = cur, v[i].id, (*it).id };
    }
    s.insert(v[i]);
  }
  return ans;
}