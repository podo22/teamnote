/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 다각형 넓이*2 (신발끈 공식)
ll area2(const vector<P>& v) {
  ll res = 0; int n = sz(v);
  for (int i = 0; i < n; i++)
    res += v[i] / v[(i+1)%n];
  return abs(res);
}