typedef long long ll;
template<int M> struct MINT {
    int v;
    MINT(ll _v = 0) { v = _v % M; if (v < 0) v += M; }
    MINT operator+(const MINT& o) const { return MINT(v + o.v); }
    MINT operator-(const MINT& o) const { return MINT(v - o.v); }
    MINT operator*(const MINT& o) const { return MINT((ll)v * o.v); }
    MINT& operator*=(const MINT& o) { return *this = *this * o; }
    friend MINT pw(MINT a, ll b) {
        MINT r = 1; for (; b; b >>= 1, a *= a) if (b & 1) r *= a;
        return r;
    }
    friend MINT inv(MINT a) { return pw(a, M - 2); }
};
namespace fft {
    using cpx = complex<double>;
    void rev_bit(int n, vector<auto>& a) {
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit;
            if (i < j) swap(a[i], a[j]);
        }
    }
    void FFT(vector<cpx>& a, bool inv_f) {
        int n = a.size(); rev_bit(n, a);
        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * acos(-1) / len * (inv_f ? -1 : 1);
            cpx wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                cpx w(1);
                for (int j = 0; j < len / 2; j++) {
                    cpx u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v; a[i + j + len / 2] = u - v; w *= wlen;
                }
            }
        }
        if (inv_f) for (auto& x : a) x /= n;
    }
    vector<ll> multiply(const vector<ll>& a, const vector<ll>& b) {
        int n = 1; while (n < a.size() + b.size()) n <<= 1;
        vector<cpx> fa(n), fb(n);
        for(int i=0; i<a.size(); i++) fa[i] = cpx(a[i], 0);
        for(int i=0; i<b.size(); i++) fb[i] = cpx(b[i], 0);
        FFT(fa, 0); FFT(fb, 0);
        for(int i=0; i<n; i++) fa[i] *= fb[i];
        FFT(fa, 1);
        vector<ll> res(n);
        for(int i=0; i<n; i++) res[i] = llround(fa[i].real());
        return res;
    }
    vector<ll> multiply_mod(const vector<ll>& a, const vector<ll>& b, ll mod) {
        int n = 1; while (n < a.size() + b.size()) n <<= 1;
        vector<cpx> v1(n), v2(n), r1(n), r2(n);
        for (int i = 0; i < a.size(); i++) v1[i] = cpx(a[i] >> 15, a[i] & 32767);
        for (int i = 0; i < b.size(); i++) v2[i] = cpx(b[i] >> 15, b[i] & 32767);
        FFT(v1, 0); FFT(v2, 0);
        for (int i = 0; i < n; i++) {
            int j = i ? n - i : i;
            cpx a1 = (v1[i] + conj(v1[j])) * cpx(0.5, 0), a2 = (v1[i] - conj(v1[j])) * cpx(0, -0.5);
            cpx b1 = (v2[i] + conj(v2[j])) * cpx(0.5, 0), b2 = (v2[i] - conj(v2[j])) * cpx(0, -0.5);
            r1[i] = a1 * b1 + a1 * b2 * cpx(0, 1); r2[i] = a2 * b1 + a2 * b2 * cpx(0, 1);
        }
        FFT(r1, 1); FFT(r2, 1);
        vector<ll> res(n);
        for (int i = 0; i < n; i++) {
            ll av = (ll)round(r1[i].real()) % mod, cv = (ll)round(r2[i].imag()) % mod;
            ll bv = ((ll)round(r1[i].imag()) + (ll)round(r2[i].real())) % mod;
            res[i] = (av << 30) + (bv << 15) + cv; res[i] = (res[i] % mod + mod) % mod;
        }
        return res;
    }
    template<int W, int M> void NTT(vector<MINT<M>>& a, bool inv_f) {
        int n = a.size(); rev_bit(n, a);
        for (int len = 2; len <= n; len <<= 1) {
            MINT<M> wlen = pw(MINT<M>(W), (M - 1) / len);
            if (inv_f) wlen = inv(wlen);
            for (int i = 0; i < n; i += len) {
                MINT<M> w = 1;
                for (int j = 0; j < len / 2; j++) {
                    MINT<M> u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v; a[i + j + len / 2] = u - v; w *= wlen;
                }
            }
        }
        if (inv_f) { MINT<M> rn = inv(MINT<M>(n)); for (auto& x : a) x *= rn; }
    }
}
template<int W, int M> struct Poly {
    using T = MINT<M>; vector<T> a;
    Poly(const vector<T>& _a = {}) : a(_a) { norm(); }
    void norm() { while (a.size() && a.back().v == 0) a.pop_back(); }
    int deg() const { return (int)a.size() - 1; }
    T operator[](int i) const { return i < a.size() ? a[i] : T(0); }
    Poly operator*(const Poly& o) const {
        if (a.empty() || o.a.empty()) return {};
        int n = 1, sz = a.size() + o.a.size() - 1;
        while (n < sz) n <<= 1;
        vector<T> fa(n), fb(n); copy(all(a), fa.begin()); copy(all(o.a), fb.begin());
        fft::NTT<W, M>(fa, 0); fft::NTT<W, M>(fb, 0);
        for (int i = 0; i < n; i++) fa[i] *= fb[i];
        fft::NTT<W, M>(fa, 1); return fa;
    }
    Poly inv(int n) const {
        Poly r({ ::inv(a[0]) });
        for (int i = 1; i < n; i <<= 1) {
            Poly tmp(vector<T>(a.begin(), a.begin() + min((int)a.size(), i * 2)));
            r = (r * (Poly({T(2)}) - r * tmp)); r.a.resize(i * 2);
        }
        r.a.resize(n); return r;
    }
    Poly operator/(Poly o) const {
        if (deg() < o.deg()) return {};
        int n = deg() - o.deg() + 1;
        Poly ra = a, rb = o.a; reverse(all(ra.a)); reverse(all(rb.a));
        Poly q = (ra * rb.inv(n)); q.a.resize(n); reverse(all(q.a)); return q;
    }
    Poly operator%(Poly o) const {
        if (deg() < o.deg()) return *this;
        Poly r = *this - (*this / o) * o; r.norm(); return r;
    }
    Poly operator-(const Poly& o) const {
        vector<T> res(max(a.size(), o.a.size()));
        for (int i = 0; i < res.size(); i++) res[i] = (*this)[i] - o[i];
        return res;
    }
};
using mint = MINT<998244353>;
using poly = Poly<3, 998244353>;
mint Kitamasa(poly c, poly a, ll n) {
    if (n <= a.deg()) return a[n];
    poly f; for (int i = 0; i <= c.deg(); i++) f.a.push_back(mint(0) - c[c.deg() - i]);
    f.a.push_back(1);
    poly res({1}), x({0, 1});
    for (; n; n >>= 1, x = (x * x) % f) if (n & 1) res = (res * x) % f;
    mint ans = 0; for (int i = 0; i <= a.deg(); i++) ans = ans + a[i] * res[i];
    return ans;
}
int main() {
    vector<ll> A = {1, 2, 1}; // 1+2*x+x^2
    vector<ll> B = {1, 1};    // 1+x
    vector<ll> C = fft::multiply(A, B); // {1, 3, 3, 1}
    vector<ll> D = fft::multiply_mod(A, B, 1000000007);
    poly p1({1, 2, 1}), p2({1, 1}); // NTT base
    p1 * p2; p1 / p2; p1 % p2; // polynomial operation
    // A_n = 1*A_{n-1} + 1*A_{n-2}
    poly coeffs({1, 1}); // {c0, c1} 순서 (A_{n-2}, A_{n-1} 계수)
    poly initial({0, 1}); // {A0, A1} 초기값
    cout << Kitamasa(coeffs, initial, 1000000000).v;
}