/**
 * [Metadata]
 * Reference : https://www.acmicpc.net/blog/view/117
 * Implemented by : alreadysolved
 * [Tested on]
 * 
 */
template<typename Node>
struct SegTree {
  int n, lg, size;
  Node e; // 항등원
  vector<Node> tree;
  function<Node(Node, Node)> func;
  int log2(int n) {
    int res = 0;
    while (n > (1 << res)) res++;
    return res;
  }
  SegTree(int n, const Node& e, auto func) : n(n), lg(log2(n)), size(1<<lg), e(e), tree(size<<1, e), func(func) {}
  SegTree(const vector<Node>& v, const Node& e, auto func) : n(sz(v)), lg(log2(n)), size(1<<lg), e(e), tree(size<<1, e), func(func) {
    for (int i = 0; i < n; i++) tree[i+size] = v[i];
    for (int i = size-1; i > 0; i--) tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
  }
  void add(int i, const Node& val) {
    tree[i |= size] += val;
    while (i >>= 1) {
      tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
    }
  }
  void update(int i, const Node& val) {
    tree[i |= size] = val;
    while (i >>= 1) {
      tree[i] = func(tree[i<<1], tree[i<<1 | 1]);
    }
  }
  Node query(int i) { return tree[--i | size]; }
  Node query(int l, int r) {
    Node L = e, R = e;
    for (l |= size, r |= size; l <= r; l >>= 1, r >>= 1) {
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
  // 1. Range Sum Query (RSQ)
  vector<int> v = {1, 2, 3, 4, 5};
  SegTree<int> rsq(v, 0, [](int a, int b) { return a+b; });
  rsq.update(3, 10);
  int sum = rsq.query(2, 4);
  // 2. Range Minimum Query (RMQ)
  const int INF = 1e9;
  SegTree<int> rmq(N, INF, [](int a, int b) { return min(a, b); });
  // 3. Binary Search on Tree (Order Statistic)
  // - Requirement: The tree must represent frequency or counts.
  // - Find the smallest index i such that prefix_sum(1...i) >= k
  int idx = rsq.find_kth(7); 
}