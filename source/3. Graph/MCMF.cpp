/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/14424
 */
template<typename T = ll>
struct MCMF {
  struct Edge { int to, rev; ll cap; T cost; };
  const T INF = 1e18, EPS = 1e-9;
  vector<vector<Edge>> graph; vector<T> dist;
  vector<int> ptr; vector<bool> vis; int n;
  MCMF(int n) : n(n), graph(n+1), dist(n+1), ptr(n+1), vis(n+1) {}
  void add(int u, int v, ll cap, T cost) {
    graph[u].push_back({ v, sz(graph[v]), cap, cost });
    graph[v].push_back({ u, sz(graph[u])-1, 0, -cost });
  }
  bool spfa(int s, int t) {
    fill(all(dist), INF); fill(all(vis), 0);
    deque<int> q; q.push_back(s); dist[s] = 0; vis[s] = 1;
    while (!q.empty()) {
      if (dist[q.front()] > dist[q.back()]) swap(q.front(), q.back());
      int cur = q.front(); q.pop_front(); vis[cur] = 0;
      for (auto& [nxt, rev, cap, cost] : graph[cur]) {
        if (cap > 0 && dist[nxt] > dist[cur] + cost + EPS) {
          dist[nxt] = dist[cur] + cost;
          if (!vis[nxt]) {
            vis[nxt] = 1;
            if (!q.empty() && dist[nxt] < dist[q.front()]) q.push_front(nxt);
            else q.push_back(nxt);
          }
        }
      }
    }
    return dist[t] < INF;
  }
  ll dfs(int cur, int t, ll flow, T& cost) {
    if (cur == t) return flow;
    vis[cur] = 1;
    for (int& i = ptr[cur]; i < sz(graph[cur]); i++) {
      auto& [nxt, rev, cap, cst] = graph[cur][i];
      if (!vis[nxt] && cap > 0 && abs(dist[nxt] - (dist[cur] + cst)) <= EPS) {
        ll push = dfs(nxt, t, min(flow, cap), cost);
        if (push > 0) {
          graph[nxt][rev].cap += push;
          cost += push * cst; cap -= push;
          vis[cur] = 0; return push;
        }
      }
    }
    return 0;
  }
  pair<ll,T> flow(int s, int t) {
    ll res = 0; T cost = 0;
    while (spfa(s, t)) {
      // if (dist[t] >= -EPS) break; // Min-Cost Flow
      fill(all(ptr), 0); fill(all(vis), 0);
      while (1) {
        ll push = dfs(s, t, 1e18, cost);
        if (push == 0) break;
        res += push;
      }
    }
    return { res, cost };
  }
};