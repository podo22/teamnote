// 모든 간선을 한 번씩 사용하는 경로·사이클 복원. 정점 1-based.
// 무방향: 홀수 차수 2개면 그중 하나, 0개면 간선 있는 정점에서 시작.
// 방향: out-in이 +1,-1인 정점 각각 1개, 나머지 0이면 +1에서 시작.
//       모두 0이면 나가는 간선 있는 정점에서 시작. 그 외는 불가능.
// path(s): 정점 방문 순서. 미방문 간선이 남으면 {}. adj는 소모됨.
struct Euler {
  int m = 0; bool dir;
  vector<vector<pair<int,int>>> adj;
  Euler(int n, bool dir = false) : dir(dir), adj(n+1) {}
  void add(int u, int v) {
    adj[u].push_back({ v, m });
    if (!dir) adj[v].push_back({ u, m });
    m++;
  }
  vector<int> path(int s) {
    vector<int> st{s}, res;
    vector<bool> used(m);
    while (!st.empty()) {
      int u = st.back();
      if (adj[u].empty()) res.push_back(u), st.pop_back();
      else {
        auto [v, id] = adj[u].back(); adj[u].pop_back();
        if (!used[id]) used[id] = true, st.push_back(v);
      }
    }
    if (sz(res) != m+1) return {};
    reverse(all(res)); return res;
  }
};