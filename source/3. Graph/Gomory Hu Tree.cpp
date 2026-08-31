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
// ex. 인접정점간 최대유량 합이 최대인 순열
vector<int> par(n+1); iota(all(par), 0);
vector<vector<int>> p(n+1);
for (int i = 1; i <= n; i++) p[i] = {i};
function<int(int)> find = [&](int x) { return x == par[x] ? x : par[x] = find(par[x]); };
auto res = gomory_hu(n, edges);
sort(all(res), [](Edge& a, Edge& b) { return a.w > b.w; });
ll ans = 0;
for (auto &e : res) {
  int u = find(e.u), v = find(e.v);
  if (u == v) continue;
  ans += e.w; par[u] = v;
  p[v].insert(p[v].end(), all(p[u]));
}
// ans: 최대 유량의 합
// p[find(1)]: 조건을 만족하는 정점들의 순열 (크기 n)