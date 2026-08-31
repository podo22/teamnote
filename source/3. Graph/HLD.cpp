/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/13510
 */
// HLD: 트리 경로/서브트리 쿼리를 세그트리 구간으로 변환 (1-idx 정점).
// hld.build(a) // a[u]=정점 u 값 (1-indexed). 정점/간선 가중치 모두 지원
// path_upd(u,v,x, edge=0) // 경로 u~v에 x 적용 (edge=1이면 LCA 정점 제외, 간선용)
// setv(u,x)/addv(u,x) // 정점 단일 갱신
// qsum/qmin/qmax(u,v, edge=0) // 경로 쿼리
// * edge=true: 간선 가중치 문제에서 씀 (정점을 간선에 대응, LCA 빼고)
template<typename T> struct SegTree {
  struct Nd { T sum, mn, mx; };
  struct Lz { T add, set; bool has; };
  int n; vector<Nd> tr; vector<Lz> lz;
  SegTree(int n) : n(n), tr(4*n+1), lz(4*n+1, { 0, 0, 0 }) {}
  Nd id() { return { 0, numeric_limits<T>::max(), numeric_limits<T>::lowest() }; }
  bool empty(Lz f) { return !f.has && f.add==0; }
  Nd merge(Nd a, Nd b) { return { a.sum+b.sum, min(a.mn,b.mn), max(a.mx,b.mx) }; }
  Lz comp(Lz f, Lz g) { // comp(f, g)(x) = f(g(x))
    if (f.has) return f;
    g.add += f.add;
    return g;
  }
  void apply(int nd, int s, int e, Lz f) {
    int len = e-s+1;
    if (f.has) tr[nd] = { f.set * len, f.set, f.set };
    tr[nd].sum += f.add * len;
    tr[nd].mn += f.add; tr[nd].mx += f.add;
    lz[nd] = comp(f, lz[nd]);
  }
  void push(int nd, int s, int e) {
    if (empty(lz[nd])) return;
    if (s != e) {
      int m = (s + e) >> 1;
      apply(nd<<1, s, m, lz[nd]);
      apply(nd<<1|1, m+1, e, lz[nd]);
    }
    lz[nd] = { 0, 0, 0 };
  }
  void build(int nd, int s, int e, const vector<T>& a) {
    if (s == e) return void(tr[nd] = { a[s], a[s], a[s] });
    int m = (s+e)>>1;
    build(nd<<1, s, m, a);
    build(nd<<1|1, m+1, e, a);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  void upd(int nd, int s, int e, int l, int r, Lz f) {
    if (l > r || r < s || e < l) return;
    push(nd, s, e);
    if (l <= s && e <= r) {
      apply(nd, s, e, f);
      return;
    }
    int m = (s+e)>>1;
    upd(nd<<1, s, m, l, r, f);
    upd(nd<<1|1, m+1, e, l, r, f);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  Nd qry(int nd, int s, int e, int l, int r) {
    push(nd, s, e);
    if (l > r || r < s || e < l) return id();
    if (l <= s && e <= r) return tr[nd];
    int m = (s+e)>>1;
    return merge(qry(nd<<1, s, m, l, r), qry(nd<<1|1, m+1, e, l, r));
  }
  void build(const vector<T>& a) { build(1, 0, n-1, a); }
  void add(int l, int r, T x) { upd(1, 0, n-1, l, r, { x, 0, 0 }); }
  void set(int l, int r, T x) { upd(1, 0, n-1, l, r, { 0, x, 1 }); }
  Nd query(int l, int r) { return qry(1, 0, n-1, l, r); }
  T qsum(int l, int r) { return qry(1, 0, n-1, l, r).sum; }
  T qmin(int l, int r) { return qry(1, 0, n-1, l, r).mn; }
  T qmax(int l, int r) { return qry(1, 0, n-1, l, r).mx; }
};
template<typename T = ll> struct HLD {
  int n, pv;
  vector<vector<int>> adj;
  vector<int> siz, dep, par, top, in;
  SegTree<T> seg;
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
  void build(const vector<T>& a = {}) { // a[u]: vertex value, 1-indexed
    pv = 0;
    for (int i = 1; i <= n; i++) {
      if (!siz[i]) {
        top[i] = i;
        dfs1(i, 0);
        dfs2(i, 0);
      }
    }
    vector<T> base(n);
    if (sz(a)) for (int i = 1; i <= n; i++) base[in[i]] = a[i];
    seg.build(base);
  }
  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      u = par[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
  }
  int path_len(int u, int v) {
    return dep[u] + dep[v] - 2*dep[lca(u, v)] + 1;
  }
  void path_upd(int u, int v, T x, bool edge = false) {
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
  void setv(int u, T x) { seg.set(in[u], in[u], x); }
  void addv(int u, T x) { seg.add(in[u], in[u], x); }
  typename SegTree<T>::Nd path_qry(int u, int v, bool edge = false) {
    typename SegTree<T>::Nd res = seg.id();
    while (top[u] != top[v]) {
      if (dep[top[u]] < dep[top[v]]) swap(u, v);
      res = seg.merge(res, seg.query(in[top[u]], in[u]));
      u = par[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    return seg.merge(res, seg.query(in[u]+edge, in[v]));
  }
  T qsum(int u, int v, bool edge = false) { return path_qry(u, v, edge).sum; }
  T qmin(int u, int v, bool edge = false) { return path_qry(u, v, edge).mn; }
  T qmax(int u, int v, bool edge = false) { return path_qry(u, v, edge).mx; }
};