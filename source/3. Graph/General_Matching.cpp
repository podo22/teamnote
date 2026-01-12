/**
 * [Metadata]
 * Reference : https://blog.kyouko.moe/20?category=767011
 * Implemented by : alreadysolved
 * [Verification]
 * Solved : https://www.acmicpc.net/problem/15737
 */
struct GeneralMatch {
  vector<vector<int>> graph;
  vector<int> vis, parent, orig, matched, aux;
  queue<int> q; int n, t = 0;
  GeneralMatch(int n) : n(n) {
    auto init = [&](auto&... vecs) { (vecs.resize(n+1), ...); };
    init(graph, vis, parent, orig, matched, aux);
  }
  void add(int a, int b) { graph[a].push_back(b); graph[b].push_back(a); }
  void augment(int u, int v) {
    while (v) {
      int pv = parent[v], nv = matched[pv];
      matched[v] = pv; matched[pv] = v;
      v = nv;
    }
  }
  int lca(int v, int w) {
    ++t;
    while (1) {
      if (v) {
        if (aux[v] == t) return v;
        aux[v] = t; v = orig[parent[matched[v]]];
      }
      swap(v, w);
    }
  }
  void blossom(int v, int w, int a) {
    while (orig[v] != a) {
      parent[v] = w; w = matched[v];
      if (vis[w] == 1) { q.push(w), vis[w] = 0; }
      orig[v] = orig[w] = a; v = parent[w];
    }
  }
  bool bfs(int u, int ban = 0) {
    fill(all(vis), -1); iota(all(orig), 0);
    if (ban) vis[ban] = 2;
    q = queue<int>(); q.push(u); vis[u] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto w : graph[v]) {
        if (vis[w] == -1) {
          parent[w] = v; vis[w] = 1;
          if (!matched[w]) { augment(u, w); return true; }
          vis[matched[w]] = 0; q.push(matched[w]);
        }
        else if (vis[w] == 0 && orig[v] != orig[w]) {
          int a = lca(orig[v], orig[w]);
          blossom(w, v, a); blossom(v, w, a);
        }
      }
    }
    return false;
  }
  int match() {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
      if(!matched[i] && bfs(i)) ans++;
    }
    return ans;
  }
  bool chk(int u) { // find max matching except u
    if (!matched[u]) return true;
    auto backup = matched;
    int v = matched[u];
    matched[u] = matched[v] = 0;
    bool res = bfs(v, u);
    matched = backup;
    return res;
  }
};