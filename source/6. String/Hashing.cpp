/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
*/
template<ll P, ll M> struct Hash1 {
  vector<ll> h, p;
  void build(const string& s) {
    int n = sz(s); h.assign(n+1, 0); p.assign(n+1, 1);
    for (int i = 0; i < n; i++) {
      h[i+1] = (h[i]*P + s[i])%M;
      p[i+1] = p[i]*P%M;
    }
  }
  ll get(int l, int r) const { // [l,r)
    return (h[r]-h[l]*p[r-l]%M+M)%M;
  }
};
template<ll P1, ll M1, ll P2, ll M2> struct Hashing {
  Hash1<P1,M1> a; Hash1<P2,M2> b;
  void build(const string& s) { a.build(s); b.build(s); }
  pair<ll,ll> get(int l, int r) const {
    return { a.get(l,r), b.get(l,r) };
  }
};
// 1e5+3, 1e5+13, 131'071, 524'287, 1'299'709, 1'301'021
// 1e9-63, 1e9+7, 1e9+9, 1e9+103
// using Hash = Hashing<917, 998244353, 10009, 1000000007>;
// Hash H; H.build(s);
// H.get(l,r) == H.get(l2,r2): s[l..r-1]과 s[l2..r2-1] 비교