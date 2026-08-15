/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://atcoder.jp/contests/abc328/tasks/abc328_f
 * https://codeforces.com/contest/766/problem/D
 */
struct DSU {
  vector<int> p; int comp;
  DSU(int n) : p(n+1, -1), comp(n) {}
  int find(int x) {
    return p[x] < 0 ? x : p[x] = find(p[x]);
  }
  bool merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return false;
    if (p[x] > p[y]) swap(x, y);
    p[x] += p[y]; p[y] = x; comp--;
    return true;
  }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -p[find(x)]; }
};
struct WeightedDSU {
  vector<int> p, d;
  WeightedDSU(int n) : p(n+1), d(n+1, 0) { iota(all(p), 0); }
  int find(int x) {
    if (p[x] == x) return x;
    int r = find(p[x]);
    d[x] += d[p[x]];
    return p[x] = r;
  }
  int diff(int a, int b) { find(a); find(b); return d[a]-d[b]; } // for parity: ret &1
  bool merge(int a, int b, int w) { // a-b = w
    int pa = find(a), pb = find(b);
    if (pa == pb) return diff(a, b) == w;
    d[pa] = w + d[b]-d[a]; p[pa] = pb;
    return true;
  }
  bool same(int a, int b) { return find(a) == find(b); }
};