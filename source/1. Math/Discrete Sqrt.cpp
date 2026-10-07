/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// p is prime
int primitive_root(int p) {
  if (p == 2) return 1;
  vector<int> fact;
  int n = p-1;
  for (ll i = 2; i*i <= n; i++) if (n%i == 0) {
    fact.push_back(i);
    while (n%i == 0) n /= i;
  }
  if (n > 1) fact.push_back(n);
  for (int g = 2; g < p; g++) {
    bool chk = true;
    for (int q : fact) if (modpow(g, (p-1)/q, p) == 1) {
      chk = false; break;
    }
    if (chk) return g;
  }
  return -1;
}
// 소수 p에서 x^k == a (mod p)의 해 하나. 없으면 -1.
// k >= 1. 최소 해를 보장하지 않음.
// O(sqrt(p) log p) 시간, O(sqrt(p)) 공간.
int discrete_root(ll k, ll a, int p) {
  assert(p >= 2 && k >= 1);
  a = (a%p + p) % p;
  if (a == 0) return 0;
  if (p == 2) return 1;
  int phi = p-1, g = primitive_root(p);
  k %= phi;
  int d = phi / gcd(k, (ll)phi);
  if (modpow(a, d, p) != 1) return -1;
  // x = g^y. (g^k)^y == a를 풀며, y는 modulo d.
  int sq = (int)sqrt(d) + 1;
  ll h = modpow(g, k, p), step = modpow(h, sq, p), cur = 1;
  vector<pair<int,int>> dec(sq);
  for (int i = 1; i <= sq; i++) {
    cur = cur * step % p;
    dec[i-1] = { (int)cur, i };
  }
  sort(all(dec)); cur = a;
  for (int i = 0; i < sq; i++) {
    auto it = lower_bound(all(dec), make_pair((int)cur, 0));
    if (it != dec.end() && it->first == cur) {
      ll y = (1LL*it->second*sq - i) % d;
      return modpow(g, y, p);
    }
    cur = cur * h % p;
  }
  return -1;
}