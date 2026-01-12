/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/11408
 */
const ll INF = 1e18;
struct MCMF {
  struct Edge { int to; ll cap, cost; int rev; };
  vector<vector<Edge>> graph;
  vector<ll> dist;
  vector<int> parent, edge;
  vector<bool> vis;
  int n;
  MCMF(int n) : n(n), graph(n+1), dist(n+1), parent(n+1), edge(n+1), vis(n+1) {}
  void add(int u, int v, ll cap, ll cost) {
    graph[u].push_back({ v, cap, cost, sz(graph[v]) });
    graph[v].push_back({ u, 0, -cost, sz(graph[u])-1 });
  }
  bool spfa(int s, int t) {
    fill(all(dist), INF); fill(all(parent), -1); fill(all(vis), false);
    queue<int> q; q.push(s);
    dist[s] = 0; vis[s] = true;
    while (!q.empty()) {
      int cur = q.front(); q.pop();
      vis[cur] = false;
      for (int i = 0; i < sz(graph[cur]); i++) {
        auto& [nxt, cap, cost, rev] = graph[cur][i];
        if (cap > 0 && dist[nxt] > dist[cur] + cost) {
          dist[nxt] = dist[cur] + cost;
          parent[nxt] = cur; edge[nxt] = i;
          if (!vis[nxt]) {
            vis[nxt] = true; q.push(nxt);
          }
        }
      }
    }
    return dist[t] != INF;
  }
  pair<int,ll> flow(int s, int t) {
    int res = 0; ll cost = 0;
    while (spfa(s, t)) {
      ll fl = INF;
      for (int v = t; v != s; v = parent[v]) {
        int u = parent[v], idx = edge[v];
        fl = min(fl, graph[u][idx].cap);
      }
      for (int v = t; v != s; v = parent[v]) {
        int u = parent[v], idx = edge[v], ridx = graph[u][idx].rev;
        graph[u][idx].cap -= fl;
        graph[v][ridx].cap += fl;
        cost += (ll)fl * graph[u][idx].cost;
      }
      res += fl;
    }
    return { res, cost };
  }
};