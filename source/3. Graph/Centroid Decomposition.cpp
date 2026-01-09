struct CentroidTree {
    int N;
    vector<vector<int>> adj;      // 원본 트리
    vector<vector<int>> c_adj;    // 센트로이드 트리
    vector<int> sz, par, vis;
    CentroidTree(int n) : N(n), adj(n + 1), c_adj(n + 1), sz(n + 1), par(n + 1), vis(n + 1, 0) {}
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int get_sz(int curr, int prev) {
        sz[curr] = 1;
        for (int next : adj[curr])
            if (next != prev && !vis[next]) sz[curr] += get_sz(next, curr);
        return sz[curr];
    }
    int get_centroid(int curr, int prev, int total_sz) {
        for (int next : adj[curr])
            if (next != prev && !vis[next] && sz[next] > total_sz / 2)
                return get_centroid(next, curr, total_sz);
        return curr;
    }
    // static_solve: 현재 센트로이드를 포함하는 모든 경로를 계산하는 로직
    void static_solve(int u) {
        /* */
    }
    int build(int curr, int p = -1) {
        int centroid = get_centroid(curr, -1, get_sz(curr, -1));
        static_solve(centroid); // 정적 분할 정복 문제일 때 사용
        vis[centroid] = 1;
        par[centroid] = p;
        for (int next : adj[centroid]) {
            if (!vis[next]) {
                int child = build(next, centroid);
                c_adj[centroid].push_back(child); // 센트로이드 계층 연결
            }
        }
        return centroid;
    }
};