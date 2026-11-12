/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/DataStructure/li_chao_tr.cpp)
 * [Tested on]
 * 
 */
struct LiChaoTree {
  // min LiChao, 정수, 사용하기 전에 init(min_x, max_x) 호출
  // update(0, {a, b}) : 직선 y=ax+b 추가
  // update(0, {a, b}, l, r) : y=ax+b를 x in [l, r]에 추가
  // 정수 x의 최솟값. init(L,R)은 객체당 한 번. 쿼리 x는 [L,R].
  struct Line { ll a, b; ll get(ll x) { return a*x+b; } };
  struct Node { int l, r; ll s, e; Line ln; };
  const ll INF = 4e18; const Line id = {0, INF};
  vector<Node> tr;
  void init(ll s, ll e) { tr.assign(1, {-1, -1, s, e, id}); }
  void update(int nd, Line v) {
    ll s = tr[nd].s, e = tr[nd].e, m = s+(e-s)/2;
    Line low = tr[nd].ln, high = v;
    if (low.get(s) > high.get(s)) swap(low, high);
    if (low.get(e) <= high.get(e)) { tr[nd].ln = low; return; }
    if (low.get(m) < high.get(m)) {
      tr[nd].ln = low;
      if (tr[nd].r == -1) { tr[nd].r = tr.size();
        tr.push_back({-1, -1, m+1, e, id});
      } update(tr[nd].r, high);
    } else {
      tr[nd].ln = high;
      if (tr[nd].l == -1) { tr[nd].l = tr.size();
        tr.push_back({-1, -1, s, m, id});
      } update(tr[nd].l, low);
    }
  }
  void update(int nd, Line v, ll l, ll r) {
    if (r < tr[nd].s || l > tr[nd].e) return;
    if (l <= tr[nd].s && tr[nd].e <= r) { update(nd, v); return; }
    ll s = tr[nd].s, e = tr[nd].e, m = s+(e-s)/2;
    if (tr[nd].l == -1) { tr[nd].l = tr.size();
      tr.push_back({-1, -1, s, m, id});
    }
    if (tr[nd].r == -1) { tr[nd].r = tr.size();
      tr.push_back({-1, -1, m+1, e, id});
    }
    update(tr[nd].l, v, l, r); update(tr[nd].r, v, l, r);
  }
  ll query(int nd, ll x){
    if (nd == -1) return INF;
    ll s = tr[nd].s, e = tr[nd].e, m = s+(e-s) / 2;
    if (x <= m) return min(tr[nd].ln.get(x), query(tr[nd].l, x));
    else return min(tr[nd].ln.get(x), query(tr[nd].r, x));
  }
};