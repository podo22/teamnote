// 쿼리마다 주어진 K개 정점 사이의 거리 합·최소 연결 서브트리·트리 DP 등.
// 전체 트리 대신 선택 정점과 필요한 LCA만 남겨 O(K)개 정점에서 처리.
// HLD 의존. 하나의 트리에서 hld.build() 이후 사용.
// nodes: 선택 정점 + 필요한 LCA, DFS 순서.
// edges: {부모, 자식}, 원래 정점 번호.
// build(): 가상 트리 루트 반환. 빈 집합이면 -1.
struct VirtualTree {
  vector<int> nodes;
  vector<pair<int,int>> edges;
  int build(vector<int> v, auto& hld) {
    nodes.clear(); edges.clear();
    if (v.empty()) return -1;
    auto cmp = [&](int a, int b) { return hld.in[a] < hld.in[b]; };
    sort(all(v), cmp); v.erase(unique(all(v)), v.end());
    int k = sz(v);
    for (int i = 1; i < k; i++) v.push_back(hld.lca(v[i-1], v[i]));
    sort(all(v), cmp); v.erase(unique(all(v)), v.end());
    nodes = v; vector<int> st;
    for (int u : nodes) {
      while (!st.empty() && !(hld.in[st.back()] <= hld.in[u] && hld.in[u] < hld.in[st.back()] + hld.siz[st.back()])) st.pop_back();
      if (!st.empty()) edges.push_back({ st.back(), u });
      st.push_back(u);
    }
    return nodes[0];
  }
};
VirtualTree vt;
int root = vt.build(v, hld); // v: 선택한 정점 목록
for (auto [p, u] : vt.edges) {
  int len = hld.dep[u] - hld.dep[p]; // 압축된 경로의 간선 수
  // p -> u 처리
}