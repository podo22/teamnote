/**
 * [Metadata]
 * Reference : https://www.acmicpc.net/blog/view/117
 * Implemented by : alreadysolved
 * [Tested on]
 * 
*/
template<typename Node> struct SegTree {
  int n, size;
  Node e; // 항등원
  vector<Node> tree;
  function<Node(Node, Node)> func;
  SegTree(int n, const Node& e, auto func) : n(n), size(1<<(__lg(n)+1)), e(e), tree(size<<1, e), func(func) {}
  SegTree(const vector<Node>& v, const Node& e, auto func) : n(sz(v)), size(1<<(__lg(n)+1)), e(e), tree(size<<1, e), func(func) {
    for (int i = 0; i < n; i++) tree[i+size] = v[i];
    for (int i = size-1; i > 0; i--) tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
  }
  void add(int i, const Node& val) {
    tree[i += size] += val;
    while (i >>= 1) {
      tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
    }
  }
  void update(int i, const Node& val) {
    tree[i += size] = val;
    while (i >>= 1) {
      tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
    }
  }
  Node query(int i) { return tree[i + size]; }
  Node query(int l, int r) {
    Node L = e, R = e;
    for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
      if (l & 1) L = func(L, tree[l++]);
      if (~r & 1) R = func(tree[r--], R);
    }
    return func(L, R);
  }
  int find_kth(Node k) {
    if (tree[1] < k) return -1;
    int node = 1;
    while (node < size) {
      node <<= 1;
      if (tree[node] < k) { k -= tree[node]; node |= 1; }
    }
    return node - size;
  }
  int find(auto chk) {
    if (!chk(e, tree[1])) return -1;
    int cur = 1; Node pref = e;
    while (cur < size) {
      if (chk(pref, tree[cur << 1])) cur = cur << 1;
      else {
        pref = func(pref, tree[cur << 1]);
        cur = cur << 1 | 1;
      }
    }
    return cur - size;
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
  // pref: left prefix result, node: current node result
  int tar = 10;
  int idx = rmq.find([&](int pref, int node) {
    // First idx i where max(v[0..i]) >= tar
    return max(pref, node) >= tar;
    // First idx i where sum(v[0..i]) >= tar
    // return pref + node >= tar;
  });

  return 0;
}