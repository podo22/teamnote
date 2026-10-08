// 정점 1-based, 시간 0-based.
struct ODC {
  int q, comp; vector<int> p;
  vector<pair<int,int>> hist;
  vector<vector<pair<int,int>>> seg;
  ODC(int n, int q) : q(q), comp(n), p(n+1, -1), seg(4*q+5) {}
  int find(int x) { return p[x] < 0 ? x : find(p[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  int size(int x) { return -p[find(x)]; }
  void merge(int x, int y) {
    x = find(x); y = find(y);
    if (x == y) return;
    if (p[x] > p[y]) swap(x, y);
    hist.push_back({ y, p[y] });
    p[x] += p[y]; p[y] = x; comp--;
  }
  void rollback(int t) {
    while (sz(hist) > t) {
      auto [y, v] = hist.back(); hist.pop_back();
      p[p[y]] -= v; p[y] = v; comp++;
    }
  }
  void add(int nd, int s, int e, int l, int r, int u, int v) {
    if (r <= s || e <= l) return;
    if (l <= s && e <= r) return void(seg[nd].push_back({ u, v }));
    int m = (s+e)>>1;
    add(nd<<1, s, m, l, r, u, v);
    add(nd<<1|1, m, e, l, r, u, v);
  }
  void add(int l, int r, int u, int v) { // [l,r) 동안 존재하는 간선
    if (l < r) add(1, 0, q, l, r, u, v);
  }
  void dfs(int nd, int s, int e, auto &query) {
    int t = sz(hist);
    for (auto [u, v] : seg[nd]) merge(u, v);
    if (e-s == 1) query(s);
    else {
      int m = (s+e)>>1;
      dfs(nd<<1, s, m, query); dfs(nd<<1|1, m, e, query);
    }
    rollback(t);
  }
  // 각 시각 t에서 query(t) 호출
  void solve(auto query) { if (q) dfs(1, 0, q, query); }
};
ODC dc(3, 5);
dc.add(0, 3, 1, 2); dc.add(1, 5, 2, 3);
dc.solve([&](int t) {
  if (t==2 || t==4) cout << dc.same(1, 3);
}); // 출력: 1, 0