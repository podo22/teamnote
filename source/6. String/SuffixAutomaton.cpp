/**
 * [Metadata]
 * Original Author : aeren
 * Source : https://github.com/justiceHui/icpc-teamnote/blob/master/code/String/SuffixAutomaton.cpp
 * [Tested on]
 * 
 */
template<typename T, size_t S, T init_val>
struct initialized_array : public array<T, S> {
  initialized_array() { this->fill(init_val); }
};

template<class Char_Type, class Adjacency_Type>
struct suffix_automaton {
  vector<int> len{0}, link{-1}, firstpos{-1}, is_clone{0};
  vector<Adjacency_Type> next{{}};
  ll ans = 0; int last = 0;
  int new_state(int l, int sl, int fp, bool c,
                const Adjacency_Type& adj) {
    int v = sz(len);
    len.push_back(l); link.push_back(sl); firstpos.push_back(fp);
    is_clone.push_back(c); next.push_back(adj); return v;
  }
  void extend(const vector<Char_Type>& s) {
    last = 0; for (auto c : s) extend(c);
  }
  void extend(Char_Type c) {
    int cur = new_state(len[last]+1, 0, len[last], false, {}), p = last;
    while (p != -1 && !next[p][c])
      next[p][c] = cur, p = link[p];
    if (p != -1) {
      int q = next[p][c];
      if (len[p]+1 == len[q]) link[cur] = q;
      else {
        int clone = new_state(len[p]+1, link[q], firstpos[q], true, next[q]);
        while (p != -1 && next[p][c] == q)
          next[p][c] = clone, p = link[p];
        link[cur] = link[q] = clone;
      }
    }
    last = cur; ans += len[cur]-len[link[cur]];
  }
  int size() const { return sz(len); }
};
// T.ans: 서로 다른 부분문자열 개수
// T.next[v][c]: 전이. 0이면 없음, 루트=0
// T.len[v]: 상태의 최대 길이, T.link[v]: suffix link
// T.firstpos[v]: 최대 길이 문자열의 최초 등장 끝idx
// 등장 횟수: 일반 상태 1, 클론 0으로 시작해 len 내림차순으로 link에 누적.
suffix_automaton<int, initialized_array<int,26,0>> T;
for (char c : s) T.extend(c-'a');
// 문자열 p가 s의 부분문자열인지 판정
int x = 0; for (char c : p) if ((x = T.next[x][c-'a']) == 0) return false;