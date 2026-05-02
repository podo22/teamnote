/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/13510
 */
struct SegTree {
  using T = ll;
  const T I = 0, L = I; // MAX: -1e18, SUM: 0, MIN: 1e18
  T merge(T a, T b) { return a+b; };
  T calc(T val, int st, int en) { return val * (en-st+1); /* return val; when MINMAX */ }
  int n;
  vector<T> tree, lazy;
  SegTree(int n) : n(n) { tree.resize(4*n+1, I); lazy.resize(4*n+1, L); }
  void push(int nd, int st, int en) {
    if (lazy[nd] == L) return;
    tree[nd] = calc(lazy[nd], st, en);
    if (st != en) lazy[nd*2] = lazy[nd], lazy[nd*2+1] = lazy[nd];
    lazy[nd] = L;
  }
  void _update(int nd, int st, int en, int l, int r, T val) {
    push(nd, st, en);
    if (r < st || en < l) return;
    if (l <= st && en <= r) { lazy[nd] = val; push(nd, st, en); return; }
    int mid = (st+en)/2;
    _update(nd*2, st, mid, l, r, val); _update(nd*2+1, mid+1, en, l, r, val);
    tree[nd] = merge(tree[nd*2], tree[nd*2+1]);
  }
  T _query(int nd, int st, int en, int l, int r) {
    push(nd, st, en);
    if (r < st || en < l) return I;
    if (l <= st && en <= r) return tree[nd];
    int mid = (st+en)/2;
    return merge(_query(nd*2, st, mid, l, r), _query(nd*2+1, mid+1, en, l, r));
  }
  void update(int idx, T val) { _update(1, 1, n, idx, idx, val); }
  void update(int l, int r, T val) { _update(1, 1, n, l, r, val); }
  T query(int idx) { return _query(1, 1, n, idx, idx); }
  T query(int l, int r) { return _query(1, 1, n, l, r); }
};
struct HLD {
  int n, pv;
  vector<vector<int>> adj;
  vector<int> siz, dep, par, top, in;
  SegTree seg;
  HLD(int n) : n(n), adj(n+1), siz(n+1), dep(n+1), par(n+1), top(n+1), in(n+1), seg(n) {}
  void add(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
  void dfs1(int u, int p) {
    siz[u] = 1; dep[u] = dep[p]+1; par[u] = p;
    for (auto& v : adj[u]) {
      if (v == p) continue;
      dfs1(v, u); siz[u] += siz[v];
      if (siz[v] > siz[adj[u][0]] || adj[u][0] == p) swap(v, adj[u][0]);
    }
  }
  void dfs2(int u, int p) {
    in[u] = ++pv;
    for (auto v : adj[u]) {
      if (v == p) continue;
      top[v] = (v == adj[u][0] ? top[u] : v);
      dfs2(v, u);
    }
  }
  void build() {
    pv = 0;
    for (int i = 1; i <= n; i++) {
      if (!siz[i]) {
        top[i] = i;
        dfs1(i, 0); dfs2(i, 0);
      }
    }
  }
  void update(int u, int val) { seg.update(in[u], val); }
  ll query(int u, int v, bool edge = false) {
    ll res = seg.I;
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      res = seg.merge(res, seg.query(in[top[u]], in[u]));
      u = par[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return seg.merge(res, seg.query(in[u]+edge, in[v]));
  }
};