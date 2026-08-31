/**
* [Metadata]
* Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/DataStructure/li_chao_tree.cpp)
* [Tested on]
* 
*/
struct LiChaoTree {
  // min LiChao, 정수, 사용하기 전에 init(min_x, max_x) 호출
  // update(0, {a, b}) : 직선 y=ax+b 추가
  // update(0, {a, b}, l, r) : y=ax+b를 x in [l, r]에 추가
  // query(0, k) : x=k에서 최솟값 리턴, 직선 없으면 INF
  // 쿼리, 직선 update : O(log n), 선분 update : O(log^2n)
  struct Line {
    ll a, b;
    ll get(ll x) { return a*x+b; }
  };
  struct Node {
    int l, r; ll s, e; Line line;
  };
  const ll INF = 4e18;
  const Line id = {0, INF};
  vector<Node> tree;
  void init(ll s, ll e) {
    tree.push_back({-1, -1, s, e, id});
  }
  void update(int node, Line v) {
    ll s = tree[node].s, e = tree[node].e, m = s+(e-s)/2;
    Line low = tree[node].line, high = v;
    if (low.get(s) > high.get(s)) swap(low, high);
    if (low.get(e) <= high.get(e)) {
      tree[node].line = low; return;
    }
    if (low.get(m) < high.get(m)) {
      tree[node].line = low;
      if (tree[node].r == -1) {
        tree[node].r = tree.size();
        tree.push_back({-1, -1, m+1, e, id});
      }
      update(tree[node].r, high);
    } else {
      tree[node].line = high;
      if (tree[node].l == -1) {
        tree[node].l = tree.size();
        tree.push_back({-1, -1, s, m, id});
      }
      update(tree[node].l, low);
    }
  }
  void update(int node, Line v, ll l, ll r) {
    if (r < tree[node].s || l > tree[node].e) return;
    if (l <= tree[node].s && tree[node].e <= r) {
      update(node, v); return;
    }
    ll s = tree[node].s, e = tree[node].e;
    ll m = s+(e-s)/2;
    if (tree[node].l == -1) {
      tree[node].l = tree.size();
      tree.push_back({-1, -1, s, m, id});
    }
    if (tree[node].r == -1) {
      tree[node].r = tree.size();
      tree.push_back({-1, -1, m+1, e, id});
    }
    update(tree[node].l, v, l, r);
    update(tree[node].r, v, l, r);
  }
  ll query(int node, ll x){
    if (node == -1) return INF;
    ll s = tree[node].s, e = tree[node].e;
    ll m = s + (e - s) / 2;
    if (x <= m) return min(tree[node].line.get(x), query(tree[node].l, x));
    else return min(tree[node].line.get(x), query(tree[node].r, x));
  }
};