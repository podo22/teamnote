// Trie<10,0> tr;
template <int S = 26, char OS = 'a'> struct Trie {
  struct Node {
    int nxt[S], pass = 0, end = 0;
    Node() { memset(nxt, -1, sizeof(nxt)); }
  };
  vector<Node> tree;
  Trie() { init(); }
  void init() { tree.clear(); tree.emplace_back(); }
  // 원소 추가(1)/삭제(-1), O(|s|)
  void insert(const auto &s, int c = 1) {
    int u = 0; tree[u].pass += c;
    for (auto i : s) {
      int idx = i - OS;
      if (tree[u].nxt[idx] == -1) {
        tree[u].nxt[idx] = sz(tree); tree.emplace_back();
      }
      u = tree[u].nxt[idx]; tree[u].pass += c;
    }
    tree[u].end += c;
  }
  // 원소 삭제, O(|s|)
  bool erase(const auto& s, int c = 1) {
    if (count(s) < c) return false;
    insert(s, -c); return true;
  }
  // 완전 일치 개수, O(|s|)
  int count(const auto& s) const {
    int u = 0;
    for (auto i : s) {
      int idx = i - OS;
      if (u == -1 || tree[u].nxt[idx] == -1) return 0;
      u = tree[u].nxt[idx];
    }
    return tree[u].end;
  }
  // prefix로 포함 개수, O(|s|)
  int count_prefix(const auto& s) const {
    int u = 0;
    for (auto i : s) {
      int idx = i - OS;
      if (u == -1 || tree[u].nxt[idx] == -1) return 0;
      u = tree[u].nxt[idx];
    }
    return tree[u].pass;
  }
  // 사전순 k번째 문자열, O(|s| * S)
  string kth(int k) const {
    if (k <= 0 || k > tree[0].pass) return "";
    int u = 0; string res = "";
    while (true) {
      if (k <= tree[u].end) return res;
      k -= tree[u].end;
      for (int i = 0; i < S; i++) {
        int v = tree[u].nxt[i];
        if (v != -1 && tree[v].pass > 0) {
          if (k <= tree[v].pass) {
            res += (char)(i + OS);
            u = v; break;
          }
          k -= tree[v].pass;
        }
      }
    }
  }
};
template <typename T = ll, int B = 62> struct XorTrie {
  struct Node {
    int nxt[2]{ -1, -1 }, cnt = 0; // 서브트리 원소개수
  };
  vector<Node> tree;
  XorTrie() { init(); }
  void init() { tree.clear(); tree.emplace_back(); }
  // 원소 추가(1)/삭제(-1), O(B)
  void insert(T x, int c = 1) {
    int u = 0; tree[u].cnt += c;
    for (int i = B-1; i >= 0; i--) {
      int b = (x >> i) & 1;
      if (tree[u].nxt[b] == -1) {
        tree[u].nxt[b] = sz(tree); tree.emplace_back();
      }
      u = tree[u].nxt[b]; tree[u].cnt += c;
    }
  }
  // 원소 삭제, O(B)
  bool erase(T x, int c = 1) {
    if (count(x) < c) return false;
    insert(x, -c); return true;
  }
  // x 개수 조회, O(B)
  int count(T x) const {
    int u = 0;
    for (int i = B-1; i >= 0; i--) {
      int b = (x >> i) & 1;
      if (u == -1 || tree[u].nxt[b] == -1) return 0;
      u = tree[u].nxt[b];
    }
    return tree[u].cnt;
  }
  // max(x ^ y), O(B)
  T max_xor(T x) const {
    int u = 0; T res = 0;
    for (int i = B-1; i >= 0; i--) {
      int b = (x >> i) & 1, p = b ^ 1;
      if (tree[u].nxt[p] != -1 && tree[tree[u].nxt[p]].cnt > 0) {
        res |= (T(1) << i); u = tree[u].nxt[p];
      } else {
        u = tree[u].nxt[b];
      }
    }
    return res;
  }
  // min(x ^ y), O(B)
  T min_xor(T x) const {
    int u = 0; T res = 0;
    for (int i = B-1; i >= 0; i--) {
      int b = (x >> i) & 1;
      if (tree[u].nxt[b] != -1 && tree[tree[u].nxt[b]].cnt > 0) {
        u = tree[u].nxt[b];
      } else {
        res |= (T(1) << i); u = tree[u].nxt[b ^ 1];
      }
    }
    return res;
  }
  // x^y 기준 k번째 최솟값(1-idx), O(B)
  T kth_xor(T x, int k) const { 
    if (k <= 0 || k > tree[0].cnt) return -1;
    int u = 0; T res = 0;
    for (int i = B-1; i >= 0; i--) {
      int b = (x >> i) & 1, l = tree[u].nxt[b], l_cnt = (l != -1 ? tree[l].cnt : 0);
      if (k <= l_cnt) {
        u = l;
      } else {
        k -= l_cnt; res |= (T(1) << i);
        u = tree[u].nxt[b ^ 1];
      }
    }
    return res;
  }
  // (x^y) < k 만족하는 y 개수, O(B)
  int count_less(T x, T k) const {
    int u = 0, res = 0;
    for (int i = B-1; i >= 0; i--) {
      if (u == -1) break;
      int bx = (x >> i) & 1, bk = (k >> i) & 1;
      if (bk) {
        int same = tree[u].nxt[bx];
        if (same != -1) res += tree[same].cnt;
        u = tree[u].nxt[bx ^ 1];
      } else {
        u = tree[u].nxt[bx];
      }
    }
    return res;
  }
};