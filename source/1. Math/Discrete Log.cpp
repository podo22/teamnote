/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// a^x == b (mod m)의 최소 x>=0. 없으면 -1
// m>=1, 합성수·gcd(a,m)>1 지원.
ll discrete_log(ll a, ll b, int m) {
  a = (a%m+m)%m; b = (b%m+m)%m;
  ll k = 1; int cnt = 0;
  for (ll g; (g = gcd(a, (ll)m)) > 1; cnt++) {
    if (b == k) return cnt;
    if (b%g) return -1;
    b /= g; m /= g; k = k*(a/g)%m;
  }
  if (m == 1 || b == k) return cnt;
  int n = (int)sqrt(m) + 1;
  ll step = modpow(a, n, m), cur = b;
  map<ll,int> dec;
  for (int j = 0; j < n; j++, cur = cur*a%m) dec[cur] = j;
  cur = k;
  for (int i = 1; i <= n; i++) {
    cur = cur*step%m;
    auto it = dec.find(cur);
    if (it != dec.end()) return 1LL*i*n - it->second + cnt;
  }
  return -1;
}