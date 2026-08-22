/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
*/
template<ll P1, ll M1, ll P2, ll M2>
struct Hashing {
  vector<ll> h1, h2, p1, p2;
  void build(const string &s) {
    int n = sz(s);
    h1 = h2 = p1 = p2 = vector<ll>(n+1);
    p1[0] = p2[0] = 1;
    for (int i = 0; i < n; i++) {
      h1[i+1] = (h1[i] * P1 + s[i]) % M1;
      h2[i+1] = (h2[i] * P2 + s[i]) % M2;
      p1[i+1] = p1[i] * P1 % M1;
      p2[i+1] = p2[i] * P2 % M2;
    }
  }
  pair<ll, ll> get(int l, int r) const { // 0-idx, [l, r)
    ll r1 = (h1[r] - h1[l] * p1[r-l]) % M1;
    ll r2 = (h2[r] - h2[l] * p2[r-l]) % M2;
    if (r1 < 0) r1 += M1;
    if (r2 < 0) r2 += M2;
    return { r1, r2 };
  }
};
// 1e5+3, 1e5+13, 131'071, 524'287, 1'299'709, 1'301'021
// 1e9-63, 1e9+7, 1e9+9, 1e9+103
// using Hash = Hashing<917, 998244353, 10009, 1000000007>;
// HS H; H.build(s);
// H.get(l, r) == H.get(l2, r2) → s[l..r-1] 와 s[l2..r2-1] 이 같은지