/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
*/
// add/set: 구간 덧셈/대입, query: {sum,mn,mx}.
// find/find_kth는 실제 사용하는 인덱스 범위를 지정.
template<typename T = ll> struct SegTree {
  struct Nd { T sum, mn, mx; };
  struct Lz { T add, set; bool has; };
  int n; vector<Nd> tr; vector<Lz> lz;
  SegTree(int n) : n(n), tr(4*n+5), lz(4*n+5, { 0, 0, 0 }) {}
  Nd id() { return { 0, numeric_limits<T>::max(), numeric_limits<T>::lowest() }; }
  Nd merge(Nd a, Nd b) { return { a.sum+b.sum, min(a.mn,b.mn), max(a.mx,b.mx) }; }
  Lz comp(Lz f, Lz g) { // f(g(x))
    if (f.has) return f;
    g.add += f.add; return g;
  }
  void apply(int nd, int s, int e, Lz f) {
    if (f.has) tr[nd] = { f.set*(e-s+1), f.set, f.set };
    tr[nd].sum += f.add*(e-s+1);
    tr[nd].mn += f.add; tr[nd].mx += f.add;
    lz[nd] = comp(f, lz[nd]);
  }
  void push(int nd, int s, int e) {
    if (!lz[nd].has && lz[nd].add == 0) return;
    if (s != e) {
      int m = (s+e)>>1;
      apply(nd<<1, s, m, lz[nd]);
      apply(nd<<1|1, m+1, e, lz[nd]);
    }
    lz[nd] = { 0, 0, 0 };
  }
  void build(int nd, int s, int e, const vector<T>& a) {
    lz[nd] = { 0, 0, 0 };
    if (s == e) {
      T v = s < sz(a) ? a[s] : 0;
      return void(tr[nd] = { v, v, v });
    }
    int m = (s+e)>>1;
    build(nd<<1, s, m, a); build(nd<<1|1, m+1, e, a);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  void upd(int nd, int s, int e, int l, int r, Lz f) {
    if (l > r || r < s || e < l) return;
    if (l <= s && e <= r) return apply(nd, s, e, f);
    push(nd, s, e); int m = (s+e)>>1;
    upd(nd<<1, s, m, l, r, f); upd(nd<<1|1, m+1, e, l, r, f);
    tr[nd] = merge(tr[nd<<1], tr[nd<<1|1]);
  }
  Nd qry(int nd, int s, int e, int l, int r) {
    if (l > r || r < s || e < l) return id();
    if (l <= s && e <= r) return tr[nd];
    push(nd, s, e); int m = (s+e)>>1;
    return merge(qry(nd<<1, s, m, l, r),
                 qry(nd<<1|1, m+1, e, l, r));
  }
  int walk(int nd, int s, int e, int l, int r, Nd& pref, auto& chk) {
    if (l > r || r < s || e < l) return -1;
    if (l <= s && e <= r && !chk(pref, tr[nd])) {
      pref = merge(pref, tr[nd]); return -1;
    }
    if (s == e) return s;
    push(nd, s, e); int m = (s+e)>>1;
    int ret = walk(nd<<1, s, m, l, r, pref, chk);
    return ret != -1 ? ret : walk(nd<<1|1, m+1, e, l, r, pref, chk);
  }
  void build(const vector<T>& a) { build(1, 0, n, a); }
  void add(int l, int r, T x) { upd(1, 0, n, l, r, { x, 0, 0 }); }
  void set(int l, int r, T x) { upd(1, 0, n, l, r, { 0, x, 1 }); }
  Nd query(int l, int r) { return qry(1, 0, n, l, r); }
  T qsum(int l, int r) { return query(l, r).sum; }
  T qmin(int l, int r) { return query(l, r).mn; }
  T qmax(int l, int r) { return query(l, r).mx; }
  // [l,i]가 조건을 처음 만족하는 i. 없으면 -1. O(log n).
  // chk(pref,node): 합친 구간의 판정. 확장 시 false -> true만 가능.
  int find(auto chk, int l = 0, int r = -1) {
    if (r == -1) r = n;
    Nd pref = id(); return walk(1, 0, n, l, r, pref, chk);
  }
  // [l,i] 합 >= k인 첫 i. 원소 비음수, k>=1. 없으면 -1.
  int find_kth(T k, int l = 0, int r = -1) {
    if (k <= 0) return -1;
    return find([&](Nd a, Nd b) { return a.sum+b.sum >= k; }, l, r);
  }
};
SegTree<ll> seg(sz(a)-1); seg.build(a); // 0-based
seg.add(1, 3, 2); seg.set(2, 4, 3); // a[1..3] += 2, a[2..4] = 3
seg.qsum(1, 3); seg.qmin(1, 3); seg.qmax(1, 3); //합, 최솟값, 최댓값
seg.find_kth(5); // 누적합 >= 5인 첫 idx. 원소 비음수
seg.find([&](auto p, auto v) { return max(p.mx, v.mx) >= 4; }); // 첫 a[i]>=4