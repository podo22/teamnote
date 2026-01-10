template <typename T>
struct KMP {
    T P; vector<int> pi;
    KMP(const T& P) : P(P), pi(sz(P)) {
        for (int i = 1, j = 0; i < sz(P); i++) {
            while (j > 0 && P[i] != P[j]) j = pi[j-1];
            if (P[i] == P[j]) pi[i] = ++j;
        }
    }
    vector<int> find(const T& S) {
        vector<int> res;
        int n = sz(S), m = sz(P), j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && S[i] != P[j]) j = pi[j-1];
            if (S[i] == P[j]) {
                if (j == m-1) {
                    res.push_back(i-m+1); j = pi[j];
                }
                else j++;
            }
        }
        return res;
    }
    int minPeriod() {
        int m = sz(P); if (m == 0) return 0;
        int len = m - pi[m-1]; if (m % len == 0) return len;
        return m;
    }
};