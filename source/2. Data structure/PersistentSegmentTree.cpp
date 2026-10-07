/**
 * [Metadata]
 * 
 * [Tested on]
 * 
 */
// 정적 배열의 구간 값 쿼리용 PST.
// 배열 0-based, [l,r] 양끝 포함, kth의 k는 1-based.
// root[i]: 앞의 i개 원소의 빈도표. [l,r] = root[r+1]-root[l].
// 구축/공간 O(N log M), 쿼리 O(log M). M은 서로 다른 값 수.
struct PST {
  struct Node { int l = 0, r = 0, cnt = 0; };
  vector<Node> tr{{}}; // 0번: 빈 노드
  vector<int> root;
  vector<ll> v;
  int n, m;
  PST(const vector<ll>& a) : root(sz(a)+1), v(a), n(sz(a)) {
    compress(v); m = sz(v);
    for (int i = 0; i < n; i++) {
      int x = lower_bound(all(v), a[i]) - v.begin();
      root[i+1] = add(root[i], 0, m-1, x);
    }
  }
  int add(int p, int s, int e, int x) {
    int u = sz(tr); tr.push_back(tr[p]); tr[u].cnt++;
    if (s == e) return u;
    int mid = (s + e) >> 1;
    if (x <= mid) tr[u].l = add(tr[p].l, s, mid, x);
    else tr[u].r = add(tr[p].r, mid+1, e, x);
    return u;
  }
  int query(int p, int q, int s, int e, int l, int r) const {
    if (l > r || r < s || e < l || p == q) return 0;
    if (l <= s && e <= r) return tr[q].cnt - tr[p].cnt;
    int mid = (s + e) >> 1;
    return query(tr[p].l, tr[q].l, s, mid, l, r)
         + query(tr[p].r, tr[q].r, mid+1, e, l, r);
  }
  int count_idx(int l, int r, int L, int R) const { // 압축값 [L,R] 개수
    assert(0 <= l && l <= r && r < n);
    return query(root[l], root[r+1], 0, m-1, L, R);
  }
  int count_less(int l, int r, ll x) const { // 원소 < x
    int R = lower_bound(all(v), x) - v.begin() - 1;
    return count_idx(l, r, 0, R);
  }
  int count_le(int l, int r, ll x) const { // 원소 <= x
    int R = upper_bound(all(v), x) - v.begin() - 1;
    return count_idx(l, r, 0, R);
  }
  int count(int l, int r, ll lo, ll hi) const { // lo <= 원소 <= hi
    int L = lower_bound(all(v), lo) - v.begin();
    int R = upper_bound(all(v), hi) - v.begin() - 1;
    return count_idx(l, r, L, R);
  }
  ll kth(int l, int r, int k) const { // 중복 포함 k번째 작은 값
    assert(0 <= l && l <= r && r < n && 1 <= k && k <= r-l+1);
    int p = root[l], q = root[r+1], s = 0, e = m-1;
    while (s < e) {
      int mid = (s + e) >> 1, cnt = tr[tr[q].l].cnt - tr[tr[p].l].cnt;
      if (k <= cnt) p = tr[p].l, q = tr[q].l, e = mid;
      else k -= cnt, p = tr[p].r, q = tr[q].r, s = mid+1;
    }
    return v[s];
  }
  optional<ll> prev(int l, int r, ll x) const { // x 이하 최댓값
    int k = count_le(l, r, x);
    if (!k) return nullopt;
    return kth(l, r, k);
  }
  optional<ll> next(int l, int r, ll x) const { // x 이상 최솟값
    int k = count_less(l, r, x) + 1;
    if (k > r-l+1) return nullopt;
    return kth(l, r, k);
  }
};
// (r-l+1)-pst.count_less(l,r,x);        // x 이상 개수
// (r-l+1)-pst.count_le(l,r,x);          // x 초과 개수
// pst.kth(l,r,r-l+2-k);                // k번째 큰 값
// auto x = pst.next(l,r,tar); if(x) cout << *x;