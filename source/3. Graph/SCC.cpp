/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 0-based. id는 역위상순: 서로 다른 SCC 사이의 u->v이면 id[u]>id[v].
struct SCC {
  int n, cnt = 0, t = 0;
  vector<vector<int>> adj;
  vector<int> dfn, low, id, st;
  SCC(int n) : n(n), adj(n), dfn(n), low(n), id(n) {}
  void add(int u, int v) { adj[u].push_back(v); }
  int add() { // 정점 추가, 새 정점 번호 반환
    adj.emplace_back(); dfn.emplace_back();
    low.emplace_back(); id.emplace_back(); return n++;
  }
  void dfs(int u) {
    dfn[u] = low[u] = t++; st.push_back(u);
    for (int v : adj[u]) {
      if (dfn[v] == -1) dfs(v), low[u] = min(low[u], low[v]);
      else if (id[v] == -1) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
      while (1) {
        int v = st.back(); st.pop_back(); id[v] = cnt;
        if (u == v) break;
      }
      cnt++;
    }
  }
  void build() { // 간선 추가 후 재호출 가능
    cnt = t = 0; st.clear();
    fill(all(dfn), -1); fill(all(id), -1);
    for (int i = 0; i < n; i++) if (dfn[i] == -1) dfs(i);
  }
};