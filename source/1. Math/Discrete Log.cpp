/**
 * [Metadata]
 * Source : https://github.com/ShahjalalShohag/code-library/blob/main/Number%20Theory/Discrete%20Root.cpp
 * [Tested on]
 * 
 */
int primitive_root(int p) { // p is prime
  vector<int> fact;
  int phi = p-1, n = phi;
  for (int i = 2; i*i <= n; i++) {
    if (n%i == 0) {
      fact.push_back(i);
      while (n%i == 0) n /= i;
    }
  }
  if (n > 1) fact.push_back(n);
  for (int res = 2; res <= p; res++) { // this loop will run at most (logp ^ 6) times i.e. until a root is found
    bool ok = true;
    // check if this is a primitive root modulo p
    for (int i = 0; i < sz(fact) && ok; i++) ok &= modpow(res, phi / fact[i], p) != 1;
    if (ok) return res;
  }
  return -1;
}
// returns any or all numbers x such that x ^ k = a (mod m)
// existence: a = 0 is trivial, and if a > 0: a ^ (phi(m) / gcd(k, phi(m))) == 1 mod m
// if solution exists, then number of solutions = gcd(k, phi(m)).
// here m is prime, but it will work for any integer which has a primitive root
int discrete_root(int k, int a, int m) {
  if (a == 0) return 1;
  int g = primitive_root(m), phi = m-1; // m is prime
  // run baby step-giant step
  int sq = (int)sqrt(m+.0) + 1;
  vector<pair<int,int>> dec(sq);
  for (int i = 1; i <= sq; i++) dec[i-1] = { modpow(g, 1LL * i * sq % phi * k % phi, m), i };
  sort(all(dec)); int ans = -1;
  for (int i = 0; i < sq; i++) {
    int my = modpow(g, 1LL* i * k % phi, m) * 1LL * a % m;
    auto  it = lower_bound(all(dec), make_pair(my, 0));
    if (it != dec.end() && it->first == my) {
      ans = it->second * sq - i; break;
    }
  }
  if (ans == -1) return -1; // no solution
  int d = (m-1) / __gcd(k, m-1);
  return modpow(g, ans%d, m);
  /* // for all possible answers
  int d = (m-1) / __gcd(k, m-1);
  vector<int> va;
  for (int i = ans%d; i < m-1; i += d) va.push_back(modpow(g, cur, m));
  sort(all(va));
  // assert(ans.size() == __gcd(k, m - 1))
  return va; */
}