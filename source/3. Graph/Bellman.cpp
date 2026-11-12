/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
auto bellman = [&](int s) -> bool {
  vector<tuple<int,ll,int>> edges;
  for (int u = 1; u <= n; u++) for (auto [w, v] : adj[u]) {
    edges.emplace_back(u, w, v);
  }
  fill(all(d), INF); d[s] = 0; bool chk = 0;
  for (int i = 0; i < n; i++) { chk = 0;
    for (auto [u, w, v] : edges) {
      if (d[u] != INF && d[v] > d[u] + w) {
        d[v] = d[u] + w; chk = 1; if (i == n - 1) return 0;
      }
    }
    if (!chk) break;
  }
  return 1;
};