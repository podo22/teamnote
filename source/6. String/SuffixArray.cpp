/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/9248
 */
// suffix array O(nlogn), lcp array O(n)
struct SA {
  int n;
  vector<int> sa, lcp, x, y, c;
  SA(const string& s) : n(sz(s)), sa(n), lcp(n), x(2*n, -1), y(2*n, -1), c(max(n, 256)) {
    for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i < sz(c); i++) c[i] += c[i-1];
    for (int i = n - 1; i >= 0; i--) sa[--c[x[i]]] = i;
    for (int d = 1, p = 0; ; d <<= 1, c.resize(p+1), p = 0) {
      for (int i = n - d; i < n; i++) y[p++] = i;
      for (int i = 0; i < n; i++) if (sa[i] >= d) y[p++] = sa[i] - d;
      fill(all(c), 0);
      for (int i = 0; i < n; i++) c[x[y[i]]]++;
      for (int i = 1; i < sz(c); i++) c[i] += c[i-1];
      for (int i = n - 1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
      swap(x, y); p = x[sa[0]] = 0;
      for (int i = 1; i < n; i++)
      x[sa[i]] = (y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+d] == y[sa[i]+d]) ? p : ++p;
      if (p == n-1) break;
    }
    for (int i = 0, k = 0; i < n; i++, k = max(0, k-1)) {
      if (x[i] == 0) continue;
      for (int j = sa[x[i]-1]; s[i+k] == s[j+k]; k++);
      lcp[x[i]] = k;
    }
  }
};