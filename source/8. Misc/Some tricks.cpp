/**
 * [Metadata]
 * Reference : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Misc/Cpp-Grammer.cpp
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
// ll에는 ~ll 사용, clz/ctz는 x=0에서 사용 불가.
__builtin_popcount(x); // 켜진 비트(1)의 총 개수
__builtin_clz(x); // 왼쪽(MSB)부터 연속된 0의 개수
__builtin_ctz(x); // 오른쪽(LSB)부터 연속된 0의 개수
// popcount를 유지하면서 다음으로 큰 수 / 작은 수
bool next_comb(ll& bit, int N) {
  ll x = bit & -bit, y = bit + x;
  bit = (((bit & ~y) / x) >> 1) | y; 
  return (bit < (1LL << N));
}
ll init_comb(int n, int k) { 
  return ((1LL << k) - 1) << (n - k); 
}
bool prev_comb(ll& bit) {
  ll y = ~bit & -~bit, x = bit & -y;
  bit = x - ((x & -x) / (y << 1));
  return x != 0;
}
// mask의 모든 부분집합을 내림차순으로 순회 (0 제외), O(3^N)
for (int sub = mask; sub > 0; sub = (sub-1)&mask);
// mask를 포함하는 모든 상위집합을 오름차순으로 순회
for (int sup = mask; sup < (1<<n); sup = (sup+1)|mask);
// 런타임 변수 n에 맞는 크기의 bitset을 사용
template <int len = 1> void solve(int n) {
  if (len < n) { solve<min(len*2, 200005)>(n); return; }
  bitset<len> bs;
  // do stuff
}
// bitset 고속순회 (켜져있는 비트만 순회)
for (int i = bs._Find_first(); i < bs.size(); i = bs._Find_next(i)) {
  // do stuff
}
// 1부터 n까지의 수에서 숫자 i가 등장하는 총 횟수
ll count_digit_frq(ll n, int i) {
  ll ret = 0;
  for (ll j = 1; j <= n; j *= 10) {
    ll q = n / (j*10), r = n % (j*10);
    ret += (i == 0 ? (q-1)*j : q*j);
    if (r >= i*j) ret += (r < (i+1)*j ? r-i*j+1 : j);
  }
  return ret;
}
// 특정 날짜(년, 월, 일)의 요일 / 0: Sat, 1: Sun, ...
int get_day_of_week(int y, int m, int d) {
  if (m <= 2) y--, m += 12; int c = y / 100; y %= 100;
  int w = ((c>>2)-(c<<1)+y+(y>>2)+(13*(m+1)/5)+d-1)%7;
  if (w < 0) w += 7; return w;
}
// 도달 가능 여부 O(N^3 / 64)
bitset<MAXN> reach[MAXN];
for (int k = 0; k < n; k++) {
  for (int i = 0; i < n; i++) {
    if (reach[i][k]) reach[i] |= reach[k];
  }
}
sort(all(v)); // Permutation
do {
  // process v
} while (next_permutation(all(v)));
vector<int> mask(n, 0); // Combination(nCk)
fill(mask.end()-r, mask.end(), 1); // pick r
do {
  for (int i = 0; i < n; i++) if (mask[i]) {
    /* v[i] is selected */ }
} while (next_permutation(all(mask)));
sort(all(v)); // Partial Permutation (nPk)
do {
  for(int i = 0; i < k; i++) { /* use v[i] */ }
  reverse(v.begin()+k, v.end());
} while (next_permutation(all(v)));
// 부호 있는 정수 나눗셈의 floor/ceil. b!=0, 몫은 ll 범위.
ll floor_div(ll a, ll b) {
  ll q = a/b, r = a%b;
  return q - (r && (r<0) != (b<0));
}
ll ceil_div(ll a, ll b) {
  ll q = a/b, r = a%b;
  return q + (r && (r<0) == (b<0));
}
// 부분배열 GCD/AND/OR의 결과별 개수·합 집계.
// v: 현재 위치에서 끝나는 부분배열의 {결과 값, 개수}, 짧은 구간부터.
vector<pair<ll,ll>> v;
ll ans = 0;
for (ll x : a) {
  vector<pair<ll,ll>> nv{{ x, 1 }};
  for (auto [g, c] : v) {
    g = gcd(g, x); // AND: g &= x; OR: g |= x;
    if (nv.back().first == g) nv.back().second += c;
    else nv.push_back({ g, c });
  }
  v.swap(nv);
  for (auto [g, c] : v) ans += g*c; // 모든 부분배열 GCD의 합
}