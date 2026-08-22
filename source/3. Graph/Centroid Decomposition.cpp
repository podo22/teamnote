/**
 * [Metadata]
 * Author : 
 * [Tested on]
 * 
 */
struct CentroidTree {
  vector<vector<int>> adj, c_adj; // adj: 원본트리 / c_adj: 센트로이드트리
  vector<int> sz, par, vis; int N;
  CentroidTree(int n) : N(n), adj(n+1), c_adj(n+1), sz(n+1), par(n+1), vis(n+1) {}
  void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
  int get_sz(int curr, int prev) {
    sz[curr] = 1;
    for (int next : adj[curr])
      if (next != prev && !vis[next]) sz[curr] += get_sz(next, curr);
    return sz[curr];
  }
  int get_cent(int curr, int prev, int to_sz) {
    for (int next : adj[curr])
      if (next != prev && !vis[next] && sz[next] > to_sz / 2)
        return get_cent(next, curr, to_sz);
    return curr;
  }
  void solve(int u) { 
    // * solve(u): 현재 centroid u를 지나는 모든 경로를 여기서 계산.
    //  - u에서 각 서브트리로 DFS하며 거리/조건 집계
    //  - 서로 다른 서브트리에서 오는 경로끼리 쌍을 만들 때 중복 주의
    // build(1) 호출하면 자동으로 centroid tree 완성.
  }
  int build(int curr, int p = -1) {
    int cent = get_cent(curr, -1, get_sz(curr, -1));
    solve(cent);
    vis[cent] = 1; par[cent] = p;
    for (int next : adj[cent]) {
      if (!vis[next]) {
        int child = build(next, cent);
        c_adj[cent].push_back(child); // 센트로이드 계층 연결
      }
    }
    return cent;
  }
};