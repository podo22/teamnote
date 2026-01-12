/**
 * [Metadata]
 * Reference : https://koosaga.com/258
 * Implemented by : alreadysolved
 * [Verification]
 * Solved : https://www.acmicpc.net/problem/15741
 */
const ll INF = 1e18;
struct WeightedGeneralMatch {
  struct Edge { int u = 0, v = 0; ll w = 0; };
  int n, nx;
  vector<vector<Edge>> adj; vector<ll> label;
  vector<int> matched, slack, root, parent, state, vis;
  vector<vector<int>> node, via;
  queue<int> q; int time = 0;
  WeightedGeneralMatch(int n) : n(n), nx(n) {
    int size = 2*n+1;
    auto init = [&](auto&... vecs) { (vecs.resize(size), ...); };
    init(label, matched, slack, root, parent, state, vis, node);
    adj.resize(size, vector<Edge>(size));
    via.resize(size, vector<int>(n+1));
    for (int u = 1; u <= n; u++)
      for (int v = 1; v <= n; v++)
        adj[u][v] = { u, v, 0 };
  }
  void add(int u, int v, ll w) { adj[u][v].w = adj[v][u].w = w; }
  ll calc(Edge e) { return label[e.u] + label[e.v] - adj[e.u][e.v].w * 2; }
  void minSlack(int u, int x) {
    if (!slack[x] || calc(adj[u][x]) < calc(adj[slack[x]][x]))
      slack[x] = u;
  }
  void updSlack(int x) {
    slack[x] = 0;
    for (int u = 1; u <= n; u++) {
      if (adj[u][x].w > 0 && root[u] != x && state[root[u]] == 0) {
        minSlack(u, x);
      }
    }
  }
  void updRoot(int x, int b) {
    root[x] = b;
    if (x > n) for (auto i : node[x]) updRoot(i, b);
  }
  void enqueue(int x) {
    if (x <= n) q.push(x);
    else for (auto i : node[x]) enqueue(i);
  }
  int getIdx(int b, int xr) {
    int idx = find(all(node[b]), xr) - node[b].begin();
    if (idx % 2 == 1) {
      reverse(node[b].begin() + 1, node[b].end());
      return sz(node[b]) - idx;
    }
    return idx;
  }
  void rematch(int u, int v) {
    matched[u] = adj[u][v].v;
    if (u <= n) return;
    Edge e = adj[u][v];
    int xr = via[u][e.u], pr = getIdx(u, xr);
    for (int i = 0; i < pr; i++)
      rematch(node[u][i], node[u][i ^ 1]);
    rematch(xr, v);
    rotate(node[u].begin(), node[u].begin() + pr, node[u].end());
  }
  void augment(int u, int v) {
    while (true) {
      int xnv = root[matched[u]];
      rematch(u, v);
      if (!xnv) return;
      rematch(xnv, root[parent[xnv]]);
      u = root[parent[xnv]]; v = xnv;
    }
  }
  int findLCA(int u, int v) {
    time++;
    while (u || v) {
      if (u == 0) { swap(u, v); continue; }
      if (vis[u] == time) return u;
      vis[u] = time; u = root[matched[u]];
      if (u) u = root[parent[u]];
      swap(u, v);
    }
    return 0;
  }
  void addBlossom(int u, int lca, int v) {
    int b = n+1;
    while (b <= nx && root[b]) b++;
    if (b > nx) nx++;
    label[b] = 0, state[b] = 0;
    matched[b] = matched[lca];
    node[b].clear(); node[b].push_back(lca);
    for (int x = u, y; x != lca; x = root[parent[y]]) {
      node[b].push_back(x), node[b].push_back(y = root[matched[x]]);
      enqueue(y);
    }
    reverse(node[b].begin() + 1, node[b].end());
    for (int x = v, y; x != lca; x = root[parent[y]]) {
      node[b].push_back(x), node[b].push_back(y = root[matched[x]]);
      enqueue(y);
    }
    updRoot(b, b);
    for (int x = 1; x <= nx; x++)
      adj[b][x].w = adj[x][b].w = 0;
    for (int x = 1; x <= n; x++) via[b][x] = 0;
    for (int xs : node[b]) {
      for (int x = 1; x <= nx; x++) {
        if (adj[b][x].w == 0 || calc(adj[xs][x]) < calc(adj[b][x])) {
          adj[b][x] = adj[xs][x];
          adj[x][b] = adj[x][xs];
        }
      }
      for (int x = 1; x <= n; x++)
        if (via[xs][x])
          via[b][x] = xs;
    }
    updSlack(b);
  }
  void expandBlossom(int b) {
    for (auto i : node[b]) updRoot(i, i);
    int xr = via[b][adj[b][parent[b]].u], pr = getIdx(b, xr);
    for (int i = 0; i < pr; i+=2) {
      int xs = node[b][i], xns = node[b][i + 1];
      parent[xs] = adj[xns][xs].u;
      state[xs] = 1; state[xns] = slack[xs] = 0;
      updSlack(xns); enqueue(xns);
    }
    state[xr] = 1; parent[xr] = parent[b];
    for (int i = pr+1; i < sz(node[b]); i++) {
      int xs = node[b][i];
      state[xs] = -1; updSlack(xs);
    }
    root[b] = 0;
  }
  bool inspect(Edge e) {
    int u = root[e.u], v = root[e.v];
    if (state[v] == -1) {
      parent[v] = e.u; state[v] = 1;
      int nu = root[matched[v]];
      slack[v] = slack[nu] = 0;
      state[nu] = 0; enqueue(nu);
    }
    else if (state[v] == 0) {
      int lca = findLCA(u, v);
      if (!lca) {
        augment(u, v); augment(v, u);
        return true;
      }
      else addBlossom(u, lca, v);
    }
    return false;
  }
  bool matching() {
    fill(state.begin(), state.begin() + nx + 1, -1);
    fill(slack.begin(), slack.begin() + nx + 1, 0);
    q = queue<int>();
    for (int x = 1; x <= nx; x++) {
      if (root[x] == x && !matched[x]) {
        parent[x] = 0; state[x] = 0;
        enqueue(x);
      }
    }
    if (q.empty()) return false;
    while (true) {
      while (!q.empty()) {
        int u = q.front(); q.pop();
        if (state[root[u]] == 1) continue;
        for (int v = 1; v <= n; v++) {
          if (adj[u][v].w > 0 && root[u] != root[v]) {
            if (calc(adj[u][v]) == 0) {
              if (inspect(adj[u][v])) return true;
            }
            else minSlack(u, root[v]);
          }
        }
      }
      ll d = INF;
      for (int b = n+1; b <= nx; b++) {
        if (root[b] == b && state[b] == 1) {
          d = min(d, label[b] / 2);
        }
      }
      for (int x = 1; x <= nx; x++) {
        if (root[x] == x && slack[x]) {
          if (state[x] == -1) d = min(d, calc(adj[slack[x]][x]));
          else if (state[x] == 0) d = min(d, calc(adj[slack[x]][x]) / 2);
        }
      }
      for (int u = 1; u <= n; u++) {
        if (state[root[u]] == 0) {
          if (label[u] <= d) return false;
          label[u] -= d;
        }
        else if (state[root[u]] == 1) label[u] += d;
      }
      for (int b = n + 1; b <= nx; b++) {
        if (root[b] == b) {
          if (state[root[b]] == 0) label[b] += d * 2;
          else if (state[root[b]] == 1) label[b] -= d * 2;
        }
      }
      q = queue<int>();
      for (int x = 1; x <= nx; x++) {
        if (root[x] == x && slack[x] && root[slack[x]] != x && calc(adj[slack[x]][x]) == 0) {
          if (inspect(adj[slack[x]][x])) return true;
        }
      }
      for (int b = n + 1; b <= nx; b++) {
        if (root[b] == b && state[b] == 1 && label[b] == 0) expandBlossom(b);
      }
    }
    return false;
  }
  pair<ll,int> match() {
    fill(matched.begin(), matched.begin() + n+1, 0);
    nx = n;
    ll cost = 0; int res = 0;
    for (int u = 0; u <= n; u++) {
      root[u] = u;
      node[u].clear();
    }
    ll maxw = 0;
    for (int u = 1; u <= n; u++) {
      for (int v = 1; v <= n; v++) {
        via[u][v] = (u == v ? u : 0);
        maxw = max(maxw, adj[u][v].w);
      }
    }
    for (int u = 1; u <= n; u++) label[u] = maxw;
    while (matching()) res++;
    for (int u = 1; u <= n; u++) {
      if (matched[u] && matched[u] < u) {
        cost += adj[u][matched[u]].w;
      }
    }
    return { cost, res };
  }
};