/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
template <typename T, typename Op>
struct SparseTable {
  int n, lg; Op f;
  vector<vector<T>> st;
  SparseTable(const vector<T>& v, Op op) : n(sz(v)), f(op) {
    lg = __lg(max(1, n)) + 1;
    st.assign(lg, vector<T>(n));
    st[0] = v;
    for (int i = 1; i < lg; i++) {
      int len = 1 << i;
      for (int m = len; m < n+len; m += len*2) {
        st[i][m-1] = v[m-1];
        for (int j = m-2; j >= max(0, m-len); j--)
          st[i][j] = f(v[j], st[i][j+1]);
        if (m < n) {
          st[i][m] = v[m];
          for (int j = m+1; j < min(n, m+len); j++)
            st[i][j] = f(st[i][j-1], v[j]);
        }
      }
    }
  }
  T query(int l, int r) const { // [l, r], 0-idx
    if (l == r) return st[0][l];
    int k = __lg(l ^ r);
    return f(st[k][l], st[k][r]);
  }
};
// SparseTable st(v, [](ll a, ll b){ return min(a, b); }); // RMQ
// SparseTable st(v, [](ll a, ll b){ return gcd(a, b); }); // Range GCD
// SparseTable st(v, [](ll a, ll b){ return a + b; }); // Range Sum