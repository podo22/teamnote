/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* 
*/
ll phi(ll n);
ll exmul(ll a, ll b, ll m) {
  if (a == 0 || b == 0) return 0;
  if (a*b >= m) return (a*b)%m + m;
  return a*b;
}
ll expow(ll b, ll e, ll m) {
  if (m == 1) return 1;
  ll ans = 1;
  for (; e; b = exmul(b, b, m), e /= 2)
    if (e & 1) ans = exmul(ans, b, m);
  return ans;
}
ll power_tower(const vector<ll>& a, int idx, ll m) {
  if (idx == sz(a) || m == 1) return 1;
  ll p = phi(m), exp = power_tower(a, idx+1, p);
  return expow(a[idx], exp, m);
}
// cout << power_tower(a, 0, mod) % mod;