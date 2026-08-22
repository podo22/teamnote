/**
* [Metadata]
* Author : alreadysolved
* [Tested on]
* https://www.acmicpc.net/problem/10066
*/
// Eertree(palindromic tree): "서로 다른 팰린드롬 부분 문자열"을 노드로 압축.
// 각 노드 = 팰린드롬 하나. 간선 = 양끝에 같은 문자 붙여 만든 더 긴 팰린드롬.
// "distinct 팰린드롬" 개수·등장 횟수
//  for (char c : s) et.add(c); // 문자열 순서대로 삽입 (온라인)
//  et.count(); // 등장 횟수
//  서로 다른 팰린드롬 개수 = sz(tree) - 2 // 노드 0,1은 가상/빈 루트
//  tree[i].l  = 그 팰린드롬 길이
//  tree[i].c  = 등장 횟수 (count() 후에만 정확)
//  tree[i].f  = suffix link (가장 긴 진짜 접미사 팰린드롬)
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