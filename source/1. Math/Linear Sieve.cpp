vector<int> Linear_sieve(int N) {
    vector<int> sieve(N+1, 1), prime(N+1);
    int pcnt = 0;
    for (int i = 2; i <= N; i++) {
        if (sieve[i]) prime[pcnt++] = i;
        for (int j = 0; i*prime[j] <= N; j++) {
            sieve[i*prime[j]] = 0;
            if (i%prime[j] == 0) break;
        }
    }
    prime.resize(pcnt); return prime;
}