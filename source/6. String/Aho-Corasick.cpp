/**
 * [Metadata]
 * Original Author : JusticeHui
 * Reference : http://boj.kr/cc544ffb909442198b37ca6e3b9e8c9d
 * Modified by : alreadysolved
 * [Tested on]
 * https://www.acmicpc.net/problem/9250
 */
// 소문자 패턴. insert 전부 -> build 한 번 -> find/count.
// find: 서로 다른 패턴, id>=1. 반환 {패턴id, 끝idx}.
// count: 겹치는 등장도 모두 셈. 같은 패턴의 중복 삽입도 횟수에 반영.
const int CH = 26;
struct AhoCorasick {
  struct Node {
    int ch[CH]{}, id = 0, fail = 0, out = 0, cnt = 0;
  };
  vector<Node> T; int tc = 1; // 루트=1, 0은 없는 간선
  AhoCorasick(int SZ) : T(SZ) {}
  int ID(char c) { return c-'a'; }
  void insert(const string& s, int id) {
    int x = 1;
    for (char c : s) {
      int v = ID(c);
      if (!T[x].ch[v]) T[x].ch[v] = ++tc;
      x = T[x].ch[v];
    }
    T[x].id = id; T[x].cnt++;
  }
  void build() {
    queue<int> q;
    for (int i = 0; i < CH; i++) {
      int& u = T[1].ch[i];
      if (u) T[u].fail = 1, q.push(u);
      else u = 1;
    }
    while (!q.empty()) {
      int v = q.front(); q.pop();
      int f = T[v].fail;
      T[v].cnt += T[f].cnt;
      T[v].out = T[f].id ? f : T[f].out;
      for (int i = 0; i < CH; i++) {
        int& u = T[v].ch[i];
        if (u) T[u].fail = T[f].ch[i], q.push(u);
        else u = T[f].ch[i];
      }
    }
  }
  int next(int x, int c) { return T[x].ch[c]; }
  vector<pair<int,int>> find(const string& s) {
    vector<pair<int,int>> res; int x = 1;
    for (int i = 0; i < sz(s); i++) {
      x = next(x, ID(s[i]));
      if (T[x].id) res.emplace_back(T[x].id, i);
      for (int y = T[x].out; y; y = T[y].out)
        res.emplace_back(T[y].id, i);
    }
    return res;
  }
  ll count(const string& s) {
    ll res = 0; int x = 1;
    for (char c : s) res += T[x = next(x, ID(c))].cnt;
    return res;
  }
};
// AhoCorasick ac(패턴 길이 합 + 2);
// ac.insert(p, id); -> ac.build();
// ac.find(s); // {id, 끝idx} 목록
// ac.count(s); // 총 등장 횟수