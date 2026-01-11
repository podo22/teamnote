auto spfa = [&](int s) -> bool {
    vector<int> c(n+1), inq(n+1); fill(all(d), INF);
    deque<int> q; q.push_back(s); d[s] = 0; inq[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop_front(); inq[u] = 0;
        for (auto [w, v] : adj[u]) if (d[v] > d[u] + w) {
            d[v] = d[u] + w; if (inq[v]) continue;
            if (sz(q) && d[v] < d[q.front()]) q.push_front(v);
            else q.push_back(v);
            inq[v] = 1; if (++c[v] >= n) return 0;
        }
    }
    return 1;
};