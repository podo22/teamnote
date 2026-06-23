/**
 * [Metadata]
 * Source : https://github.com/ShahjalalShohag/code-library/blob/main/Number%20Theory/Multiplicative%20Order.cpp
 * [Tested on]
 * 
 */
ll phi(ll n);
ll get_order(ll a, ll mod) {
  if (__gcd(a, mod) != 1) return -1;
  ll m = phi(mod), p = m, ans = 2e18;
  if (power(a, p, mod) == 1) ans = p;
  vector<ll> fac;
  for (ll i = 2 ; i*i <= m; i++) {
    while(m%i == 0) m /= i, fac.push_back(i);
  }
  if (m > 1) fac.push_back(m);
  for (auto x : fac) {
    if (power(a, p/x, mod) == 1) p /= x, ans = p;
  }
  assert(ans != 2e18); return ans;
}