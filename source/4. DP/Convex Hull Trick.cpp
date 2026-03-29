/**
 * [Metadata]
 * Original Author : Simon Lindholm
 * Source : https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
 * [Tested on]
 * 
 */
// Slopes(k) and queries(x) can be in any order
template <typename T> struct Line {
  mutable T k, m, p;
  bool operator<(const Line& o) const { return k < o.k; }
  bool operator<(T x) const { return p < x; }
};
template <typename T = ll> struct LineContainer : multiset<Line<T>, less<>> {
  using iterator = typename multiset<Line<T>, less<>>::iterator;
  // (for doubles, use div(a,b) = a/b)
  static constexpr T inf = numeric_limits<T>::max();
  T div(T a, T b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == this->end()) return x->p = inf, 0;
    if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
    else x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(T k, T m) { // y = kx + m
    auto z = this->insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = this->erase(z);
    if (x != this->begin() && isect(--x, y)) isect(x, y = this->erase(y));
    while ((y = x) != this->begin() && (--x)->p >= y->p)
    isect(x, this->erase(y));
  }
  T query(T x) {
    assert(!this->empty());
    auto l = *this->lower_bound(x);
    return l.k * x + l.m;
  }
}; // add(-k, -m), -query(x) for Lower hull(min)
LineContainer CHT;
int main() {
  dp[0] = 0; CHT.add(a[0], dp[0]);
  for (int i = 1; i < n; i++) { // dp[i] = Max(a[j]*b[i] + dp[j])
    dp[i] = CHT.query(b[i]);
    CHT.add(a[i], dp[i]);
  }
  cout << dp[n-1] << "\n";
}