/**
 * [Metadata]
 * Original Author : edenooo
 * Reference : https://github.com/justiceHui/icpc-teamnote/blob/master/code/String/AhoCorasick.cpp
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
struct AhoCorasick {
  struct Node {
      int nxt[26], fail, link = -1, id = -1;
      Node() { memset(nxt, 0, sizeof nxt); }
  };
  vector<Node> trie;
  AhoCorasick() { trie.emplace_back(); }
  void insert(const string& s, int id) {
      int u = 0;
      for (char c : s) {
          int &v = trie[u].nxt[c - 'a'];
          if (!v) v = trie.size(), trie.emplace_back();
          u = v;
      }
      trie[u].id = id;
  }
  void build() {
      queue<int> q;
      for (int i = 0; i < 26; i++) if (trie[0].nxt[i]) q.push(trie[0].nxt[i]);
      while (!q.empty()) {
          int u = q.front(); q.pop();
          for (int i = 0; i < 26; i++) {
              int &v = trie[u].nxt[i], f = trie[trie[u].fail].nxt[i];
              if (v) {
                  trie[v].fail = f;
                  trie[v].link = (trie[f].id != -1) ? f : trie[f].link;
                  q.push(v);
              } else v = f;
          }
      }
  }
  vector<pair<int,int>> query(const string& s) {
      vector<pair<int,int>> res;
      int u = 0;
      for (int i = 0; i < (int)s.size(); i++) {
          u = trie[u].nxt[s[i] - 'a'];
          for (int t = u; t != -1; t = trie[t].link) {
              if (trie[t].id != -1) res.emplace_back(i, trie[t].id);
          }
      }
      return res;
  }
};
int main() {
  AhoCorasick ac;
  vector<string> patterns = {"he", "she", "hers", "his"};
  for(int i = 0; i < sz(patterns); i++)
    ac.insert(patterns[i], i); // 패턴과 ID(0~N-1) 삽입
  ac.build(); // 실패 함수/DFA 빌드 (필수)
  string text = "ushers";
  auto res = ac.query(text); // 탐색: {끝 인덱스, 패턴 ID} 쌍 반환
  for (auto& [idx, id] : res) {
    // patterns[id] 가 text의 idx에서 끝남을 의미
  }
}