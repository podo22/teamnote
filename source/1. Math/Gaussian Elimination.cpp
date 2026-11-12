// modinv
struct Gauss {
  using Mat = vector<vector<ll>>;
  const ll M = 1000000007;
  // a=[A|B]. 앞 cols열(A)에서 피벗을 찾아 B에도 행 연산. {rank(A), det(A): 정사각일 때}.
  // full=true: 피벗 위아래 소거, false: 아래만 소거. 원소는 [0,M).
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
  // AX=B. rank(A)<n이면 false, 성공하면 b=X.
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
  // [A|b]는 n*(n+1). Ax=b의 유일해 x를 반환, rank(A)<n이면 {}.
  vector<ll> solve(Mat a) {
    int n = sz(a);
    if (elim(a, n).first != n) return {};
    vector<ll> x(n);
    for (int i = 0; i < n; i++) x[i] = a[i][n];
    return x;
  }
  // n*n 행렬 A의 역행렬을 반환, rank(A)<n이면 {}.
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