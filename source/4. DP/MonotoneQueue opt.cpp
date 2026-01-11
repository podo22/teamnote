ll f(int j, int i); // j에서 i로 전이할 때의 값 (dp[j] + cost(j, i))
void solve() {
  auto cross = [&](ll p, ll q) {
    ll lo = max(p, q), hi = n + 1;
    while (lo + 1 < hi) {
      ll mid = (lo + hi) / 2;
      if (f(p, mid) > f(q, mid)) hi = mid; // min 기준: f(p) > f(q)면 q가 우세
      else lo = mid;
    }
    return hi;
  };
  deque<pair<ll,ll>> dq; // {candidate_index, start_pos}
  dq.push_back({0, 1}); // 초기값: 0번이 1번 위치부터 최적이라고 가정
  for (int i = 1; i <= n; i++) {
    while (dq.size() > 1 && dq[1].second <= i) dq.pop_front();
    dp[i] = f(dq[0].first, i);
    while (!dq.empty()) {
      ll p = dq.back().first;
      ll pos = cross(p, i);
      if (pos <= dq.back().second) dq.pop_back();
      else {
        if (pos <= n) dq.push_back({i, pos});
        break;
      }
    }
    if (dq.empty()) dq.push_back({i, 1});
  }
}