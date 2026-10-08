struct TreeIso {
  map<vector<int>,int> mp;
  int encode(const vector<vector<int>> &g, int root = 0) {
    int n = sz(g)-1;
    function<int(int,int)> dfs = [&](int u, int p) {
      vector<int> v;
      for (int x : g[u]) if (x != p) v.push_back(dfs(x, u));
      sort(all(v));
      return mp.emplace(v, sz(mp)+1).first->second;
    };
    if (root) return dfs(root, 0);
    vector<int> c;
    function<int(int,int)> cent = [&](int u, int p) {
      int s = 1, mx = 0;
      for (int x : g[u]) if (x != p) {
        int t = cent(x, u);
        s += t; mx = max(mx, t);
      }
      if (max(mx, n-s) <= n/2) c.push_back(u);
      return s;
    };
    cent(1, 0); int ret = 2e9;
    for (int x : c) ret = min(ret, dfs(x, 0));
    return ret;
  }
} ti;
// ti.encode(a) == ti.encode(b);
// ti.encode(a, ra) == ti.encode(b, rb); // 루트 지정