/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* https://www.acmicpc.net/problem/10066
*/
struct EERTREE {
  struct Node {
    int l, f, c, p, nxt[26];
    Node(int l, int f, int p = 0) : l(l), f(f), c(0), p(p) {
      for (int i = 0; i < 26; i++) nxt[i] = 0;
    }
  };
  vector<Node> tree; string s; int last;
  void reset() { s = "#"; last = 1; }
  EERTREE() { reset();
    tree.push_back({ -1, 0 }); tree.push_back({ 0, 0 });
  }
  int find(int x) {
    int p = sz(s)-1;
    while (s[p - tree[x].l - 1] != s[p]) x = tree[x].f;
    return x;
  }
  void add(char c) {
    s += c; int v = c-'a', p = find(last);
    if (!tree[p].nxt[v]) {
      int lnk = (p == 0 ? 1 : tree[find(tree[p].f)].nxt[v]);
      tree.push_back({ tree[p].l+2, lnk, p });
      tree[p].nxt[v] = sz(tree)-1;
    }
    tree[last = tree[p].nxt[v]].c++;
  }
  void count() {
    for (int i = sz(tree)-1; i > 1; i--) tree[tree[i].f].c += tree[i].c;
  }
};