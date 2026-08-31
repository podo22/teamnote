/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/14216
 */
template<typename T = ll> struct Hungarian {
  vector<T> u, v, ans; vector<int> p, way;
  int n, m; const T INF = 1e15;
  Hungarian(int n, int m) : n(n), m(m), u(n+1), v(m+1), p(m+1), way(m+1) {}
  T solve (const vector<vector<T>> &a) {
    ans.clear();
    vector<T> mv(m+1); vector<bool> vis(m+1);
    for (int i = 1; i <= n; i++) {
      fill(all(mv), INF); fill(all(vis), false);
      p[0] = i; int j0 = 0;
      while (p[j0] != 0) {
        vis[j0] = true; T dt = INF;
        int i0 = p[j0], j1 = 0;
        for (int j = 1; j <= m; j++) {
          if (vis[j]) continue;
          T cur = a[i0][j] - u[i0] - v[j];
          if (cur < mv[j]) mv[j] = cur, way[j] = j0;
          if (mv[j] < dt) dt = mv[j], j1 = j;
        }
        for (int j = 0; j <= m; j++) {
          if (vis[j]) u[p[j]] += dt, v[j] -= dt;
          else mv[j] -= dt;
        }
        j0 = j1;
      }
      while (j0 != 0) {
        int j1 = way[j0];
        p[j0] = p[j1]; j0 = j1;
      }
      ans.push_back(-v[0]);
    }
    return sz(ans) ? ans.back() : 0;
  }
  T cost(int k) { return ans[k-1]; }
  vector<int> match() {
    vector<int> res(n+1);
    for (int i = 1; i <= m; i++) if (p[i]) res[p[i]] = i;
    return res;
  }
};