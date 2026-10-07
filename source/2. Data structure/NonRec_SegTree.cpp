/**
 * [Metadata]
 * Reference : https://www.acmicpc.net/blog/view/117
 * Implemented by : alreadysolved
 * [Tested on]
 * 
*/
template<typename Node> struct SegTree {
  int n, siz; Node e; // 항등원
  vector<Node> tr;
  function<Node(Node, Node)> fn;
  SegTree(int n, const Node& e, auto fn) : n(n), siz(1<<(__lg(n)+1)), e(e), tr(siz<<1, e), fn(fn) {}
  SegTree(const vector<Node>& v, const Node& e, auto fn) : n(sz(v)), siz(1<<(__lg(n)+1)), e(e), tr(siz<<1, e), fn(fn) {
    for (int i = 0; i < n; i++) tr[i+siz] = v[i];
    for (int i = siz-1; i > 0; i--) tr[i] = fn(tr[i<<1], tr[i<<1 | 1]);
  }
  void add(int i, const Node& val) {
    tr[i += siz] += val;
    while (i >>= 1) tr[i] = fn(tr[i<<1], tr[i<<1 | 1]);
  }
  void update(int i, const Node& val) {
    tr[i += siz] = val;
    while (i >>= 1) tr[i] = fn(tr[i<<1], tr[i<<1 | 1]);
  }
  Node query(int i) { return tr[i + siz]; }
  Node query(int l, int r) {
    Node L = e, R = e;
    for (l += siz, r += siz; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) L = fn(L, tr[l++]);
      if (~r & 1) R = fn(tr[r--], R);
    }
    return fn(L, R);
  }
  int find_kth(Node k) {
    if (tr[1] < k) return -1;
    int nd = 1;
    while (nd < siz) {
      nd <<= 1;
      if (tr[nd] < k) { k -= tr[nd]; nd |= 1; }
    }
    return nd - siz;
  }
  int find(auto chk) {
    if (!chk(e, tr[1])) return -1;
    int cur = 1; Node pref = e;
    while (cur < siz) {
      if (chk(pref, tr[cur << 1])) cur = cur << 1;
      else {
        pref = fn(pref, tr[cur << 1]);
        cur = cur << 1 | 1;
      }
    }
    return cur - siz;
  }
};
vector<int> v = {1, 2, 3, 4, 5};
SegTree<int> rsq(v, 0, [](int a, int b) { return a+b; });
rsq.add(1, 5);             // v[1] += 5
rsq.query(1, 3);           // [1,3] 합, 양끝 포함
rsq.find_kth(4);           // 누적합 >= 4인 첫 인덱스. 원소 비음수
SegTree<int> rmq(10, -1e9, [](int a, int b) { return max(a,b); });
rmq.update(2, 15);         // v[2] = 15
rmq.query(0, 5);           // [0,5] 최댓값
// find: 누적 결과가 조건을 처음 만족하는 인덱스, 없으면 -1.
// pref는 이미 지나온 왼쪽 구간, nd는 검사할 구간의 결과.
int tar = 10;
rmq.find([&](int pref, int nd) { return max(pref, nd) >= tar; });