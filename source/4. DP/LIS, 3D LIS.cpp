/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// a[i] < a[j] -> lower_bound, a[i] <= a[j] -> upper_bound
vector<int> LIS(vector<int> v) {
  int n = sz(v);
  vector<int> lis, pos(n);
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(all(lis), v[i]);
    pos[i] = it - lis.begin();
    if (it == lis.end()) lis.push_back(v[i]);
    else *it = v[i];
  }
  vector<int> res;
  for (int i = n-1, j = sz(lis)-1; i >= 0; i--) {
    if (pos[i] == j) {
      res.push_back(v[i]); j--;
    }
  }
  reverse(all(res));
  return res;
}
// 3D LIS
struct Cand {
  map<int,pair<ll,int>> m; // z -> {최대 누적 가치, 원본 인덱스}
  pair<ll,int> get(int z, bool strict) const {
    auto it = strict ? m.lower_bound(z) : m.upper_bound(z);
    if (it == m.begin()) return {0, -1};
    return prev(it)->second;
  }
  void add(int z, ll val, int id) {
    if (get(z, false).first >= val) return;
    auto it = m.lower_bound(z);
    while (it != m.end() && it->second.first <= val) it = m.erase(it);
    m.insert(it, { z, {val, id} });
  }
};
pair<ll,vector<int>> LIS3D(const vector<array<int,3>> &v, const vector<ll> &w, bool strict = true) {
  int n = sz(v), last = -1; ll best = 0;
  vector<int> ord(n), pre(n, -1), ys;
  iota(all(ord), 0);
  for (auto [x, y, z] : v) ys.push_back(y);
  compress(ys);
  sort(all(ord), [&](int i, int j) {
    if (!strict) return v[i] < v[j];
    if (v[i][0] != v[j][0]) return v[i][0] < v[j][0];
    return v[i][1] > v[j][1];
  });
  vector<Cand> bit(sz(ys)+1);
  for (int i : ord) {
    auto [x, y, z] = v[i];
    int p = lower_bound(all(ys), y) - ys.begin() + 1;
    pair<ll,int> prv = { 0, -1 };
    for (int j = p-strict; j > 0; j -= j&-j) prv = max(prv, bit[j].get(z, strict));
    ll cur = prv.first + w[i]; pre[i] = prv.second;
    if (last == -1 || best < cur) best = cur, last = i;
    for (int j = p; j < sz(bit); j += j&-j) bit[j].add(z, cur, i);
  }
  vector<int> ans;
  for (int i = last; i != -1; i = pre[i]) ans.push_back(i);
  reverse(all(ans)); return { best, ans };
}