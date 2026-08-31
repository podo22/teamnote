/**
 * [Metadata]
 * Reference : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Misc/Cpp-Grammer.cpp
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
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
// v(>0)보다 크고 popcount가 같은 가장 작은 정수
ll next_perm(ll v) {
  ll t = v | (v - 1);
  return (t+1)|(((~t & -~t)-1)>>(__builtin_ctz(v)+1));
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
// LIS
// a[i] < a[j] -> lower_bound
// a[i] <= a[j] -> upper_bound
vector<int> LIS(vector<int> v) {
  int n = sz(v);
  vector<int> lis, pos(n);
  for (int i = 0; i < n; i++) {
    auto it = lower_bound(all(lis), v[i]);
    pos[i] = it - lis.begin();
    if (it == lis.end()) lis.push_back(v[i]);
    else *it = v[i];
  }
  vector<int> res;
  for (int i = n-1, j = sz(lis)-1; i >= 0; i--) {
    if (pos[i] == j) {
      res.push_back(v[i]); j--;
    }
  }
  reverse(all(res));
  return res;
}
// 3D LIS
struct Cand {
  map<int,int> m; // y -> 그 y에서의 최소 z
  bool chk(int y, int z) const {
    auto it = m.lower_bound(y);
    return it != m.begin() && prev(it)->second < z; // non-strict: <=
  }
  void add(int y, int z) {
    auto it = m.lower_bound(y);
    if (it != m.begin() && prev(it)->second <= z) return;
    while (it != m.end() && it->second >= z) it = m.erase(it);
    m.insert(it, {y, z});
  }
};
int LIS3D(vector<array<int,3>> v) {
  sort(all(v), [](auto &a, auto &b) {
    if (a[0] != b[0]) return a[0] < b[0];
    return a[1] > b[1]; // non-strict: <
  });
  vector<Cand> res;
  for (auto [x, y, z] : v) {
    int lo = 0, hi = sz(res);
    while (lo < hi) {
      int mid = (lo+hi) / 2;
      if (res[mid].chk(y, z)) lo = mid + 1;
      else hi = mid;
    }
    if (lo == sz(res)) res.emplace_back();
    res[lo].add(y, z);
  }
  return sz(res);
}
// 도달 가능 여부 O(N^3 / 64)
bitset<MAXN> reach[MAXN];
for (int k = 0; k < n; k++) {
  for (int i = 0; i < n; i++) {
    if (reach[i][k]) reach[i] |= reach[k];
  }
}