struct TwoSat {
  int n; SCC scc;
  vector<bool> result;
  TwoSat(int n) : n(n), scc(2 * n + 2), result(n + 1) {}
  // (x_a == is_a) OR (x_b == is_b) 추가
  void add_clause(int a, bool is_a, int b, bool is_b) {
    int u = a << 1 | !is_a, v = b << 1 | !is_b;
    scc.add_edge(u ^ 1, v);
    scc.add_edge(v ^ 1, u);
  }
  bool satisfiable() {
    scc.build();
    for (int i = 1; i <= n; i++) {
      if (scc.scc_id[i << 1] == scc.scc_id[i << 1 | 1]) return false;
      result[i] = scc.scc_id[i << 1] < scc.scc_id[i << 1 | 1];
    }
    return true;
  }
  bool get(int i) { return result[i]; }
};