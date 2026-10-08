// Gomory-Hu Tree: 모든 정점 쌍의 최대 유량(Min-cut)을 표현하는 트리
// 트리에서 u-v 경로 상의 최소 가중치 간선 = 원본 그래프에서 u-v의 최대 유량
struct Dinic {};
struct Edge { int u, v; ll w; };
vector<Edge> gomory_hu(int n, const vector<Edge> &ev) {
  vector<Edge> tree;
  vector<int> par(n+1, 1);
  for (int i = 2; i <= n; i++) {
    Dinic dn(n);
    for (auto& [u, v, w] : ev) { dn.add(u, v, w); dn.add(v, u, w); }
    tree.push_back({i, par[i], dn.flow(i, par[i])});
    vector<bool> cut = dn.mincut(i);
    for (int j = i + 1; j <= n; j++) {
      if (cut[j] && par[j] == par[i]) par[j] = i;
    }
  }
  return tree;
}
// 인접 정점 간 최대 유량 합이 최대인 순열
auto res = gomory_hu(n, edges);
sort(all(res), [](const Edge& a, const Edge& b) { return a.w > b.w; });
DSU uf(n); vector<vector<int>> p(n+1);
for (int i = 1; i <= n; i++) p[i] = {i};
ll ans = 0;
for (auto& e : res) {
  int u = uf.find(e.u), v = uf.find(e.v);
  if (!uf.merge(u, v)) continue;
  if (uf.find(u) == v) swap(u, v);
  p[u].insert(p[u].end(), all(p[v])); ans += e.w;
} // ans: 최대 합, p[uf.find(1)]: 해당 순열