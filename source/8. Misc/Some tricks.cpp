__builtin_popcount(x); // 켜진 비트(1)의 총 개수
__builtin_clz(x); // 왼쪽(MSB)부터 연속된 0의 개수
__builtin_ctz(x); // 오른쪽(LSB)부터 연속된 0의 개수
// popcount를 유지하면서 다음으로 큰 수
bool next_combination(ll& bit, int N) {
  ll x = bit & -bit, y = bit + x;
  bit = (((bit & ~y) / x) >> 1) | y; 
  return (bit < (1LL << N));
}
// v(>0)보다 크고 popcount가 같은 가장 작은 정수
ll next_perm(ll v) {
  ll t = v | (v - 1);
  return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}
// mask의 모든 부분집합을 내림차순으로 순회 (0 제외), O(3^N)
for (int submask = mask; submask > 0; submask = (submask-1) & mask);
// mask를 포함하는 모든 상위집합을 오름차순으로 순회
for (int supmask = mask; supmask < (1 << n); supmask = (supmask+1) | mask);
// 런타임 변수 n에 맞는 크기의 bitset을 사용
const int MAXLEN = 200005; // 최대 범위
template <int len = 1> 
void solve(int n) {
  if (len < n) { solve<min(len * 2, MAXLEN)>(n); return; }
  bitset<len> bs;
  // do stuff
}
// bitset 고속순회 (켜져있는 비트만 순회)
void bitset_iterate(bitset<1000>& bs) {
  int idx = bs._Find_first(); 
  while (idx < bs.size()) {
    // do stuff
    idx = bs._Find_next(idx); 
  }
}
// 1부터 n까지의 수에서 숫자 i가 등장하는 총 횟수
ll count_digit_frq(ll n, int i) {
  ll ret = 0;
  for (ll j = 1; j <= n; j *= 10) {
    ll div = j * 10, quote = n / div, rem = n % div;
    if (i == 0) ret += (quote - 1) * j;
    else ret += quote * j;
    if (rem >= i * j) {
      if (rem < (i + 1) * j) ret += rem - i * j + 1;
      else ret += j;
    }
  }
  return ret;
}
// 특정 날짜(년, 월, 일)의 요일 / 0: Sat, 1: Sun, ...
int get_day_of_week(int y, int m, int d) {
  if (m <= 2) y--, m += 12; int c = y / 100; y %= 100;
  int w = ((c>>2)-(c<<1)+y+(y>>2)+(13*(m+1)/5)+d-1) % 7;
  if (w < 0) w += 7; return w;
}