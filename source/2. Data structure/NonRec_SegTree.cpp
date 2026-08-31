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
int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  // 1. RSQ (Range Sum Query)
  SegTree<int> rsq(v, 0, [](int a, int b) { return a+b; });
  rsq.add(1, 5);             // v[1] += 5
  int sum = rsq.query(1, 3); // Sum of v[1..3]
  int kth = rsq.find_kth(4); // First idx with prefix sum >= 4
  // 2. RMQ (Range Maximum Query)
  SegTree<int> rmq(10, -1e9, [](int a, int b) { return max(a, b); });
  rmq.update(2, 15);         // v[2] = 15
  int mx = rmq.query(0, 5);  // Max of v[0..5]
  // 3. SegTree Walk (find), O(log N)
  // pref: left prefix result, nd: current nd result
  int tar = 10;
  int idx = rmq.find([&](int pref, int nd) {
    // First idx i where max(v[0..i]) >= tar
    return max(pref, nd) >= tar;
    // First idx i where sum(v[0..i]) >= tar
    // return pref + nd >= tar;
  });
}