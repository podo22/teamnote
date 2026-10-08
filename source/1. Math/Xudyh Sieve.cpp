/**
 * [Metadata]
 * Original Author : Aeren
 * Source : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Math/XudyhSieve.cpp
 * [Tested on]
 * 
 */
// f의 누적합: g와 f*g의 누적합을 쉽게 계산할 수 있을 때.
// pf(n): 전처리한 f의 누적합, pg(n): g의 누적합, pfg(n): f*g의 누적합.
// mu 누적합: pg(n)=n, pfg(n)=1.
// phi 누적합: pg(n)=n, pfg(n)=n(n+1)/2.
// th까지 pf 전처리 후 xudyh_sieve(th,pf,pg,pfg).query(N).
template<class T, class F1, class F2, class F3>
struct xudyh_sieve{
  T th; // threshold, 2(single query) ~ 5 * MAXN^2/3
  F1 pf; F2 pg; F3 pfg;
  // prefix sum of f(up to th), g(easy to calc), f*g(easy to calc)
  unordered_map<T, T> mp; // f * g means dirichlet conv.
  xudyh_sieve(T th, F1 pf, F2 pg, F3 pfg) : th(th), pf(pf),p g(pg), pfg(pfg) {}
  // Calculate the preix sum of a multiplicative f up to n
  T query(T n){ // O(n^2/3)
    if(n <= th) return pf(n); if(mp.count(n)) return mp[n];
    T res = pfg(n);
    for(T low = 2, high = 2; low <= n; low = high + 1){
      high = n / (n / low);
      res -= (pg(high) - pg(low - 1)) * query(n / low);
      res = (res % MOD + MOD) % MOD; // delete
    }
    return mp[n] = res * modpow(pg(1), MOD-2, MOD) % MOD; // res / pg(1);
  }
};