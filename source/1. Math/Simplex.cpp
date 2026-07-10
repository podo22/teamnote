// cx 최대화, 조건: Ax <= b, x >= 0
// ret: max_val (해 없음: -inf, 무한 해: inf)
template<typename T> struct Simplex {
  int m, n; vector<int> B, N;
  vector<vector<T>> D;
  const T EPS = 1e-9, INF = 1e18;
  Simplex(int m, int n) : m(m), n(n), B(m), N(n+1), D(m+2, vector<T>(n+2)) {
    iota(all(N), 0); iota(all(B), n);
  }
  void pivot(int r, int s) {
    T inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; i++) if (i != r) {
      for (int j = 0; j < n + 2; j++) if (j != s) {
        D[i][j] -= D[r][j] * D[i][s] * inv;
      }
    }
    for (int j = 0; j < n + 2; j++) if (j != s) D[r][j] *= inv;
    for (int i = 0; i < m + 2; i++) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv; swap(B[r], N[s]);
  }
  bool simplex(int phase) {
    int x = (phase == 1 ? m+1 : m);
    while (1) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (phase == 2 && N[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s])) s = j;
      }
      if (D[x][s] > -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n+1] / D[i][s] < D[r][n+1] / D[r][s] || (D[i][n+1] / D[i][s] == D[r][n+1] / D[r][s] && B[i] < B[r])) r = i;
      }
      if (r == -1) return false;
      pivot(r, s);
    }
  }
  T solve(const vector<vector<T>> &A, const vector<T> &b, const vector<T> &c, vector<T> &x) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) D[i][j] = A[i][j];
      D[i][n] = -1; 
      D[i][n+1] = b[i];
    }
    for (int j = 0; j < n; j++) D[m][j] = -c[j];
    D[m+1][n] = 1;
    int r = 0;
    for (int i = 1; i < m; i++) if (D[i][n+1] < D[r][n+1]) r = i;
    if (D[r][n+1] < -EPS) {
      pivot(r, n);
      if (!simplex(1) || D[m+1][n+1] < -EPS) return -INF;
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; j++) 
          if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s])) s = j;
        pivot(i, s);
      }
    }
    if (!simplex(2)) return INF;
    x.assign(n, 0);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n+1];
    return D[m][n+1];
  }
};
// min은 c에 -1을 곱해 대입. 결과에 -1을 곱함
// a>=b -> -a<=-b / a==b -> a<=b, -a<=-b
int main() {
  // ex. 3x+2y 최대화, 조건: x+2y<=4, x+y<=3
  vector<vector<double>> A = {{1., 2.},{1., 1.}};
  vector<double> b = {4., 3.}, c = {3., 2.}, x;
  Simplex<double> sp(sz(A), sz(A[0]));
  double ans = sp.solve(A, b, c, x);
  if (ans == -sp.INF) {
    cout << "해 없음\n";
  } else if (ans == sp.INF) {
    cout << "무한 해\n";
  } else {
    cout << "최댓값: " << ans << "\n";
    cout << "x=" << x[0] << ", y=" << x[1] << "\n";
  }
  return 0;
}
