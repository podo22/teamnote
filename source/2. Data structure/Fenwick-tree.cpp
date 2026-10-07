/**
 * [Metadata]
 * Source : https://github.com/kidw0124/ACShoooooooooot-Teamnote/blob/main/src/data-structure/fenwick-tree.cpp
 *          https://github.com/kidw0124/ACShoooooooooot-Teamnote/blob/main/src/data-structure/2d-fenwick-tree.cpp
 * [Tested on]
 * 
 */
struct Fenwick {
  const ll MAXN = 100000;
  vector<ll> tree; int SZ;
  Fenwick(ll n) : tree(n), SZ(n) {}
  Fenwick() : Fenwick(MAXN) {}
  ll query(ll p) { // sum from index 0 to p, inclusive
    ll ret = 0;
    for (; p >= 0; p = (p & (p+1)) - 1) ret += tree[p];
    return ret;
  }
  void add(ll p, ll val) {
    for (; p < SZ; p |= p+1) tree[p] += val;
  }
};
// Ex. inversion counting
vector<ll> v = a; compress(v);
Fenwick bit(sz(v)); ll inv = 0;
for (int i = 0; i < sz(a); i++) {
  int x = lower_bound(all(v), a[i]) - v.begin();
  inv += i - bit.query(x);
  bit.add(x, 1);
}
// Fenwick_2d<int> T(n+1,m+1) for nxm grid indexed from 1
template<class T> struct Fenwick_2d {
  vector<vector<T>> x;
  Fenwick_2d(int n, int m) : x(n, vector<T>(m)) { }
  void add(int k1, int k2, int a) { // x[k] += a
    for (; k1 < sz(x); k1 |= k1+1)
      for (int k = k2; k < sz(x[k1]); k |= k+1) x[k1][k] += a;
  }
  T sum(int k1, int k2) { // return x[0]+...+x[k]
    T s = 0;
    for (; k1 >= 0; k1 = (k1 & (k1 + 1)) - 1)
      for (int k = k2; k >= 0; k = (k&(k+1))-1) s += x[k1][k];
    return s;
  }
};