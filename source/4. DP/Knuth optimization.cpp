// 인접 구간을 합치는 최소 비용 DP. 예: 파일 합치기.
// dp[l][r]=min_k(dp[l][k]+dp[k+1][r])+cost(l,r), dp[i][i]=0.
// 조건: opt[l][r-1]<=opt[l][r]<=opt[l+1][r]. 동률이면 큰 k.
// 충분조건(a<=b<=c<=d): C(b,c)<=C(a,d), C(a,c)+C(b,d)<=C(a,d)+C(b,c).
ll knuth(int n, auto cost) {
  const ll INF = 1LL << 62;
  vector<vector<ll>> dp(n, vector<ll>(n));
  vector<vector<int>> opt(n, vector<int>(n));
  for (int i = 0; i < n; i++) opt[i][i] = i;
  for (int len = 2; len <= n; len++)
    for (int l = 0, r = len-1; r < n; l++, r++) {
      dp[l][r] = INF; ll c = cost(l, r);
      for (int k = opt[l][r-1]; k <= min(r-1, opt[l+1][r]); k++) {
        ll v = dp[l][k] + dp[k+1][r] + c;
        if (v <= dp[l][r]) dp[l][r] = v, opt[l][r] = k;
      }
    }
  return dp[0][n-1];
}
vector<ll> a{40, 30, 30, 50}, S(sz(a)+1); // 파일합치기
for (int i = 0; i < sz(a); i++) S[i+1] = S[i]+a[i];
ll ans = knuth(sz(a), [&](int l, int r) {
  return S[r+1]-S[l];
}); // 300