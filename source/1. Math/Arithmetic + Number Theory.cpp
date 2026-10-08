ll modmul(ll a, ll b, ll m) { return (ll)((__int128)a*b % m); }
ll modpow(ll b, ll e, ll m) {
  ll ans = 1;
  for (; e; b = modmul(b, b, m), e /= 2)
  if (e & 1) ans = modmul(ans, b, m);
  return ans;
}
ll xgcd(ll a, ll b, ll &x, ll &y) {
  if (!b) return x = 1, y = 0, a;
  ll x1, y1, g = xgcd(b, a % b, x1, y1);
  return x = y1, y = x1 - a / b * y1, g;
}
ll modinv(ll a, ll m) {
  ll x, y;
  ll g = xgcd(a, m, x, y);
  if (g != 1) return -1;
  return (x%m + m) % m;
}
ll phi(ll n) {
  ll res = n;
  for (ll i = 2; i*i <= n; i++) if (n%i == 0) {
    res -= res / i;
    while (n%i == 0) n /= i;
  } if (n > 1) res -= res / n;
  return res;
}
// Multiplicative Order: a^k == 1 (mod m)인 최소 양의 k. gcd(a,m)=1.
ll get_order(ll a, ll m) {
  if (gcd(a, m) != 1) return -1;
  ll k = phi(m);
  for (ll p : factor(k))
    if (modpow(a, k/p, m) == 1) k /= p;
  return k;
}
// Power Tower: a[0]^(a[1]^(...)) mod m.
ll power_tower(const vector<ll>& a, int idx, ll m) {
  if (idx == sz(a) || m == 1) return 1;
  auto mul = [](ll x, ll y, ll m) -> ll {
    __int128 v = (__int128)x*y;
    return v < m ? (ll)v : (ll)(v%m)+m;
  };
  auto pow = [&](ll b, ll e) {
    ll ret = 1;
    for (; e; b = mul(b, b, m), e /= 2)
      if (e & 1) ret = mul(ret, b, m);
    return ret;
  };
  return pow(a[idx], power_tower(a, idx+1, phi(m)));
}
cout << power_tower(a, 0, mod) % mod;
// Floor Sum: sum_{i=1}^n floor(n/i). n/i가 같은 구간을 묶음.
ll floor_sum(ll n) {
  ll sum = 0;
  for (ll i = 1, last; i <= n; i = last + 1) {
    last = n / (n / i);
    sum += (n / i) * (last - i + 1);
    // n / x yields the same value for i <= x <= last.
  }
  return sum;
}
// sum_{i=0}^{n-1} floor((a*i+b)/m), O(log m). n,a,b>=0, m>0
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
// nCk: fac[0]=1; finv[N]=modpow(fac[N],M-2,M); C(n,k)=fac[n]*finv[k]%M*finv[n-k]%M (M prime, N<M, k<0 or k>n => 0).