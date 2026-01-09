struct BiMatch { // Hopcroft-Karp
    vector<vector<int>> graph, grev;
    vector<int> mA, mB, dist, work, vis;
    int ns, ms;
    BiMatch(int n, int m) : ns(n), ms(m) {
        graph.resize(n+1);
        grev.resize(m+1);
        mA.resize(n+1);
        mB.resize(m+1);
        dist.resize(n+1);
        work.resize(n+1);
        vis.resize(max(n,m)+1);
    }
    void add(int a, int b) { graph[a].push_back(b); grev[b].push_back(a); }
    void bfs() {
        fill(all(dist), -1);
        queue<int> q;
        for (int i = 1; i <= ns; i++) {
            if (!mA[i]) {
                dist[i] = 0;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int i = q.front(); q.pop();
            for (auto j : graph[i]) {
                int k = mB[j];
                if (k && dist[k] == -1) {
                    dist[k] = dist[i] + 1;
                    q.push(k);
                }
            }
        }
    }
    bool dfs(int cur) {
        for (int& i = work[cur]; i < sz(graph[cur]); i++) {
            int nb = graph[cur][i];
            int ori = mB[nb];
            if (!ori || dist[ori] == dist[cur] + 1 && dfs(ori)) {
                mA[cur] = nb;
                mB[nb] = cur;
                return true;
            }
        }
        return false;
    }
    int match() {
        int ans = 0;
        while (1) {
            fill(all(work), 0);
            bfs();
            int cnt = 0;
            for (int i = 1; i <= ns; i++) {
                if (!mA[i] && dfs(i)) cnt++;
            }
            if (!cnt) break;
            ans += cnt;
        }
        return ans;
    }
    pair<vector<int>,vector<int>> vertex() { // find minimum vertex cover
        vector<bool> visA(ns+1), visB(ms+1);
        queue<int> q;
        for (int i = 1; i <= ns; i++) {
            if (!mA[i]) {
                q.push(i);
                visA[i] = 1;
            }
        }
        while (!q.empty()) {
            int a = q.front(); q.pop();
            for (auto b : graph[a]) {
                if (!visB[b]) {
                    visB[b] = 1;
                    int na = mB[b];
                    if (na && !visA[na]) {
                        visA[na] = 1;
                        q.push(na);
                    }
                }
            }
        }
        vector<int> retA, retB;
        for (int i = 1; i <= ns; i++) {
            if (visA[i]) retA.push_back(i);
        }
        for (int i = 1; i <= ms; i++) {
            if (!visB[i]) retB.push_back(i);
        }
        return { retA, retB };
    }
    bool dfs1(int a, int b) {
        vis[a] = 1;
        for (auto i : graph[a]) {
            if (i == b) continue;
            int ori = mB[i];
            if (ori == 0 || (!vis[ori] && dfs1(ori, b))) {
                return true;
            }
        }
        return false;
    }
    bool dfs2(int b, int a) {
        vis[b] = 1;
        for (auto i : grev[b]) {
            if (i == a) continue;
            int ori = mA[i];
            if (ori == 0 || (!vis[ori] && dfs2(ori, a))) {
                return true;
            }
        }
        return false;
    }
    bool chk1(int a) { // find max matching except a
        fill(all(vis), 0);
        int b = mA[a];
        return (b == 0) || dfs2(b, a);
    }
    bool chk2(int b) { // find max matching except b
        fill(all(vis), 0);
        int a = mB[b];
        return (a == 0) || dfs1(a, b);
    }
};

/*
struct BiMatch {
    vector<vector<int>> graph;
    vector<int> mA, mB, vis;
    int ns, ms;
    BiMatch(int n, int m) : ns(n), ms(m) {
        graph.resize(n+1);
        mA.resize(n+1);
        mB.resize(m+1);
        vis.resize(n+1);
    }
    void add(int a, int b) { graph[a].push_back(b); }
    bool dfs(int cur) {
        vis[cur] = 1;
        for (auto i : graph[cur]) {
            int ori = mB[i];
            if (ori == 0 || (!vis[ori] && dfs(ori))) {
                mA[cur] = i;
                mB[i] = cur;
                return true;
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
};
*/