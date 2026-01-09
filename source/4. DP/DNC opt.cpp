ll dp[MAX_K][MAX_N];
// i부터 j까지 구간의 비용을 계산하는 함수 (문제에 맞게 구현)
ll get_cost(int l, int r) { /* return sum[l][r] + C; */ }
// k: 현재 단계(구간 개수 등), pL, pR: 최적의 j를 찾을 탐색 범위
void dnc(int k, int l, int r, int pL, int pR) {
    if (l > r) return;
    int opt = pL, mid = (l + r) / 2;
    dp[k][mid] = -1e18 // 최솟값 문제면 INF, 최댓값 문제면 -INF
    for (int j = pL; j <= min(mid, pR); j++) {
        ll val = (j == 0 ? 0 : dp[k - 1][j - 1]) + get_cost(j, mid);
        if (val > dp[k][mid]) {
            dp[k][mid] = val;
            opt = j;
        }
    }
    dnc(k, l, mid - 1, pL, opt);
    dnc(k, mid + 1, r, opt, pR);
}
// usage: for (int i = 1; i <= T; i++) dnc(i, 0, n-1, 0, n-1);