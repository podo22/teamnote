// C[k] = sum_{i op j = k} A[i]*B[j]. op: '&', '|', '^'.
void fwht(vector<ll> &a, char op, bool inv = false) {
  const ll M = 998244353;
  int n = sz(a);
  for (int len = 1; len < n; len <<= 1) for (int i = 0; i < n; i += len*2) for (int j = 0; j < len; j++) {
    ll u = a[i+j], v = a[i+j+len];
    if (op == '|') a[i+j+len] = (v + (inv ? M-u : u))%M;
    else if (op == '&') a[i+j] = (u + (inv ? M-v : v))%M;
    else a[i+j] = (u+v)%M, a[i+j+len] = (u-v+M)%M;
  }
  if (inv && op == '^') {
    ll r = modpow(n, M-2, M);
    for (auto& x : a) x = x*r%M;
  }
} // 계수 [0,998244353)
vector<ll> bitconv(vector<ll> a, vector<ll> b, char op) {
  const ll M = 998244353;
  int n = 1;
  while (n < max(sz(a), sz(b))) n <<= 1;
  a.resize(n); b.resize(n);
  fwht(a, op); fwht(b, op);
  for (int i = 0; i < n; i++) a[i] = a[i]*b[i]%M;
  fwht(a, op, true); return a;
}