/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://codeforces.com/contest/2223/problem/B
 */
auto getInvs = [&](vector<ll> v) -> ll {
  if (v.empty()) return 0;
  vector<ll> tmp(sz(v));
  auto solve = [&](auto solve, int l, int r) -> ll {
    if (l >= r) return 0;
    int m = (l+r)/2;
    ll res = solve(solve, l, m) + solve(solve, m+1, r);
    int i = l, j = m+1, k = l;
    while (i <= m && j <= r) {
      if (v[i] <= v[j]) tmp[k++] = v[i++];
      else tmp[k++] = v[j++], res += m-i+1;
    }
    while (i <= m) tmp[k++] = v[i++];
    while (j <= r) tmp[k++] = v[j++];
    for (int i = l; i <= r; i++) v[i] = tmp[i];
    return res;
  };
  return solve(solve, 0, sz(v)-1);
};