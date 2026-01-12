/**
 * [Metadata]
 * Source : https://github.com/kidw0124/ACShoooooooooot-Teamnote/blob/main/src/data-structure/fenwick-tree.cpp
 *          https://github.com/kidw0124/ACShoooooooooot-Teamnote/blob/main/src/data-structure/2d-fenwick-tree.cpp
 * [Tested on]
 * 
 */
struct Fenwick {
  const ll MAXN = 100000;
  vector<ll> tree; int TSIZE;
  Fenwick(ll sz) : TSIZE(sz+1), tree(sz + 1) {}
  Fenwick() : Fenwick(MAXN) {}
  ll query(ll p) {  // sum from index 1 to p, inclusive
    ll ret = 0;
    for (; p > 0; p -= p & -p) ret += tree[p];
    return ret;
  }
  void add(ll p, ll val) {
    for (; p <= TSIZE; p += p & -p) tree[p] += val;
  }
};
// Fenwick_2d<int> Tree(n+1,m+1) for nxm grid indexed from 1
template <class T>struct Fenwick_2d {
  vector<vector<T>> x;
  Fenwick_2d(int n, int m) : x(n, vector<T>(m)) { }
  void add(int k1, int k2, int a) { // x[k] += a
    for (; k1 < x.size(); k1 |= k1 + 1)
      for (int k = k2; k < x[k1].size(); k |= k + 1) x[k1][k] += a;
  }
  T sum(int k1, int k2) { // return x[0]+...+x[k]
    T s = 0;
    for (; k1 >= 0; k1 = (k1 & (k1 + 1)) - 1)
      for (int k = k2; k >= 0; k = (k & (k + 1)) - 1) s += x[k1][k];
    return s;
  }
};