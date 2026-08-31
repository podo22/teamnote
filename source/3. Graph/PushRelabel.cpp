/**
 * [Metadata]
 * Reference : https://loj.ac/s/1500182
 * Implemented by : alreadysolved
 * [Verification]
 * https://loj.ac/p/127
 */
template<typename T = ll> struct HLPP {
  struct Edge { int to; T cap; int rev; };
  T INF = numeric_limits<T>::max();
  vector<vector<Edge>> adj;
  vector<T> ex;
  vector<int> pos, lvl, nxt, gprv, gnxt;
  int n, high = 0, gap = 0, cnt = 0;
  HLPP(int n) : n(n+1), adj(n+2), ex(n+2), pos(n+2), lvl(n+2), nxt(2*n+3), gprv(2*n+3), gnxt(2*n+3) {}
  void add(int u, int v, T cap) {
    adj[u].push_back({ v, cap, sz(adj[v]) });
    adj[v].push_back({ u, 0, sz(adj[u])-1 });
  }
  void push(int u, int h) {
    nxt[u] = nxt[n+h]; nxt[n+h] = u;
    high = max(high, h);
  }
  void ugap(int u, int h) {
    gnxt[u] = gnxt[gprv[u] = n+h];
    gprv[gnxt[u]] = gnxt[gprv[u]] = u;
    gap = max(gap, h);
  }
  void dgap(int u) {
    gnxt[gprv[u]] = gnxt[u];
    gprv[gnxt[u]] = gprv[u];
  }
  void addex(int u, T f) {
    ex[u] += f;
    if (ex[u] == f) push(u, lvl[u]);
  }
  void upd(int u, int h) {
    if (lvl[u] != n+1) dgap(u);
    lvl[u] = h; if (h == n+1) return;
    ugap(u, h); if (ex[u] > 0) push(u, h);
  }
  void relabel(int t) {
    cnt = high = gap = 0;
    iota(nxt.begin()+n, nxt.end(), n);
    iota(gprv.begin()+n, gprv.end(), n);
    iota(gnxt.begin()+n, gnxt.end(), n);
    fill(all(lvl), n+1); fill(all(pos), 0);
    lvl[t] = 0; queue<int> q; q.push(t);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (auto &e : adj[u]) {
        if (!adj[e.to][e.rev].cap || lvl[e.to] <= lvl[u]+1) continue;
        upd(e.to, lvl[u]+1); q.push(e.to);
      }
    }
  }
  void discharge(int u) {
    T &v = ex[u]; int h = n, Sz = sz(adj[u]);
    for (int &i = pos[u], k = Sz; k--; i = (i ? i : Sz)-1) {
      auto& e = adj[u][i];
      if (!e.cap) continue;
      if (lvl[u] != lvl[e.to]+1) {
        h = min(h, lvl[e.to]); continue;
      }
      auto f = min(v, e.cap);
      v -= f; addex(e.to, f); e.cap -= f;
      adj[e.to][e.rev].cap += f;
      if (!v) return;
    }
    cnt++;
    if (gnxt[gnxt[n+lvl[u]]] < n) {
      upd(u, h+1); return;
    }
    for (int i = lvl[u]; gap >= i; gap--) {
      while (gnxt[n+gap] < n) {
        int t = gnxt[n+gap];
        lvl[t] = n+1; dgap(t);
      }
    }
  }
  T flow(int s, int t) {
    relabel(t);
    addex(s, INF); ex[t] -= INF;
    while (~high) {
      int u = nxt[n+high];
      if (u >= n) { high--; continue; }
      nxt[n+high] = nxt[u];
      if (lvl[u] != high) continue;
      discharge(u);
      if (cnt >= 4*n) relabel(t);
    }
    return ex[t]+INF;
  }
};