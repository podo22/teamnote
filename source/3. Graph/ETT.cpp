/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct EulerTour {
  vector<vector<int>> adj; int n, pv = 0;
  vector<int> in, out, rev, dep;
  EulerTour(int n) : n(n), adj(n+1), in(n+1), out(n+1), rev(n+1), dep(n+1) {}
  void add(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
  void dfs(int u, int p = 0, int d = 0) {
    in[u] = ++pv; rev[pv] = u; dep[u] = d;
    for (auto v : adj[u]) if (v != p) dfs(v, u, d+1);
    out[u] = pv;
  }
  bool chk(int u, int v) { // u가 v의 조상(또는 본인)인지 판별
    return in[u] <= in[v] && out[v] <= out[u];
  }
  int size(int u) { return out[u]-in[u]+1; }
};
// EulerTour et(N); et.dfs(root); / u의 서브트리 : [in[u], out[u]]