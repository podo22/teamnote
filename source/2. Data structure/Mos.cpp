/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct Query { int l, r, idx; };
vector<ll> mos(vector<int> a, vector<Query> q) {
  int n = sz(a);
  auto tmp = a; compress(tmp);
  for (auto &x : a) x = lower_bound(all(tmp), x) - tmp.begin();
  int k = *max_element(all(a)) + 1;
  int B = max(1, (int)(n / sqrt(max(1, sz(q)))));
  sort(all(q), [&](const Query& x, const Query& y) {
    int bx = x.l / B, by = y.l / B;
    if (bx != by) return bx < by;
    return (bx & 1) ? x.r > y.r : x.r < y.r;
  });
  vector<ll> cnt(k), res(sz(q));
  ll now = 0;
  auto add = [&](int i) { if (cnt[a[i]]++ == 0) now++; };
  auto remove = [&](int i) { if (--cnt[a[i]] == 0) now--; };
  int l = 0, r = 0; // 0-idx, [l, r)
  for (auto &[ql, qr, idx] : q) {
    while (l > ql) add(--l);
    while (r < qr) add(r++);
    while (l < ql) remove(l++);
    while (r > qr) remove(--r);
    res[idx] = now;
  }
  return res;
}