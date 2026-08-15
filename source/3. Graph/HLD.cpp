/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* https://www.acmicpc.net/problem/13510
*/
struct SegTree {
  const ll INF = 4e18;
  struct T { ll sum, mn, mx; };
  struct L { ll add, set; bool has; };
  int n; vector<T> tr; vector<L> lz;
  SegTree(int n) : n(n), tr(4*n+1), lz(4*n+1, { 0, 0, 0 }) {}
  T id() { return { 0, INF, -INF }; }
  bool empty(L f) { return !f.has && f.add==0; }
  T merge(T a, T b) { return {a.sum+b.sum, min(a.mn,b.mn), max(a.mx,b.mx)}; }
  L comp(L f, L g) { // comp(f, g)(x) = f(g(x))
    if (f.has) return f;
    g.add += f.add;
    return g;
  }
  void apply(int nd, int s, int e, L f) {
    int len = e-s+1;
    if (f.has) tr[nd] = { f.set * len, f.set, f.set };
    tr[nd].sum += f.add * len;
    tr[nd].mn += f.add; tr[nd].mx += f.add;
  }
  void push(int nd, int s, int e) {
    if (empty(lz[nd])) return;
    apply(nd, s, e, lz[nd]);
    if (s != e) {
      lz[nd<<1]   = comp(lz[nd], lz[nd<<1]);
      lz[nd<<1|1] = comp(lz[nd], lz[nd<<1|1]);
    }
    lz[nd] = { 0, 0, 0 };
  }
  void build(int nd, int s, int e, const vector<ll>& a) {
    if (s == e) return void(tr[nd] = { a[s], a[s], a[s] });
    int m = (s+e)>>1;
    build(nd<<1, s, m, a);
    build(nd<<1|1, m+1, e, a);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  void upd(int nd, int s, int e, int l, int r, L f) {
    push(nd, s, e);
    if (r < s || e < l) return;
    if (l <= s && e <= r) {
      lz[nd] = comp(f, lz[nd]);
      push(nd, s, e);
      return;
    }
    int m = (s+e)>>1;
    upd(nd<<1, s, m, l, r, f);
    upd(nd<<1|1, m+1, e, l, r, f);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  T qry(int nd, int s, int e, int l, int r) {
    push(nd, s, e);
    if (r < s || e < l) return id();
    if (l <= s && e <= r) return tr[nd];
    int m = (s+e)>>1;
    return merge(qry(nd<<1, s, m, l, r), qry(nd<<1|1, m+1, e, l, r));
  }
  void build(const vector<ll>& a) { build(1, 0, n-1, a); }
  void add(int l, int r, ll x) { upd(1, 0, n-1, l, r, { x, 0, 0 }); }
  void set(int l, int r, ll x) { upd(1, 0, n-1, l, r, { 0, x, 1 }); }
  T query(int l, int r) { return qry(1, 0, n-1, l, r); }
  ll qsum(int l, int r) { return qry(1, 0, n-1, l, r).sum; }
  ll qmin(int l, int r) { return qry(1, 0, n-1, l, r).mn; }
  ll qmax(int l, int r) { return qry(1, 0, n-1, l, r).mx; }
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
      if (adj[u][0] == p || siz[v] > siz[adj[u][0]]) swap(v, adj[u][0]);
    }
  }
  void dfs2(int u, int p) {
    in[u] = pv++;
    for (auto v : adj[u]) {
      if (v == p) continue;
      top[v] = (v == adj[u][0] ? top[u] : v);
      dfs2(v, u);
    }
  }
  void build(const vector<ll>& a) { // a[u]: vertex value, 1-indexed
    pv = 0;
    for (int i = 1; i <= n; i++) {
      if (!siz[i]) {
        top[i] = i;
        dfs1(i, 0);
        dfs2(i, 0);
      }
    }
    vector<ll> base(n);
    for (int i = 1; i <= n; i++) base[in[i]] = a[i];
    seg.build(base);
  }
  void path_upd(int u, int v, ll x, bool edge = false) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      seg.add(in[top[u]], in[u], x); // or seg.set
      u = par[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    if (in[u] + edge <= in[v]) {
      seg.add(in[u] + edge, in[v], x); // or seg.set
    }
  }
  void setv(int u, ll x) { seg.set(in[u], in[u], x); }
  void addv(int u, ll x) { seg.add(in[u], in[u], x); }
  SegTree::T path_qry(int u, int v, bool edge = false) {
    SegTree::T res = seg.id();
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      res = seg.merge(res, seg.query(in[top[u]], in[u]));
      u = par[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return seg.merge(res, seg.query(in[u]+edge, in[v]));
  }
  ll qsum(int u, int v, bool edge = false) { return path_qry(u, v, edge).sum; }
  ll qmin(int u, int v, bool edge = false) { return path_qry(u, v, edge).mn; }
  ll qmax(int u, int v, bool edge = false) { return path_qry(u, v, edge).mx; }
};