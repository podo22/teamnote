ll modmul(ll a, ll b, ll m) { return (ll)((__int128)a*b % m); }
ll modpow(ll b, ll e, ll m) { // e >= 0, m > 0. 반환값 [0,m).
  b %= m; if (b < 0) b += m;
  ll ans = 1 % m;
  for (; e; b = modmul(b, b, m), e /= 2) if (e & 1) ans = modmul(ans, b, m);
  return ans;
}
ll xgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll x1, y1, g = xgcd(b, a % b, x1, y1);
  return x = y1, y = x1 - a / b * y1, g;
}
ll modinv(ll a, ll m) { // m >= 2. 역원이 없으면 -1.
  a %= m; if (a < 0) a += m;
  ll x, y, g = xgcd(a, m, x, y);
  if (g != 1) return -1;
  x %= m; return x < 0 ? x+m : x;
}
ll phi(ll n) { // n >= 1.
  ll res = n;
  for (ll i = 2; i <= n/i; i++) if (n%i == 0) {
    res -= res / i;
    while (n%i == 0) n /= i;
  } if (n > 1) res -= res / n;
  return res;
}
// Multiplicative Order: 최소 양의 k: a^k ≡ 1 (mod m). 서로소x -> -1
ll get_order(ll a, ll m) {
  a %= m; if (a < 0) a += m;
  if (gcd(a, m) != 1) return -1;
  ll k = phi(m); // factor(k)는 소인수 중복 포함
  for (ll p : factor(k)) if (modpow(a, k/p, m) == 1) k /= p;
  return k;
}
// Power Tower: a[idx]^(a[idx+1]^(...)) mod m.
// a[i] >= 0, 1 <= m <= LLONG_MAX/2+1.
ll power_tower(const vector<ll> &a, int idx, ll m) {
  if (idx == sz(a)) return 1;
  ll lim = m;
  for (int i = idx; i < sz(a); i++) {
    if (lim == 1) {
      int j = i;
      while (j < sz(a) && a[j] == 0) j++;
      if ((j-i)%2) lim = 2;
      break;
    }
    if (a[i] <= 1) break;
    ll e = 0;
    for (__int128 v = 1; v < lim; v *= a[i]) e++;
    lim = e;
  }
  if (m == 1) return lim == 1;
  ll res = modpow(a[idx], power_tower(a, idx+1, phi(m)), m);
  return res + (lim == 1 ? m : 0);
}
cout << power_tower(a, 0, mod) % mod;
// Floor Sum: Σ_{i=1}^n floor(n/i). 몫이 같은 [i,last]를 묶음
ll floor_sum(ll n) {
  ll sum = 0;
  for (ll i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    sum += (n / i) * (last - i + 1);
    if (last == n) break;
  }
  return sum;
}
// Σ_{i=0}^{n-1} floor((a*i+b)/m). n,a,b >= 0, m > 0
ll floor_sum(ll n, ll m, ll a, ll b) {
  ll ret = 0;
  while (true) {
    ret += (__int128)n*(n-1)/2*(a/m) + (__int128)n*(b/m);
    a %= m; b %= m;
    __int128 y = (__int128)a*n + b;
    if (y < m) return ret;
    n = y/m; b = y%m;
    swap(a, m);
  }
}
// nCk: fac[0] = 1; finv[N] = modpow(fac[N], M-2, M); finv[i-1]=finv[i]*i%M (i=N..1). C(n,k) = fac[n]*finv[k]%M * finv[n-k]%M (M:prime, N<M, k<0 or k>n => 0)