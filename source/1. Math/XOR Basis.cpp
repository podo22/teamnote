/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
/* using Mask = bitset<MAX_N>; */
template <typename T = ll, int B = 62> struct Basis {
  T b[B]{}; int sz = 0;
  /* Mask mask[B]{}; */
  // 기저 원소 삽입, O(B)
  bool insert(T x /*, int id*/) {
    /* Mask cur; cur.set(id); */
    for (int i = B-1; i >= 0; i--) {
      if (!(x >> i & 1)) continue;
      if (!b[i]) {
        b[i] = x; sz++;
        /* mask[i] = cur; */
        return true;
      }
      x ^= b[i];
      /* cur ^= mask[i]; */
    }
    return false;
  }
  // 만들 수 있는 최댓값, O(B)
  T max_xor(T init = 0 /*, Mask &res*/) const {
    /* res.reset(); */
    for (int i = B-1; i >= 0; i--) {
      if ((init ^ b[i]) > init) {
        init ^= b[i];
        /* res ^= mask[i]; */
      }
    }
    return init;
  }
  // 0 제외 최솟값, O(B)
  T min_xor() const {
    for (int i = 0; i < B; i++) if (b[i]) return b[i];
    return 0;
  }
  // 기저로 줄인 잔여값. res: 사용한 원소들의 마스크.
  T reduce(T x /*, Mask* res = nullptr*/) const {
    /* if (res) res->reset(); */
    for (int i = B-1; i >= 0; i--) {
      if (x >> i & 1) {
        x ^= b[i];
        /* if (res) *res ^= mask[i]; */
      }
    }
    return x;
  }
  // 생성 가능 여부
  bool can(T x /*, Mask* res = nullptr*/) const {
    return reduce(x /*, res*/) == 0;
  }
  // 기약 사다리꼴(RREF) 기저 목록, O(B^2)
  vector<T> rref() const {
    T tmp[B]; copy(begin(b), end(b), tmp);
    for (int i = 0; i < B; i++) {
      if (!tmp[i]) continue;
      for (int j = i + 1; j < B; j++) {
        if (tmp[j] >> i & 1) tmp[j] ^= tmp[i];
      }
    }
    vector<T> rb;
    for (int i = 0; i < B; i++) if (tmp[i]) rb.push_back(tmp[i]);
    return rb;
  }
  // k번째 최소 XOR 합 (1-idx, 0 포함), O(B^2)
  T kth(ll k) const {
    if (k > (1ULL << sz)) return -1;
    auto rb = rref();
    T res = 0;
    for (int i = 0; i < sz; i++) {
      if ((k-1) >> i & 1) res ^= rb[i];
    }
    return res;
  }
  // x의 순위 (1-idx, 0 포함, 불가능 시 -1), O(B^2)
  ll rank(T x) const {
    auto rb = rref();
    ll res = 0;
    for (int i = 0; i < sz; i++) {
      if (x >= (x ^ rb[i])) {
        x ^= rb[i];
        res |= (1LL << i);
      }
    }
    return x ? -1 : res + 1;
  }
  // 기저 병합, O(B^2)
  void merge(const Basis& o) {
    for (int i = 0; i < B; i++) if (o.b[i]) insert(o.b[i]);
  }
};