/**
 * [Metadata]
 * Reference : https://blog.kyouko.moe/20?category=767011, https://t1.daumcdn.net/cfile/tistory/9916F74B5B4762BD26
 * Implemented by : alreadysolved
 * [Verification]
 * Solved : https://www.acmicpc.net/problem/15737
 */
struct GeneralMatch {
  vector<vector<int>> adj;
  vector<int> vis, par, ori, mat, aux;
  queue<int> q; int n, t = 0;
  GeneralMatch(int n) : n(n), adj(n+1), vis(n+1), par(n+1), ori(n+1), mat(n+1), aux(n+1) {}
  void add(int a, int b) { adj[a].push_back(b); adj[b].push_back(a); }
  void augment(int v) {
    while (v) {
      int pv = par[v], nv = mat[pv];
      mat[v] = pv; mat[pv] = v; v = nv;
    }
  }
  int lca(int v, int w) {
    ++t; while (1) {
      if (v) {
        if (aux[v] == t) return v;
        aux[v] = t; v = ori[par[mat[v]]];
      }
      swap(v, w);
    }
  }
  void blossom(int v, int w, int a) {
    while (ori[v] != a) {
      par[v] = w; w = mat[v];
      if (vis[w] == 1) q.push(w), vis[w] = 0;
      ori[v] = ori[w] = a; v = par[w];
    }
  }
  bool bfs(int u, int ban = 0) {
    fill(all(vis), -1); iota(all(ori), 0);
    if (ban) vis[ban] = 2;
    q = queue<int>(); q.push(u); vis[u] = 0;
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto w : adj[v]) {
        if (vis[w] == -1) {
          par[w] = v; vis[w] = 1;
          if (!mat[w]) { augment(w); return true; }
          vis[mat[w]] = 0; q.push(mat[w]);
        }
        else if (vis[w] == 0 && ori[v] != ori[w]) {
          int a = lca(ori[v], ori[w]);
          blossom(w, v, a); blossom(v, w, a);
        }
      }
    }
    return false;
  }
  int match() {
    int ans = 0; vector<int> v(n); iota(all(v), 1);
    shuffle(all(v), rng);
    for (auto x : v) if (!mat[x]) {
      for (auto y : adj[x]) if (!mat[y]) {
        mat[x] = y, mat[y] = x;
        ans++; break;
      }
    }
    for (int i = 1; i <= n; i++) {
      if (!mat[i] && bfs(i)) ans++;
    }
    return ans;
  }
  bool chk(int u) { // find max matching except u
    if (!mat[u]) return true;
    auto tmp = mat; int v = mat[u];
    mat[u] = mat[v] = 0;
    bool res = bfs(v, u); mat = tmp;
    return res;
  }
};