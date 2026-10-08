/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 변수 0-based. 리터럴 2*i: x_i, 2*i+1: !x_i.
struct TwoSat {
  int n; SCC sc; vector<bool> ans;
  TwoSat(int n) : n(n), sc(2*n) {}
  int I(int x) { return x^1; }
  void add_edge(int u, int v) { // u->v와 대우
    sc.add(u, v); sc.add(I(v), I(u));
  }
  void add_clause(int u, int v) { add_edge(I(u), v); }
  void add_clause(int u, bool ut, int v, bool vt) {
    add_clause(u*2 + !ut, v*2 + !vt); // (u==ut) or (v==vt)
  }
  int add() { sc.add(); sc.add(); return n++; }
  void most_one(const vector<int>& v, bool cd = true) {
    int pre = -1;
    for (int i : v) {
      int x = i*2 + !cd, now = add()*2;
      add_edge(x, now);
      if (pre != -1) {
        add_edge(pre, now); add_edge(pre, I(x));
      }
      pre = now;
    }
  }
  bool solve() {
    sc.build(); ans.resize(n);
    for (int i = 0; i < n; i++) {
      if (sc.id[i*2] == sc.id[i*2+1]) return false;
      ans[i] = sc.id[i*2] < sc.id[i*2+1];
    }
    return true;
  }
};