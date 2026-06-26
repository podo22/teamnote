/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/DataStructure/li_chao_tree.cpp)
 * [Tested on]
 * 
 */
struct LiChaoTree{
  struct Line{
    ll a, b;
    ll get(ll x){
      return a*x+b;
    }
  };
  struct Node{
    int l, r;
    ll s, e;
    Line line;
  };
  const ll INF = 1e18;
  const Line id = {0, INF};
  vector<Node> tree;
  void init(ll s, ll e){
    tree.push_back({-1, -1, s, e, id});
  }
  void update(int node, Line v){
    ll s = tree[node].s, e = tree[node].e;
    ll m = (s + e) / 2;
    Line low = tree[node].line, high = v;
    if (low.get(s) > high.get(s)) swap(low, high);
    if (low.get(e) <= high.get(e)){
      tree[node].line = low;
      return;
    }
    if (low.get(m) < high.get(m)){
      tree[node].line = low;
      if (tree[node].r == -1){
        tree[node].r = tree.size();
        tree.push_back({-1, -1, m+1, e, id});
      }
      update(tree[node].r, high);
    }else{
      tree[node].line = high;
      if (tree[node].l == -1){
        tree[node].l = tree.size();
        tree.push_back({-1, -1, s, m, id});
      }
      update(tree[node].l, low);
    }
  }
  ll query(int node, ll x){
    if (node == -1) return INF;
    ll s = tree[node].s, e = tree[node].e;
    ll m = (s + e) / 2;
    if (x <= m) return min(tree[node].line.get(x), query(tree[node].l, x));
    else return min(tree[node].line.get(x), query(tree[node].r, x));
  }
};