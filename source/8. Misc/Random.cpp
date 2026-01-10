#include <random>
#include <chrono>
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

uniform_int_distribution<int>(l, r)(rng); // [l, r]
uniform_real_distribution<double>(l, r)(rng); // [l, r)
shuffle(all(v), rng) // shuffle vector
vector<double> w = { 40, 10, 50 };
discrete_distribution<int>(all(w))(rng); // 0: 40%, 1: 10%, 2: 50%
bernoulli_distribution(P)(rng); // True with probability P(0.0~1.0)