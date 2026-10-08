/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Math/FPS.cpp)
 * Edited by : alreadysolved
 * [Tested on]
 * 
 */
struct Mint {
  static constexpr ll M = 998244353;
  using V = ll; V val;
  Mint(V y = 0) : val(y % M) { if (val < 0) val += M; }
  operator V() const { return val; }
  Mint operator-() const { return Mint(-val); }
  Mint operator+(auto r) const { return Mint(*this) += r; }
  Mint operator-(auto r) const { return Mint(*this) -= r; }
  Mint operator*(auto r) const { return Mint(*this) *= r; }
  Mint operator/(auto r) const { return Mint(*this) /= r; }
  Mint& operator+=(Mint r) { val += r.val; if (val >= M) val -= M; return *this; }
  Mint& operator-=(Mint r) { val -= r.val; if (val < 0) val += M; return *this; }
  Mint& operator*=(Mint r) { val = val * r.val % M; return *this; }
  Mint& operator/=(Mint r) { return *this *= r.inv(); }
  Mint inv() { assert(val); return inv(val, M); }
  V inv(ll x, ll m) { return x > 1 ? m - inv(m % x, x) * m / x : 1; }
  Mint pow(auto y) {
    if (y < 0) return inv().pow(-y);
    Mint r = 1, x = *this;
    for (; y; y /= 2, x *= x) if (y % 2) r *= x;
    return r;
  }
  friend ostream& operator<<(ostream& os, const Mint& x) { return os << x.val; }
  friend istream& operator>>(istream& is, Mint& x) { ll v; is >> v; x = v; return is; }
};
using Poly = vector<Mint>;
// coef[i]: x^i 계수. resize(N): 앞 N개 계수 유지(부족하면 0).
// inv/log/exp는 현재 size()=N을 기준으로 mod x^N 계산.
struct FPS {
  Poly coef;
  FPS(Poly a) : coef(move(a)) {}
  FPS(int n = 0) : coef{n} {}
  int size() { return coef.size(); }
  int deg() { return size()-1; }
  Mint& operator[](int index) { assert(index < coef.size()); return coef[index]; }
  FPS operator+(auto f) {
    FPS res = *this; res.resize(max(size(), f.size()));
    for (int i = 0; i < f.size(); i++) res[i] += f[i];
    return res;
  }
  FPS operator-(auto f) {
    FPS res = *this; res.resize(max(size(), f.size()));
    for (int i = 0; i < f.size(); i++) res[i] -= f[i];
    return res;
  }
  // 다항식 곱셈(컨볼루션). 결과 길이 = size()+f.size()-1.
  FPS operator*(auto f) { return FPS(polymul(coef, f.coef)); }
  FPS &operator+=(auto f) { return *this = *this + f; }
  FPS &operator-=(auto f) { return *this = *this - f; }
  FPS &operator*=(auto f) { return *this = *this * f; }
  void resize(int n) { coef.resize(n); }
  // 뒤의 0 제거. 계수 하나는 남김.
  void shrink() { while (size() > 1 && coef.back() == 0) coef.pop_back(); }
  FPS power(ll k) {
    FPS res(1), f = *this;
    for (; k; k /= 2, f *= f) if (k % 2) res *= f;
    return res;
  }
  // 1/f mod x^N. 조건: f[0] != 0.
  FPS inv() { assert(coef[0] != 0);
    FPS g(Poly{coef[0].inv()});
    for (int siz = 1; siz < size(); siz *= 2) {
      FPS f = *this; f.resize(siz*2);
      g *= FPS(2) - f*g; g.resize(siz*2);
    }
    g.resize(size()); return g;
  }
  // log(f) mod x^N. 조건: f[0] = 1.
  FPS log() { assert(coef[0] != 0);
    FPS g = differenciate() * inv();
    g.resize(size()-1); return g.integrate();
  }
  // 미분. 결과 길이 N-1.
  FPS differenciate() {
    FPS res; res.resize(size() - 1);
    for (int i = 1; i < size(); i++) res.coef[i - 1] = coef[i] * i;
    return res;
  }
  // 적분. 적분상수 0, 결과 길이 N+1.
  FPS integrate() {
    FPS res; res.resize(size() + 1);
    for (int i = 1; i <= size(); i++) res.coef[i] = coef[i - 1] * Mint(i).inv();
    return res;
  }
  // 형식적 지수 exp(f) mod x^N. 조건: f[0] = 0.
  FPS exp() { assert(coef[0] == 0);
    FPS g(1);
    for (int siz = 1; siz < size(); siz *= 2) {
      FPS f = *this; f.resize(siz*2); g.resize(siz*2);
      g *= f + FPS(1) - g.log(); g.resize(siz*2);
    }
    g.resize(size()); return g;
  }
  void print() { for (int i = 0; i < size(); i++) cout << coef[i] << ' '; cout << endl; }
  Mint evaluate(Mint x) {
    Mint res = 0;
    for (int i = size()-1; i >= 0; i--) res = res*x + coef[i];
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
      for (auto &x : P) x *= invn;
    }
  }
  Poly polymul(Poly a, Poly b) {
    if (a.empty() || b.empty()) return {};
    int n = a.size()+b.size()-1, N = 1;
    while (N < n) N *= 2;
    a.resize(N); b.resize(N);
    Mint g = Mint(3).pow(998244353 / N);
    ntt(a, false, g); ntt(b, false, g);
    for (int i = 0; i < N; i++) a[i] *= b[i];
    ntt(a, true, g.inv()); a.resize(n); return a;
  }
};
// Bostan-Mori: 유리 생성함수 P/Q의 x^k 계수. Q[0]!=0, k>=0.
// d=max(deg P, deg Q), O(d log d log(k+1)). 현재 연산은 mod 998244353.
// 용도: 차수는 작고 인덱스 k는 큰 선형 점화식의 항 계산.
// a[n]=c[1]a[n-1]+...+c[d]a[n-d]일 때:
// A={a[0],...,a[d-1]}, Q={1,-c[1],...,-c[d]}.
// P=FPS(A)*Q; P.resize(d); Bostan_Mori(P,Q,k) = a[k].
Mint Bostan_Mori(FPS P, FPS Q, ll k) {
  while (k) { FPS R = Q;
    for (int i = 1; i < R.size(); i+=2) R[i] = -R[i];
    P *= R; Q *= R; Poly tmp;
    for (int i = k%2; i < P.size(); i+=2) tmp.push_back(P[i]);
    P.coef.swap(tmp); tmp.clear();
    for (int i = 0; i < Q.size(); i+=2) tmp.push_back(Q[i]);
    Q.coef.swap(tmp); k /= 2;
  }
  return P.size() ? P[0] / Q[0] : Mint(0);
}