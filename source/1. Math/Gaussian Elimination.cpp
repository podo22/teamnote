// modinv
struct Gauss {
  using Mat = vector<vector<ll>>;
  const ll M = 1000000007;
  // 앞 cols개 열을 소거. 반환: {rank, 정사각 계수행렬의 det}.
  // full=true: RREF, false: 전진 소거. 계수는 [0,M).
  pair<int,ll> elim(Mat& a, int cols, bool full = true) {
    int n = sz(a), m = n ? sz(a[0]) : 0, r = 0;
    ll det = 1;
    for (int c = 0; c < cols && r < n; c++) {
      int p = r;
      while (p < n && a[p][c] == 0) p++;
      if (p == n) continue;
      if (p != r) { swap(a[p], a[r]); det = (M-det)%M; }
      det = det*a[r][c]%M;
      ll v = modinv(a[r][c], M);
      for (int j = c; j < m; j++) a[r][j] = a[r][j]*v%M;
      for (int i = full ? 0 : r+1; i < n; i++) {
        if (i == r || a[i][c] == 0) continue;
        ll f = a[i][c];
        for (int j = c; j < m; j++)
          a[i][j] = (a[i][j]-f*a[r][j]%M+M)%M;
      }
      r++;
    }
    return {r, r == cols ? det : 0};
  }
  // a: n*n, b: 우변 행렬. false면 a가 특이행렬.
  bool rref(Mat& a, Mat& b, int n) {
    for (int i = 0; i < n; i++)
      a[i].insert(a[i].end(), all(b[i]));
    bool ok = elim(a, n).first == n;
    for (int i = 0; i < n; i++) {
      b[i].assign(a[i].begin()+n, a[i].end());
      a[i].resize(n);
    }
    return ok;
  }
  // n*(n+1) 확대행렬. 유일해가 없으면 {}.
  vector<ll> solve(Mat a) {
    int n = sz(a);
    if (elim(a, n).first != n) return {};
    vector<ll> x(n);
    for (int i = 0; i < n; i++) x[i] = a[i][n];
    return x;
  }
  // 정사각행렬의 역행렬. 없으면 {}.
  Mat inverse(Mat a) {
    int n = sz(a);
    for (int i = 0; i < n; i++) {
      a[i].resize(2*n); a[i][n+i] = 1;
    }
    if (elim(a, n).first != n) return {};
    for (auto& row : a) row.erase(row.begin(), row.begin()+n);
    return a;
  }
  ll det(Mat a) { return elim(a, sz(a), false).second; }
  int rank(Mat a) {
    return elim(a, a.empty() ? 0 : sz(a[0]), false).first;
  }
};