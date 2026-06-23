/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Math/FPS.cpp)
 * [Tested on]
 * 
 */
template <ll M = 998244353>
struct Modint {
  using V = long long; V val;
  Modint() : val(0) {} Modint(auto y) : val(y % M) {}
  operator V() const { return val; }
  Modint operator-() const { return Modint() -= *this; }
  Modint operator+(auto rhs) const { return Modint(*this) += rhs; }
  Modint operator-(auto rhs) const { return Modint(*this) -= rhs; }
  Modint operator*(auto rhs) const { return Modint(*this) *= rhs; }
  Modint operator/(auto rhs) const { return Modint(*this) /= rhs; }
  Modint &operator+=(Modint rhs) { val += rhs.val; if (val >= M) val -= M; return *this; }
  Modint &operator-=(Modint rhs) { val -= rhs.val; if (val < 0) val += M; return *this; }
  Modint &operator*=(Modint rhs) { val = val * rhs.val % M; return *this; }
  Modint &operator/=(Modint rhs) { val = val * rhs.inv() % M; return *this; }
  Modint inv() { return inv(val, M); }
  V inv(ll x, ll m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  Modint pow(auto y) {
    if (y == 0) return Modint(1);
    if (y < 0) return Modint(val).inv().pow(-y);
    Modint ans(1), x(val);
    while (y) { if (y % 2) ans *= x; x *= x; y /= 2; }
    return ans;
  }
  friend std::ostream &operator<<(std::ostream &os, const Modint<M> &x) { return os << x.val; }
  friend std::istream &operator>>(std::istream &is, Modint<M> &x) { ll v; is >> v; x = v; return is; }
};
using Mint = Modint<998244353>;
using Poly = vector<Mint>;

struct FPS {
  Poly coef;
  FPS(Poly a) : coef(a) {}
  FPS(int n = 0) { coef.resize(1); coef[0] = Mint(n); }
  int size() { return coef.size(); }
  int deg() { return size() - 1; }
  Mint& operator[](int index) { assert(index < coef.size()); return coef[index]; }
  FPS operator+(auto f) {
    FPS res; res.resize(max(size(), f.size()));
    for (int i = 0; i < size(); i++) res.coef[i] += coef[i];
    for (int i = 0; i < f.size(); i++) res.coef[i] += f.coef[i];
    return res;
  }
  FPS operator-(auto f) {
    FPS res; res.resize(max(size(), f.size()));
    for (int i = 0; i < size(); i++) res.coef[i] += coef[i];
    for (int i = 0; i < f.size(); i++) res.coef[i] -= f.coef[i];
    return res;
  }
  FPS operator*(auto f) {
    Poly nc = polymul(coef, f.coef);
    nc.resize(size() + f.size() - 1); return FPS(nc);
  }
  FPS &operator+=(auto f) { return *this = *this + f; }
  FPS &operator-=(auto f) { return *this = *this - f; }
  FPS &operator*=(auto f) { return *this = *this * f; }
  void resize(int sz) { while (size() < sz) coef.push_back(Mint(0)); while (size() > sz) coef.pop_back(); }
  void shrink() { while (size() > 1 && coef.back() == 0) coef.pop_back(); }
  FPS power(ll k) {
    FPS res(1), f = *this; res[0] = 1;
    while (k) { if (k % 2) res = res * f; f = f * f; k /= 2; }
    return res;
  }
  FPS inv() {
    assert(coef[0] != 0); FPS g(Poly{Mint(coef[0]).inv()}), two(2);
    for (int sz = 1; sz < size(); sz *= 2) {
      FPS f(*this); f.resize(sz * 2);
      FPS tmp = g * f; tmp.resize(sz * 2);
      g = g * (two - tmp); g.resize(sz * 2);
    }
    g.resize(size()); return g;
  }
  FPS log() {
    assert(coef[0] != 0); FPS g = differenciate() * inv();
    g.resize(size()); g = g.integrate(); g.resize(size()); return g;
  }
  FPS differenciate() {
    FPS res; res.resize(size() - 1);
    for (int i = 1; i < size(); i++) res.coef[i - 1] = coef[i] * i;
    return res;
  }
  FPS integrate() {
    FPS res; res.resize(size() + 1);
    for (int i = 1; i <= size(); i++) res.coef[i] = coef[i - 1] * Mint(i).inv();
    return res;
  }
  FPS exp() {
    assert(coef[0] == 0); FPS g(1), one(1);
    for (int sz = 1; sz < 2 * size(); sz *= 2) {
      FPS f(*this); f.resize(sz * 2);
      g = g * (f + one - g.log()); g.resize(sz * 2);
    }
    g.resize(size()); return g;
  }
  void print() { for (int i = 0; i < size(); i++) cout << coef[i] << ' '; cout << endl; }
  Mint evaluate(Mint x) {
    Mint res(0);
    for (int i = size() - 1; i >= 0; i--) { res *= x; res += coef[i]; }
    return res;
  }
  private:
  void ntt(Poly &P, bool inv, Mint g) {
    int n = P.size(); if (n == 1) return;
    for (int i = 1, j = 0; i < n; i++) {
      int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit;
      j ^= bit; if (i < j) swap(P[i], P[j]);
    }
    vector<Mint> w(n / 2); w[0] = 1;
    for (int i = 1; i < n / 2; i++) w[i] = w[i - 1] * g;
    for (int i = 1; i < n; i <<= 1) {
      int nd = n / (2 * i);
      for (int j = 0; j < n; j += i << 1) {
        for (int k = 0; k < i; k++) {
          Mint tmp = P[i + j + k] * w[nd * k];
          P[i + j + k] = P[j + k] - tmp; P[j + k] += tmp;
        }
      }
    }
    if (inv) {
      Mint invn = Mint(n).inv();
      for (int i = 0; i < n; i++) P[i] *= invn;
    }
  }
  Poly polymul(Poly v1, Poly v2) {
    ll n1 = v1.size(), n2 = v2.size(), N = 1;
    while (N <= n1 + n2 - 1) N *= 2;
    v1.resize(N); v2.resize(N);
    Mint g = Mint(3).pow(998244353 / N);
    ntt(v1, false, g); ntt(v2, false, g);
    Poly res; res.resize(N);
    for (int i = 0; i < N; i++) res[i] = v1[i] * v2[i];
    ntt(res, true, g.inv()); return res;
  }
};