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
  map<int,int> m; // y -> 그 y에서의 최소 z
  bool chk(int y, int z) const {
    auto it = m.lower_bound(y);
    return it != m.begin() && prev(it)->second < z; // non-strict: <=
  }
  void add(int y, int z) {
    auto it = m.lower_bound(y);
    if (it != m.begin() && prev(it)->second <= z) return;
    while (it != m.end() && it->second >= z) it = m.erase(it);
    m.insert(it, {y, z});
  }
};
int LIS3D(vector<array<int,3>> v) {
  sort(all(v), [](auto &a, auto &b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] > b[1]; // non-strict: <
  });
  vector<Cand> res;
  for (auto [x, y, z] : v) {
    int lo = 0, hi = sz(res);
    while (lo < hi) {
      int mid = (lo+hi) / 2;
      if (res[mid].chk(y, z)) lo = mid + 1;
      else hi = mid;
    }
    if (lo == sz(res)) res.emplace_back();
    res[lo].add(y, z);
  }
  return sz(res);
}