ll modpow(ll b, ll e);
ll modinv(ll a, ll m);
struct Gauss {
  const ll M = 1000000007;
  // return: 소거 성공 여부(false면 역행렬/해 없음)
  bool rref(vector<vector<ll>> &a, vector<vector<ll>> &b, int n) {
    for (int c = 0; c < n; c++) {
      int piv = c;
      while (piv < n && a[piv][c] == 0) piv++;
      if (piv == n) return false;
      swap(a[c], a[piv]); swap(b[c], b[piv]);
      ll d = modinv(a[c][c]);
      for (int j = c; j < n; j++) a[c][j] = a[c][j] * d % M;
      for (int j = 0; j < sz(b[c]); j++) b[c][j] = b[c][j] * d % M;
      for (int i = 0; i < n; i++) if (i != c) {
        ll f = a[i][c];
        if (f == 0) continue;
        for (int j = c; j < n; j++)
        a[i][j] = (a[i][j] - f * a[c][j] % M + M) % M;
        for (int j = 0; j < sz(b[i]); j++)
        b[i][j] = (b[i][j] - f * b[c][j] % M + M) % M;
      }
    }
    return true;
  }
  // Ax=b 해 (없으면 {})
  vector<ll> solve(vector<vector<ll>> a) {
    int n = sz(a);
    vector<vector<ll>> A(n, vector<ll>(n)), B(n, vector<ll>(1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) A[i][j] = a[i][j];
      B[i][0] = a[i][n];
    }
    if (!rref(A, B, n)) return {};
    vector<ll> x(n);
    for (int i = 0; i < n; i++) x[i] = B[i][0];
    return x;
  }
  // 역행렬 (없으면 {})
  vector<vector<ll>> inverse(vector<vector<ll>> a) {
    int n = sz(a);
    vector<vector<ll>> b(n, vector<ll>(n));
    for (int i = 0; i < n; i++) b[i][i] = 1;
    if (!rref(a, b, n)) return {};
    return b;
  }
  // 행렬식
  ll det(vector<vector<ll>> a) {
    int n = sz(a); ll res = 1;
    for (int c = 0; c < n; c++) {
      int piv = c;
      while (piv < n && a[piv][c] == 0) piv++;
      if (piv == n) return 0;
      if (piv != c) { swap(a[c], a[piv]); res = (M - res) % M; }
      res = res * a[c][c] % M;
      ll d = modinv(a[c][c]);
      for (int j = c; j < n; j++) a[c][j] = a[c][j] * d % M;
      for (int i = c + 1; i < n; i++) {
        ll f = a[i][c];
        if (f == 0) continue;
        for (int j = c; j < n; j++)
        a[i][j] = (a[i][j] - f * a[c][j] % M + M) % M;
      }
    }
    return res;
  }
  // rank
  int rank(vector<vector<ll>> a) {
    int n = sz(a), m = sz(a[0]), r = 0;
    for (int c = 0; c < m; c++) {
      int piv = r;
      while (piv < n && a[piv][c] == 0) piv++;
      if (piv == n) continue;
      swap(a[r], a[piv]);
      ll d = modinv(a[r][c]);
      for (int j = c; j < m; j++) a[r][j] = a[r][j] * d % M;
      for (int i = r + 1; i < n; i++) {
        ll f = a[i][c];
        if (f == 0) continue;
        for (int j = c; j < m; j++)
        a[i][j] = (a[i][j] - f * a[r][c] % M + M) % M;
      }
      r++;
    }
    return r;
  }
};