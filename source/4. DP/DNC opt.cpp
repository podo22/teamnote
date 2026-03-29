/**
 * [Metadata]
 * Reference : https://github.com/overnap/cp-teamnote/blob/master/source/DivideAndConquerOptimization.cpp
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
ll dp[MAX_K][MAX_N];
// l부터 r까지 구간의 비용을 계산하는 함수
ll get_cost(int l, int r) {/* return sum[l][r] + C; */}
// k: 현재단계(구간개수 등), pL,pR: j를 찾을 탐색범위
void dnc(int k, int l, int r, int pL, int pR) {
  if (l > r) return;
  int opt = pL, mid = (l + r) / 2;
  dp[k][mid] = -1e18 // 최솟값문제: INF, 최댓값: -INF
  for (int j = pL; j <= min(mid, pR); j++) {
    ll val = (j==0 ?: dp[k-1][j-1]) + get_cost(j, mid);
    if (val > dp[k][mid]) {
      dp[k][mid] = val;
      opt = j;
    }
  }
  dnc(k, l, mid - 1, pL, opt);
  dnc(k, mid + 1, r, opt, pR);
}
// for (int i = 1; i <= T; i++) dnc(i, 0, n-1, 0, n-1);