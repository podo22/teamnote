/**
 * [Metadata]
 * 
 * [Tested on]
 * 
 */
// 무방향 그래프, 정점 1-based. 중복 간선 허용, self-loop 제외.
// 정점 BCC: 단절점은 여러 성분에 속할 수 있음.
// build: O(V+E). 간선 추가 후 재호출 가능.
struct BCC {
  int n, t = 0, cnt = 0;
  vector<vector<int>> adj, bcc; // bcc[u]: u가 속한 성분 번호들
  vector<int> in, low, par, st;
  vector<char> cut; // cut[u]: 단절점 여부
  vector<pair<int,int>> bridge;
  BCC(int n) : n(n), adj(n+1), bcc(n+1), in(n+1),
    low(n+1), par(n+1), cut(n+1) {}
  void add(int u, int v) {
    adj[u].push_back(v); adj[v].push_back(u);
  }
  void dfs(int u, int p) {
    in[u] = low[u] = ++t; par[u] = p; st.push_back(u);
    int ch = 0; bool skip = false;
    for (int v : adj[u]) {
      // 부모 간선은 하나만 제외. 나머지 중복 간선은 역방향 간선.
      if (v == p && !skip) { skip = true; continue; }
      if (!in[v]) {
        ch++; dfs(v, u); low[u] = min(low[u], low[v]);
        if (low[v] >= in[u]) {
          if (p) cut[u] = 1;
          while (1) {
            int x = st.back(); st.pop_back();
            bcc[x].push_back(cnt);
            if (x == v) break;
          }
          bcc[u].push_back(cnt++);
        }
        if (low[v] > in[u])
          bridge.emplace_back(min(u,v), max(u,v));
      } else low[u] = min(low[u], in[v]);
    }
    if (!p) cut[u] = ch > 1;
  }
  // 단절점·브리지·BCC 소속 계산. 다른 조회 전에 호출.
  // 성분 번호 [0,cnt-1]. 고립 정점도 성분 하나로 처리.
  void build() {
    t = cnt = 0; st.clear(); bridge.clear();
    fill(all(in), 0); fill(all(cut), 0);
    for (auto& v : bcc) v.clear();
    for (int u = 1; u <= n; u++) if (!in[u]) {
      dfs(u, 0); st.pop_back();
      if (adj[u].empty()) bcc[u].push_back(cnt++);
    }
  }
  // 제거하면 연결 성분 수가 증가하는 정점들. O(V).
  vector<int> cutVertex() const {
    vector<int> res;
    for (int u = 1; u <= n; u++) if (cut[u]) res.push_back(u);
    return res;
  }
  // 제거하면 연결 성분 수가 증가하는 간선들. 순서는 미정렬.
  vector<pair<int,int>> cutEdge() const { return bridge; }
  // 정점 제거·단절점 경유 문제를 트리 경로 문제로 변환.
  // 원래 정점 [1,n], 성분 c의 정점 번호 n+c+1.
  // 비단절점도 유지하며, 원본이 비연결이면 forest.
  vector<vector<int>> block_cut() const {
    vector<vector<int>> g(n+cnt+1);
    for (int u = 1; u <= n; u++) for (int c : bcc[u]) {
      g[u].push_back(n+c+1); g[n+c+1].push_back(u);
    }
    return g;
  }
};