/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct TwoSat {
  int n; SCC scc;
  vector<bool> res;
  TwoSat(int n) : n(n), scc(2 * n + 2), res(n + 1) {}
  // (x_a == is_a) OR (x_b == is_b) 추가
  void add(int a, bool is_a, int b, bool is_b) {
    int u = a << 1 | !is_a, v = b << 1 | !is_b;
    scc.add(u ^ 1, v);
    scc.add(v ^ 1, u);
  }
  bool satisfiable() {
    scc.build();
    for (int i = 1; i <= n; i++) {
      if (scc.id[i << 1] == scc.id[i << 1 | 1]) return false;
      res[i] = scc.id[i << 1] < scc.id[i << 1 | 1];
    }
    return true;
  }
  bool get(int i) { return res[i]; }
};