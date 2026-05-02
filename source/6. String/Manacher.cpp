/**
 * [Metadata]
 * Original Author : JusticeHui
 * Modified by : alreadysolved
 * Source : https://github.com/justiceHui/icpc-teamnote-for-newbie/blob/master/code/String/Manacher.cpp
 * [Tested on]
 * https://www.acmicpc.net/problem/16163
 */
// 각 문자를 중심으로 하는 최장 팰린드롬의 반경을 반환
// Manacher("abaaba") = {0,1,0,3,0,1,6,1,0,3,0,1,0}
// # a # b # a # a # b # a #
// 0 1 0 3 0 1 6 1 0 3 0 1 0
struct manacher {
  vector<int> p;
  template<class T> manacher(const T &s) {
    int n = sz(s)*2+1, c = 0, r = 0;
    p.assign(n, 0); T t; t.resize(n);
    for (int i = 0; i < sz(s); i++) t[i*2+1] = s[i];
    for (int i = 0; i < n; i++) {
      if (r > i) p[i] = min(r-i, p[2*c-i]);
      while (i-p[i]-1 >= 0 && i+p[i]+1 < n && t[i-p[i]-1] == t[i+p[i]+1]) p[i]++;
      if (i+p[i] > r) c = i, r = i+p[i];
    }
  }
  bool chk(int l, int r) {
    if (l > r) return false;
    return p[l+r+1] >= r-l+1;
  }
  ll cnt() {
    ll res = 0;
    for (auto i : p) res += (i+1)/2;
    return res;
  }
};