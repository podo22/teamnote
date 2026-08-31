/**
 * [Metadata]
 * Author : 
 * [Tested on]
 * 
 */
template <typename T>
struct MergeSortTree {
  int sz;
  vector<vector<T>> tr; // Space: O(N log N)
  MergeSortTree(int n) {
    sz = 1; while (sz < n) sz <<= 1;
    tr.resize(sz*2);
  }
  void add(int x, T v) { tr[x+sz].push_back(v); }
  void build() { // Build: O(N log N)
    for (int i = sz-1; i > 0; i--) {
      tr[i].resize(sz(tr[i*2]) + sz(tr[i*2+1]));
      merge(all(tr[i*2]), all(tr[i*2+1]), tr[i].begin());
    }
  }
  int query(int l, int r, T k) { // Query: O(log^2 N)
    int res = 0;
    for (l += sz, r += sz; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res += tr[l].end() - upper_bound(all(tr[l]), k); 
        l++; }
      if (!(r & 1)) {
        res += tr[r].end() - upper_bound(all(tr[r]), k);
        r--; }
      /*
       - Count < k: lower_bound(all(v)) - v.begin()
       - Count <= k: upper_bound(all(v)) - v.begin()
       - Count >= k: v.end() - lower_bound(all(v))
       - Count > k: v.end() - upper_bound(all(v))
      */
    }
    return res;
  }
};