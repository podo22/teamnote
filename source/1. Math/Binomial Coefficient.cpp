// when M is big prime; Init: O(MAXN), Query: O(1)
ll modmul(ll a, ll b, ll m)
ll modpow(ll b, ll e, ll m)
const int M = 1e9+7, MAXN = 4000000;
ll fac[MAXN+5], finv[MAXN+5];
void init() {
  fac[0] = 1;
  for (int i = 1; i <= MAXN; i++)
    fac[i] = modmul(fac[i-1], i, M);
  finv[MAXN] = modpow(fac[MAXN], M-2, M);
  for (int i = MAXN-1; i >= 0; i--)
    finv[i] = modmul(finv[i+1], i+1, M);
}
ll nCk(int n, int k) {
  ll r = modmul(fac[n], finv[n-k], M);
  return modmul(r, finv[k], M);
}
// O(Sum of p^k) per query. (M = product of p^k)
ll modmul(ll a, ll b, ll m)
ll modpow(ll b, ll e, ll m)
ll xgcd(ll a, ll b, ll &x, ll &y)
ll modinv(ll a, ll m)
ll count(ll n, ll p) {
  ll cnt = 0; while (n > 0) { cnt += n/p; n /= p; }
  return cnt;
}
ll calc(ll n, ll p, ll pe, const auto& ft) {
  if (n == 0) return 1;
  ll v = ft[pe], res = modpow(v, n/pe, pe);
  res = modmul(res, ft[n%pe], pe);
  return modmul(res, calc(n/p, p, pe, ft), pe);
}
ll nCk_pe(ll n, ll k, ll p, ll pe, ll e) {
  if (k < 0 || k > n) return 0;
  ll pc = count(n, p) - count(k, p) - count(n-k, p);
  if (pc >= e) return 0;
  vector<ll> ft(pe+1); ft[0] = 1;
  for(int i = 1; i <= pe; i++) {
    ft[i] = ft[i-1];
    if (i%p != 0) ft[i] = modmul(ft[i], i, pe);
  }
  ll den = modmul(calc(k, p, pe, ft), calc(n-k, p, pe, ft), pe);
  ll res = modmul(calc(n, p, pe, ft), modinv(den, pe), pe);
  res = modmul(res, modpow(p, pc, pe), pe);
  return res;
}
ll nCk(ll n, ll k, int m) {
  if (k < 0 || k > n) return 0;
  if (k == 0 || k == n) return 1;
  ll t = m, res = 0;
  auto add = [&](ll p, ll pe, ll e) {
    ll rem = nCk_pe(n, k, p, pe, e);
    ll tm = modmul(rem, m/pe, m);
    tm = modmul(tm, modinv(m/pe, pe), m);
    res = (res + tm) % m;
  };
  for (ll i = 2; i*i <= t; i++) {
    if (t%i == 0) {
      ll p = i, pe = 1, e = 0;
      while (t%i == 0) { pe *= i; t /= i; e++; }
      add(p, pe, e);
    }
  }
  if (t > 1) add(t, t, 1);
  return res;
}