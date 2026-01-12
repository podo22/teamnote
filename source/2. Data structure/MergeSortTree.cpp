/**
 * [Metadata]
 * Author : ???
 * [Tested on]
 * 
 */
template <typename T>
struct MergeSortTree {
  int sz;
  vector<vector<T>> tree; // Space: O(N log N)
  MergeSortTree(int n) {
    sz = 1;
    while (sz < n) sz <<= 1;
    tree.resize(sz*2);
  }
  void add(int x, T v) { tree[x+sz].push_back(v); }
  void build() { // Build: O(N log N)
    for (int i = sz-1; i > 0; i--) {
      tree[i].resize(sz(tree[i*2]) + sz(tree[i*2+1]));
      merge(all(tree[i*2]), all(tree[i*2+1]), tree[i].begin());
    }
  }
  int query(int l, int r, T k) { // Query: O(log^2 N)
    int res = 0;
    for (l += sz, r += sz; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) {
        res += tree[l].end() - upper_bound(all(tree[l]), k); l++;
      }
      if (!(r & 1)) {
        res += tree[r].end() - upper_bound(all(tree[r]), k); r--;
      }
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