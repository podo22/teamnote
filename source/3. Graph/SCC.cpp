struct SCC {
  int n, cnt, timer;
  vector<vector<int>> adj;
  vector<int> dfn, low, id;
  vector<bool> ins; stack<int> st;
  SCC(int n) : n(n), adj(n), dfn(n, -1), low(n, -1), id(n, -1), ins(n), cnt(0), timer(0) {}
  void add_edge(int u, int v) { adj[u].push_back(v); }
  void dfs(int u) {
    dfn[u] = low[u] = ++timer;
    st.push(u); ins[u] = true;
    for (int v : adj[u]) {
      if (dfn[v] == -1) {
        dfs(v); low[u] = min(low[u], low[v]);
      } else if (ins[v]) {
        low[u] = min(low[u], dfn[v]);
      }
    }
    if (low[u] == dfn[u]) {
      while (true) {
        int v = st.top(); st.pop();
        ins[v] = false; id[v] = cnt;
        if (u == v) break;
      }
      cnt++;
    }
  }
  void build() {
    for (int i = 0; i < n; i++)
      if (dfn[i] == -1) dfs(i);
  }
};