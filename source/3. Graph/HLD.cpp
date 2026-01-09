struct HLD{
    vector<int> dep, par, sz, in, out, top;
    int idx;
    vector<vector<int>> adj, graph;
    int n;
    HLD (int n_){
        n = n_;
        idx = 0;
        dep.resize(n+1);
        par.resize(n+1);
        sz.resize(n+1);
        in.resize(n+1);
        out.resize(n+1);
        top.resize(n+1);
        adj.resize(n+1);
        graph.resize(n+1);
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int v=1, int pre=-1){
        for (int u : adj[v]){
            if (u == pre) continue;

            graph[v].push_back(u);
            dfs(u, v);
        }
    }
    void dfs1(int v=1){
        sz[v] = 1;
        for (int &u : graph[v]){
            dep[u] = dep[v] + 1;
            par[u] = v;
            dfs1(u);
            sz[v] += sz[u];

            if (sz[u] > sz[graph[v][0]]) swap(u, graph[v][0]);
        }
    }
    void dfs2(int v=1){
        in[v] = ++idx;
        for (int u : graph[v]){
            top[u] = (u == graph[v][0]) ? top[v] : u;
            dfs2(u);
        }
        out[v] = idx;
    }
    void calculate(){
        dfs(); dfs1(); dfs2();
    }
    array<vector<array<int, 2>>, 2> getPath(int u, int v){
        vector<array<int, 2>> v1, v2;
        while (top[u] != top[v]){
            if (dep[top[u]] > dep[top[v]]){
                ll xx = top[u];
                v1.push_back({in[xx], in[u]});
                u = par[xx];
            }else{
                ll xx = top[v];
                v2.push_back({in[xx], in[v]});
                v = par[xx];
            }
        }
        if (dep[u] < dep[v]){
            v2.push_back({in[u], in[v]});
        }else{
            v1.push_back({in[v], in[u]});
        }
        return {v1, v2};
        // auto pp = hld.getPath(u, v);
        // Node res1 = id;
        // Node res2 = id;
        // for (auto p2 : pp[0]){
        //     res1 = seg.merge(seg.query(p2[0], p2[1]+1), res1);
        // }
        // for (auto p2 : pp[1]){
        //     res2 = seg.merge(seg.query(p2[0], p2[1]+1), res2);
        // }
        // swap(res1.lsum, res1.rsum);
        // auto res = seg.merge(res1, res2);
    }
};
