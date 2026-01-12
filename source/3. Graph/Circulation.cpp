/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/20135
 */
const ll INF = 1e18;
struct Dinic {}; // or MCMF
struct Circulation {
  vector<ll> demand, low;
  vector<pair<int,int>> edge;
  int n, S, T; Dinic dn;
  Circulation(int n) : n(n), S(n+1), T(n+2), demand(n+3, 0), dn(n+2) {};
  void add_demand(int u, ll d) { demand[u] += d; }
  int add(int u, int v, ll l, ll r) {
    demand[u] -= l; demand[v] += l;
    dn.add(u, v, r - l); low.push_back(l);
    edge.push_back({ u, sz(dn.graph[u])-1 });
    return sz(edge)-1;
  }
  ll solve() {
    ll sum = 0, res = 0;
    for (int i = 1; i <= n; i++) sum += demand[i];
    if (sum != 0) return false;
    for (int i = 1; i <= n; i++) {
      if (demand[i] > 0) {
        dn.add(S, i, demand[i]); res += demand[i];
      }
      else if (demand[i] < 0) dn.add(i, T, -demand[i]);
    }
    ll f = dn.flow(S, T);
    return (f != res ? -1 : f);
  }
  ll get_flow(int i) { // get actual flow
    auto [u, idx] = edge[i];
    int v = dn.graph[u][idx].to, rev = dn.graph[u][idx].rev;
    return dn.graph[v][rev].cap + low[i];
  }
};