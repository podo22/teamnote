const ll INF = 1e18;
struct Dinic {
  struct Edge { int to; ll cap; int rev; };
  vector<vector<Edge>> graph;
  vector<int> level, work; int n;
  Dinic(int n) : n(n), graph(n+1), level(n+1), work(n+1) {}
  void add(int u, int v, ll cap) {
    graph[u].push_back({ v, cap, sz(graph[v])});
    graph[v].push_back({ u, 0, sz(graph[u])-1});
  }
  bool bfs(int s, int t) {
    fill(all(level), -1); level[s] = 0;
    queue<int> q; q.push(s);
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (auto [nxt, cap, rev] : graph[cur]) {
        if (cap > 0 && level[nxt] == -1) {
          level[nxt] = level[cur]+1;
          q.push(nxt);
        }
      }
    }
    return (level[t] != -1);
  }
  ll dfs(int cur, int t, ll flow) {
    if (cur == t) return flow;
    for (int& i = work[cur]; i < sz(graph[cur]); i++) {
      auto& [nxt, cap, rev] = graph[cur][i];
      if (cap > 0 && level[nxt] == level[cur]+1) {
        ll push = dfs(nxt, t, min(flow, cap));
        if (push > 0) {
          cap -= push; graph[nxt][rev].cap += push;
          return push;
        }
      }
    }
    return 0;
  }
  ll flow(int s, int t) {
    ll ans = 0;
    while (bfs(s, t)) {
      fill(all(work), 0);
      while (auto flow = dfs(s, t, INF)) ans += flow;
    }
    return ans;
  }
  vector<bool> mincut(int s) {
    vector<bool> vis(n+1); vis[s] = true;
    queue<int> q; q.push(s);
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      for (auto [nxt, cap, rev] : graph[cur]) {
        if (cap > 0 && !vis[nxt]) {
          vis[nxt] = true; q.push(nxt);
        }
      }
    }
    return vis;
  }
};