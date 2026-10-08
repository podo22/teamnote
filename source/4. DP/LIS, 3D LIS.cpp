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
  map<int,pair<int,int>> m; // y -> {최소 z, 원본 인덱스}
  int get(int y, int z) const {
    auto it = m.lower_bound(y); // non-strict: upper_bound(y)
    if (it == m.begin()) return -1;
    auto [pz, id] = prev(it)->second;
    return pz < z ? id : -1; // non-strict: pz <= z
  }
  void add(int y, int z, int id) {
    auto it = m.lower_bound(y);
    if (it != m.begin() && prev(it)->second.first <= z) return;
    while (it != m.end() && it->second.first >= z) it = m.erase(it);
    m.insert(it, { y, { z, id } });
  }
};
// 세 좌표가 모두 엄격히 증가하는 최장 체인(인덱스 반환).
vector<int> LIS3D(const vector<array<int,3>>& v) {
  int n = sz(v), last = -1;
  vector<int> ord(n), pre(n, -1); iota(all(ord), 0);
  sort(all(ord), [&](int i, int j) {
    // non-strict: return v[i] < v[j];
    if (v[i][0] != v[j][0]) return v[i][0] < v[j][0];
    return v[i][1] > v[j][1];
  });
  vector<Cand> res;
  for (int i : ord) {
    auto [x, y, z] = v[i];
    int lo = 0, hi = sz(res);
    while (lo < hi) {
      int mid = (lo+hi)/2;
      if (res[mid].get(y, z) != -1) lo = mid+1;
      else hi = mid;
    }
    if (lo) pre[i] = res[lo-1].get(y, z);
    if (lo == sz(res)) res.emplace_back(), last = i;
    res[lo].add(y, z, i);
  }
  vector<int> ans;
  for (int i = last; i != -1; i = pre[i]) ans.push_back(i);
  reverse(all(ans)); return ans;
}