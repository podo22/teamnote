/**
* [Metadata]
* Original Author : JusticeHui
* Reference : http://boj.kr/cc544ffb909442198b37ca6e3b9e8c9d
* Modified by : alreadysolved
* [Tested on]
* https://www.acmicpc.net/problem/9250
*/
const int CH = 26;
struct AhoCorasick {
  struct Node {
    int ch[CH], nxt[CH], id, fail, out, cnt;
    Node() { memset(ch, 0, sizeof ch);
      memset(nxt, 0, sizeof nxt);
      id = fail = out = cnt = 0;
    }
  };
  vector<Node> T; int tc = 1;
  AhoCorasick(int SZ) { T.resize(SZ); }
  int ID(char c) { return c - 'a'; }
  void insert(const string &s, int id) {
    int x = 1; // 'id' must be >= 1
    for (auto c : s) {
      int cid = ID(c);
      if (!T[x].ch[cid]) T[x].ch[cid] = ++tc;
      x = T[x].ch[cid];
    }
    T[x].id = id; T[x].cnt++;
  }
  int next(int x, int c) {
    int& res = T[x].nxt[c]; if (res) return res;
    if (x != 1 && !T[x].ch[c]) res = next(T[x].fail, c);
    else if (T[x].ch[c]) res = T[x].ch[c];
    else res = 1;
    return res;
  }
  void build() {
    queue<int> q;
    for (int i = 0; i < CH; i++) {
      if (int c = T[1].ch[i]) T[c].fail = 1, q.push(c);
    }
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int i = 0; i < CH; i++) {
        int c = T[v].ch[i]; if (!c) continue;
        int fail = T[c].fail = next(T[v].fail, i);
        if (T[fail].id) T[c].out = fail;
        else T[c].out = T[fail].out;
        T[c].cnt += T[fail].cnt; q.push(c);
      }
    }
  }
  vector<pair<int,int>> find(const string &s) {
    vector<pair<int,int>> res;
    int x = 1, tot = 0;
    for (int i = 0; i < sz(s); i++) {
      x = next(x, ID(s[i])); tot += T[x].cnt;
      if (T[x].id) res.emplace_back(T[x].id, i);
      for (int y = T[x].out; y; y = T[y].out)
      res.emplace_back(T[y].id, i);
    }
    assert(sz(res) == tot);
    return res;
  }
  ll count(const string &s) {
    ll res = 0; int x = 1;
    for (char c : s) res += T[x = next(x, ID(c))].cnt;
    return res;
  }
};