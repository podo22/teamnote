/**
 * [Metadata]
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
// dp[k][i] = min_j f(k,j,i). 이전 행을 먼저 계산해야 함.
// 조건: 최적 j(동률이면 가장 작은 j)가 i에 대해 비감소.
// 각 계산 대상 i에는 유효한 전이가 하나 이상 있어야 함.
// max: 초기값 INF -> -INF, 비교 < -> >, 불가능한 전이도 -INF.
// 상태/후보가 각각 O(N), f가 O(1)이면 한 행 O(N log N).
const ll INF = 1LL << 62;
ll dp[MAX_K][MAX_N];
ll f(int k, int j, int i); // 전이 값. 불가능하면 INF 반환.
void dnc(int k, int l, int r, int pL, int pR) {
  if (l > r) return;
  int opt = pL, mid = (l + r) / 2;
  dp[k][mid] = INF;
  for (int j = pL; j <= pR; j++) {
    ll val = f(k, j, mid);
    if (val < dp[k][mid]) {
      dp[k][mid] = val; opt = j;
    }
  }
  dnc(k, l, mid - 1, pL, opt);
  dnc(k, mid + 1, r, opt, pR);
}
// dp[k][i]: 앞의 i개 원소를 정확히 k개 구간으로 나눈 최소 비용
ll f(int k, int j, int i) {
  if (j >= i || dp[k-1][j] == INF) return INF;
  ll sum = S[i] - S[j];
  return dp[k-1][j] + sum * sum; // 계산 결과가 INF 미만이라고 가정
}
// 1 <= K <= n. dp/S의 두 번째 차원은 n+1 이상.
for (int k = 0; k <= K; k++)
  fill(dp[k], dp[k] + n+1, INF);
dp[0][0] = 0;
for (int k = 1; k <= K; k++)
  dnc(k, k, n, k-1, n-1);
// 답: dp[K][n]