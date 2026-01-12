/**
 * [Metadata]
 * Original Author : ahgus89
 * Source : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Math/LinearSieve.cpp
 * [Tested on]
 * 
 */
struct Sieve {
  // sp: 최소 소인수, e: i의 최소 소인수 지수, phi: 오일러 피 함수(1~i 중 i와 서로소인 개수), mu: 뫼비우스 함수, tau: 약수 개수, sigma: 약수의 합
  vector<int> sp, e, phi, mu, tau, sigma, tmp, primes;
  Sieve(int n) : sp(n+1), e(n+1), phi(n+1), mu(n+1), tau(n+1), sigma(n+1), tmp(n+1) {
    phi[1] = mu[1] = tau[1] = sigma[1] = 1;
    for (int i = 2; i <= n; i++) {
      if (!sp[i]) {
        sp[i]=i; primes.push_back(i);
        e[i]=1; phi[i]=i-1; mu[i]=-1; tau[i]=2; sigma[i]=tmp[i]=i+1;
      }
      for (int p : primes) {
        if (i*p > n || p > sp[i]) break;
        int m = i*p; sp[m] = p;
        if (i%p == 0) {
          e[m] = e[i]+1; phi[m] = phi[i]*p; mu[m] = 0;
          tau[m] = tau[i]/(e[i]+1)*(e[m]+1);
          tmp[m] = tmp[i]*p+1; sigma[m] = sigma[i]/tmp[i]*tmp[m];
          break;
        }
        e[m] = 1; phi[m] = phi[i]*(p-1); mu[m] = -mu[i];
        tau[m] = tau[i]*2; tmp[m] = p+1; sigma[m] = sigma[i]*(p+1);
      }
    }
  }
};