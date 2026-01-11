const ll INF = 1e18;
struct HLPP {
  struct Edge {
    int to; ll cap; int rev;
  };
  vector<vector<Edge>> graph;
  vector<ll> ex;
  vector<int> level, work;
  vector<vector<int>> B;
  int n, high = 0, cnt = 0;
  HLPP(int n) : n(n+1), graph(n+1), level(n+1), work(n+1), ex(n+1), B(n+1) {}
  void add(int u, int v, ll cap) {
    graph[u].push_back({ v, cap, sz(graph[v]) });
    graph[v].push_back({ u, cap, sz(graph[u])-1 });
  }
  void push(int u) {
    if (level[u] >= n) return;
    B[level[u]].push_back(u);
    high = max(high, level[u]);
  }
  void relabel(int t) {
    cnt = 0;
    for (auto& b : B) b.clear();
    fill(all(level), n);
    queue<int> q; q.push(t);
    level[t] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      int h = level[u] + 1;
      for (auto& e : graph[u]) {
        if (graph[e.to][e.rev].cap > 0 && h < level[e.to]) {
          level[e.to] = h; q.push(e.to);
          if (ex[e.to] > 0) push(e.to);
        }
      }
    }
  }
  void discharge(int u) {
    auto& excess = ex[u];
    int h = n * 2, sz = sz(graph[u]);
    for (int& i = work[u], m = sz; m--; i = (i-1 + sz) % sz) {
      auto& e = graph[u][i];
      if (!e.cap) continue;
      if (level[u] != level[e.to] + 1) {
        h = min(h, level[e.to] + 1);
        continue;
      }
      auto f = min(e.cap, excess);
      e.cap -= f;
      excess -= f;
      if (!ex[e.to]) push(e.to);
      ex[e.to] += f;
      graph[e.to][e.rev].cap += f;
      if (!excess) return;
    }
    cnt++; level[u] = h;
    if (level[u] < n && ex[u] > 0) push(u);
  }
  ll flow(int s, int t) {
    relabel(t);
    ex[s] = INF; ex[t] = -INF;
    push(s);
    for (; ~high; high--) {
      while (!B[high].empty()) {
        int u = B[high].back();
        B[high].pop_back();
        if (level[u] == high) discharge(u);
        if (cnt > n/8) relabel(t);
      }
    }
    return ex[t] + INF;
  }
};