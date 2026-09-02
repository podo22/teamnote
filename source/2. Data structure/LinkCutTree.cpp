/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// MAXN은 (초기 크기 + insert 총 횟수) 이상
const ll INF = 1e18, MAXN = 3e5+5;
struct BBST {
  struct Node {
    int l = 0, r = 0, p = 0, id = -1;
    ll cnt = 0, val = 0, sum = 0, mx = -INF, mn = INF, lz = 0;
    bool flip = false;
  } tr[MAXN];
  int rt = 0, ptr = 0, pos[MAXN];
  void clear() {
    fill(tr, tr+ptr+1, Node{}); rt = ptr = 0;
  }
  int new_nd(ll v = 0, int id = -1) {
    auto &n = tr[++ptr]; n.id = id;
    n.val = n.mx = n.mn = n.sum = v; n.cnt = 1;
    n.l = n.r = n.p = n.lz = 0; n.flip = false;
    if (id != -1) pos[id] = ptr;
    return ptr;
  }
  bool is_rt(int x) { return !tr[x].p || (tr[tr[x].p].l != x && tr[tr[x].p].r != x); }
  void update(int x) {
    if (!x) return;
    auto &n = tr[x], &l = tr[n.l], &r = tr[n.r];
    n.cnt = 1+l.cnt+r.cnt; n.sum = n.val + l.sum + r.sum;
    n.mx = max({n.val, n.l ? l.mx : -INF, n.r ? r.mx : -INF});
    n.mn = min({n.val, n.l ? l.mn : INF, n.r ? r.mn : INF});
  }
  void apply(int x, ll v) {
    if (!x) return;
    auto &n = tr[x]; n.val += v; n.lz += v;
    n.mx += v; n.mn += v; n.sum += v*n.cnt;
  }
  void push(int x) {
    if (!x) return;
    auto &n = tr[x];
    if (n.lz) {
      apply(n.l, n.lz); apply(n.r, n.lz); n.lz = 0;
    } if (n.flip) {
      swap(n.l, n.r);
      if (n.l) tr[n.l].flip ^= 1;
      if (n.r) tr[n.r].flip ^= 1;
      n.flip = false;
    }
  }
  void push_all(int x) {
    if (!is_rt(x)) push_all(tr[x].p);
    push(x);
  }
  void rotate(int x) {
    int p = tr[x].p, g = tr[p].p, b;
    if (x == tr[p].l) tr[p].l = b = tr[x].r, tr[x].r = p;
    else tr[p].r = b = tr[x].l, tr[x].l = p;
    tr[x].p = g; tr[p].p = x;
    if (b) tr[b].p = p;
    if (!is_rt(p)) (tr[g].l == p ? tr[g].l : tr[g].r) = x;
    else rt = x;
    update(p); update(x);
  }
  void splay(int x, int tgt = 0) {
    push_all(x);
    while (tr[x].p != tgt && !is_rt(x)) {
      int p = tr[x].p, g = tr[p].p;
      if (g != tgt && !is_rt(p)) {
        if ((tr[p].l == x) == (tr[g].l == p)) rotate(p);
        else rotate(x);
      } rotate(x);
    }
    if (!tgt && is_rt(x)) rt = x;
  }
  // k번째 원소를 tg(기본 0=루트) 아래로 splay
  void find_kth(int k, int tg = 0) {
    int cur = rt;
    while (push(cur), 1) {
      int lc = tr[tr[cur].l].cnt;
      if (k == lc+1) break;
      if (k <= lc) cur = tr[cur].l;
      else k -= lc+1, cur = tr[cur].r;
    }
    splay(cur, tg);
  }
  // 구간을 서브트리로 모음 (루트 반환, 1 <= l <= r <= N)
  int gather(int l, int r) {
    find_kth(r+2); find_kth(l, rt);
    return tr[tr[rt].l].r;
  }
  int build(int l, int r, int p, const vector<ll> &v) {
    if (l > r) return 0;
    int mid = (l+r)/2, val = 0, id = -1;
    if (mid > 1 && mid < sz(v)+2) val = v[mid-2], id = mid-1;
    int x = new_nd(val, id);
    tr[x].p = p;
    tr[x].l = build(l, mid-1, x, v);
    tr[x].r = build(mid+1, r, x, v);
    update(x); return x;
  }
  void init(const vector<ll> &v) { // v는 0-idx vector
    clear();
    rt = build(1, sz(v)+2, 0, v);
  }
  void add_val(int l, int r, ll v) { apply(gather(l, r), v); }
  int get_idx(int id) { // ID 원소의 인덱스 반환 (1-idx)
    push_all(pos[id]); splay(pos[id]);
    return tr[tr[rt].l].cnt;
  }
  ll get_val(int k) { find_kth(k+1); return tr[rt].val; }
  void reverse(int l, int r) { tr[gather(l, r)].flip ^= 1; }
  // k번째 뒤(0: 앞 / N: 뒤)에 값 v (ID: id) 삽입
  void insert(int k, ll v, int id = -1) {
    find_kth(k+1); find_kth(k+2, rt);
    int x = new_nd(v, id), p = tr[rt].r;
    tr[p].l = x; tr[x].p = p;
    update(p); update(rt); splay(x);
  }
  void erase(int l, int r) {
    int p = tr[gather(l, r)].p;
    tr[p].r = 0; update(p); splay(p);
  }
  void shift(int l, int r, int k) { // k칸 우측 시프트
    int L = r-l+1; k = (k%L+L) % L;
    if (!k) return;
    reverse(l, r); reverse(l, l+k-1); reverse(l+k, r);
  }
  int build_val(int l, int r, int p, const vector<pair<ll,int>> &v) {
    if (l > r) return 0;
    int mid = (l + r) / 2;
    ll val = 0; int id = -1;
    if (mid == 1) val = -INF;
    else if (mid == sz(v)+2) val = INF;
    else val = v[mid-2].first, id = v[mid-2].second;
    int x = new_nd(val, id); tr[x].p = p;
    tr[x].l = build_val(l, mid - 1, x, v);
    tr[x].r = build_val(mid + 1, r, x, v);
    update(x); return x;
  }
  // (val, id) 사전순 정렬된 v(0-idx)로 트리 생성
  void init_val(const vector<pair<ll,int>> &v = {}) {
    clear(); rt = build_val(1, sz(v)+2, 0, v);
  }
  // (val, id) >= (s, id) 인 첫 노드를 tg 아래로 splay
  int lower_bound(ll s, int id = -1, int tg = 0) {
    int cur = rt, ret = 0;
    while (cur) { push(cur);
      if (tie(tr[cur].val, tr[cur].id) >= tie(s, id)) {
        ret = cur; cur = tr[cur].l;
      }
      else cur = tr[cur].r;
    }
    if (ret) splay(ret, tg);
    return ret;
  }
  // (val, id) < (s, id) 인 마지막 노드를 tg 아래로 splay
  int prev_bound(ll s, int id = -1, int tg = 0) {
    int cur = rt, ret = 0;
    while (cur) { push(cur);
      if (tie(tr[cur].val, tr[cur].id) < tie(s, id)) {
        ret = cur; cur = tr[cur].r;
      }
      else cur = tr[cur].l;
    }
    if (ret) splay(ret, tg);
    return ret;
  }
  // 값 [ (s1,id1), (s2,id2) ) 구간을 모음 (루트 반환)
  int gather_val(ll s1, ll s2, int id1 = -1, int id2 = -1) {
    int r = lower_bound(s2, id2), l = prev_bound(s1, id1, r);
    return tr[l].r;
  }
  // (v, id)값 노드 정렬 위치에 삽입
  void insert_val(ll v, int id = -1) {
    int r = lower_bound(v, id), l = prev_bound(v, id, r);
    int x = new_nd(v, id); tr[l].r = x; tr[x].p = l;
    update(l); update(r); splay(x);
  }
  void erase_val(ll v, int id = -1) { // (v, id)값 노드 제거
    int r = lower_bound(v, id+1), l = prev_bound(v, id, r);
    tr[l].r = 0; update(l); update(r); splay(l);
  }
  // === Link-Cut tree ===
  // 루트~x 경로를 단일 Splay로 연결
  void access(int x) {
    for (int y = 0; x; y = x, x = tr[x].p) {
      splay(x); tr[x].r = y; update(x);
    }
  }
  void make_rt(int x) { access(x); splay(x); tr[x].flip ^= 1; }
  int find_rt(int x) {
    access(x); splay(x);
    while (push(x), tr[x].l) x = tr[x].l;
    splay(x); return x;
  }
  bool conn(int u, int v) { return find_rt(u) == find_rt(v); }
  // link/cur: 간선 (u, v) 추가/제거 (성공 시 true)
  bool link(int u, int v) {
    if (conn(u, v)) return false;
    make_rt(u); tr[u].p = v; return true;
  }
  bool cut(int u, int v) {
    make_rt(u);
    if (find_rt(v) == u && tr[v].p == u && !tr[v].l) {
      tr[v].p = tr[u].r = 0;
      update(u); return true;
    }
    return false;
  }
  void cut(int x) { // x와 부모 노드 간선 제거
    access(x); splay(x);
    if (tr[x].l) {
      tr[tr[x].l].p = 0; tr[x].l = 0; update(x);
    }
  }
  int lca(int u, int v) {
    if (!conn(u, v)) return 0;
    access(u); access(v); splay(u);
    return tr[u].p ? tr[u].p : u;
  }
  // path_xxx: u, v가 연결되어 있을 때만 호출 가능
  Node path_qry(int u, int v) {
    make_rt(u); access(v); splay(v);
    return tr[v];
  }
  void path_upd(int u, int v, ll val) {
    make_rt(u); access(v); splay(v);
    apply(v, val);
  }
};