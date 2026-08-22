/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/11402
 * https://www.acmicpc.net/problem/14854
 */
// when M is big prime; Init: O(MAXN), Query: O(1)
ll modmul(ll a, ll b, ll m);
ll modpow(ll b, ll e, ll m);
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
  if (n < k || k < 0) return 0;
  ll r = modmul(fac[n], finv[n-k], M);
  return modmul(r, finv[k], M);
}