/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct TwoSat { // 0-idx
  int n, t, cnt;
  vector<vector<int>> adj;
  vector<int> dfn, low, scc, st;
  vector<bool> ans;
  TwoSat(int n) : n(n), adj(2*n), dfn(2*n), low(2*n), scc(2*n) {}
  int I(int x) { return x^1; }
  void add_edge(int u, int v) { adj[u].push_back(v); adj[I(v)].push_back(I(u)); } // u->v
  void add_clause(int u, int v) { add_edge(I(u), v); }
  void add_clause(int u, bool ut, int v, bool vt) { add_clause(u*2 + !ut, v*2 + !vt); } // (u==ut) or (v==vt)
  int add() {
    auto New = [&](auto&... vs) { (vs.emplace_back(), ...); };
    for (int i = 0; i < 2; i++) New(adj, dfn, low, scc);
    return n++;
  }
  void most_one(const vector<int> &v, bool cd = true) {
    int pre = -1;
    for (auto i : v) {
      int x = i*2 + !cd, now = add()*2;
      add_edge(x, now);
      if (pre != -1) { add_edge(pre, now); add_edge(pre, I(x)); }
      pre = now;
    }
  }
  void dfs(int u) {
    dfn[u] = low[u] = ++t; st.push_back(u);
    for (auto v : adj[u]) {
      if (dfn[v] == -1) { dfs(v); low[u] = min(low[u], low[v]); }
      else if (scc[v] == -1) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
      while (1) {
        int v = st.back(); st.pop_back();
        scc[v] = cnt;
        if (u == v) break;
      }
      cnt++;
    }
  }
  bool solve() {
    t = cnt = 0; st.clear();
    fill(all(dfn), -1); fill(all(scc), -1);
    for (int i = 0; i < 2*n; i++) if (dfn[i] == -1) dfs(i);
    ans.resize(n);
    for (int i = 0; i < n; i++) {
      if (scc[i*2] == scc[i*2+1]) return false;
      ans[i] = scc[i*2] < scc[i*2+1];
    }
    return true;
  }
};