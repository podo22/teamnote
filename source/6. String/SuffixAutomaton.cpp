/**
 * [Metadata]
 * Original Author : aeren
 * Source : https://github.com/justiceHui/icpc-teamnote/blob/master/code/String/SuffixAutomaton.cpp
 * [Tested on]
 * 
 */
// 문자열의 모든 부분 문자열을 상태(≤2N)로 압축해 담은 DFA
// 부분 문자열의 개수·등장 횟수·매칭. O(len)
// suffix_automaton<int, initialized_array<int,26,0>> T;
// T.extend(s); // 문자열을 순서대로 삽입
// T.ans // 서로 다른 부분 문자열 개수
// T.next[v][c] // 전이 (없으면 0), v=0이 루트
// T.len[v], T.link[v] // 상태 길이, suffix link
// * 등장 횟수: 각 상태의 endpos 크기 = "그 상태의 가장 긴 문자열" 등장 횟수
//   extend 후, 각 상태 cnt=1(클론은 0)로 두고 link 트리에서 자식->부모로 누적합
template<typename T, size_t S, T init_val>
struct initialized_array : public array<T, S> {
  initialized_array(){ this->fill(init_val); }
};
template<class Char_Type, class Adjacency_Type>
struct suffix_automaton{
  // Begin States
  // len: length of the longest substring in the class
  // link: suffix link
  // firstpos: minimum value in the set endpos
  vector<int> len{0}, link{-1}, firstpos{-1}, is_clone{false};
  vector<Adjacency_Type> next{{}};
  ll ans{0LL}; // 서로 다른 부분 문자열 개수
  // End States
  void set_link(int v, int lnk){
    if(link[v] != -1) ans -= len[v] - len[link[v]];
    link[v] = lnk;
    if(link[v] != -1) ans += len[v] - len[link[v]];
  }
  int new_state(int l, int sl, int fp, bool c, const Adjacency_Type &adj){
    int now = len.size(); len.push_back(l); link.push_back(-1);
    set_link(now, sl); firstpos.push_back(fp);
    is_clone.push_back(c); next.push_back(adj); return now;
  } int last = 0;
  void extend(const vector<Char_Type> &s){
    last = 0; for(auto c: s) extend(c); }
  void extend(Char_Type c){
    int cur = new_state(len[last] + 1, -1, len[last], false, {}), p = last;
    while(~p && !next[p][c]) next[p][c] = cur, p = link[p];
    if(!~p) set_link(cur, 0);
    else{
      int q = next[p][c];
      if(len[p] + 1 == len[q]) set_link(cur, q);
      else{
        int clone = new_state(len[p] + 1, link[q], firstpos[q], true, next[q]);
        while(~p && next[p][c] == q) next[p][c] = clone, p = link[p];
        set_link(cur, clone); set_link(q, clone);
      }
    }
    last = cur;
  }
  int size() const {  return (int)len.size(); } // # of states
}; suffix_automaton<int, initialized_array<int,26,0>> T;
// for(auto c : s) if((x=T.next[x][c]) == 0) return false;