struct BiMatch { // Hopcroft-Karp
    vector<vector<int>> graph, grev;
    vector<int> mA, mB, dist, work;
    vector<bool> visA, visB, fA, fB; // vertex i can be excluded from some max matching
    int ns, ms;
    BiMatch(int n, int m) : ns(n), ms(m), graph(n+1), grev(m+1), mA(n+1), mB(m+1), dist(n+1), work(n+1) {}
    void add(int a, int b) { graph[a].push_back(b); grev[b].push_back(a); }
    void bfs() {
        fill(all(dist), -1);
        queue<int> q;
        for (int i = 1; i <= ns; i++) if (!mA[i]) {
            dist[i] = 0; q.push(i);
        }
        while (!q.empty()) {
            int i = q.front(); q.pop();
            for (auto j : graph[i]) {
                int k = mB[j];
                if (k && dist[k] == -1) {
                    dist[k] = dist[i] + 1; q.push(k);
                }
            }
        }
    }
    bool dfs(int cur) {
        for (int& i = work[cur]; i < sz(graph[cur]); i++) {
            int nb = graph[cur][i], ori = mB[nb];
            if (!ori || dist[ori] == dist[cur] + 1 && dfs(ori)) {
                mA[cur] = nb; mB[nb] = cur; return true;
            }
        }
        return false;
    }
    int match() {
        int ans = 0;
        while (1) {
            fill(all(work), 0); bfs();
            int cnt = 0;
            for (int i = 1; i <= ns; i++) {
                if (!mA[i] && dfs(i)) cnt++;
            }
            if (!cnt) break;
            ans += cnt;
        }
        return ans;
    }
    void chkEss() {
        fA.assign(ns+1, 0); fB.assign(ms+1, 0);
        visA.assign(ns+1, 0); visB.assign(ms+1, 0);
        queue<int> q;
        for (int i = 1; i <= ns; i++) if (!mA[i]) fA[i] = visA[i] = 1, q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) if (!visB[v]) {
                visB[v] = 1; int r = mB[v];
                if (r && !fA[r]) {
                    fA[r] = visA[r] = 1; q.push(r);
                }
            }
        }
        for (int i = 1; i <= ms; i++) if (!mB[i]) fB[i] = 1, q.push(i);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : grev[v]) {
                int r = mA[u];
                if (r && !fB[r]) {
                    fB[r] = 1; q.push(r);
                }
            }
        }
    }
    pair<vector<int>,vector<int>> vertex() { // find minimum vertex cover
        chkEss();
        vector<int> va, vb;
        for (int i = 1; i <= ns; i++) if (!visA[i]) va.push_back(i);
        for (int i = 1; i <= ms; i++) if (visB[i]) vb.push_back(i);
        return { va, vb };
    }
};
/* struct BiMatch {
    vector<vector<int>> graph;
    vector<int> mA, mB, vis;
    int ns, ms;
    BiMatch(int n, int m) : ns(n), ms(m), graph(n+1), mA(n+1), mB(m+1), vis(n+1) {}
    void add(int a, int b) { graph[a].push_back(b); }
    bool dfs(int cur) {
        vis[cur] = 1;
        for (auto i : graph[cur]) {
            int ori = mB[i];
            if (ori == 0 || (!vis[ori] && dfs(ori))) {
                mA[cur] = i; mB[i] = cur; return true;
            }
        }
        return false;
    }
    int match() {
        int res = 0;
        for (int i = 1; i <= ns; i++) {
            if (mA[i]) continue;
            fill(all(vis), 0);
            if (dfs(i)) res++;
        }
        return res;
    }
}; */